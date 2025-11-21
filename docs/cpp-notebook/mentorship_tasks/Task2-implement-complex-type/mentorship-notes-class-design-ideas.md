**source** : Email conversations with Joanthon Bell
## Concepts & Terminology

### Expressions & Evaluation

- **Expression**: a phrase in source code describing a computation.  
    Example: `(1 + 2) * 3`.
(1+2) becomes 3
3x3 becomes 9
Each step is a reduction.
We think +, * as symbols in maths, but in CS they are just functions with special names and infix syntax.

**so (1+2) really means:**
**operator+(1 , 2)**

and 3x3 means operator*(3 ,3)

**Expressions are just a recipie for compution
Operators are really functions
evaluation is just reducing the recipie step by step until you end up with a final value**

- **Computation**: the reduction of a subexpression to an intermediate value.  
    Example: `(1 + 2)` reduces to `3`.
- **Value**: an expression with no further reductions possible.
- **Evaluation**: the process of reducing computations until:
    - It terminates with a value
    - It terminates with an error
    - It does not terminate (infinite loop)
### Functions vs Operators

- An operator is just a function with a “funny name” and infix syntax.
    
- Stroustroup insight:
insight 1:
Stroustroup had the insight that the traditional arithmetic operators could simply be viewed and defined as ordinary functions that are referred to with a traditional infix syntax, but in every other respect may be thought of, and behave like, any other function.
insight 2:
We often use the same name (symbol) for different underlying operations.
  - Example:
    - `int + int → int`
    - `float + float → float`
    - Both are written as `operator+`, but they are different functions internally.


- C++ allows **overloading**: c++ allows same name to given to two functions provided the number and types of their arguments differ. -> The compiler uses **type inference** to decide which version to call at the **call site** (sub expression in which the function is being applied)
  - If it can’t decide (ambiguity), you must disambiguate with:
    - a **cast**
    - or a **fully qualified name**

(**basics**: phrase **fully qualified name** : things like `namespace::function`, `Class::function` )

 This idea evolved into **operator overloading** in C++.
  - You can define custom behavior for operators (`+`, `==`, etc.) for user-defined types.
  - This lets custom types "look and feel" like built-in types.

### Value Types

- A **value type** (built-in or user-defined) should:
    
    - Behave like a built-in in terms of initialization, assignment, copying, moving, destruction.
        
    - Support some arithmetic operations, depending on type (e.g. `double` supports arithmetic but not bitwise).
        

### What Happens When Rebinding to a User-Defined Type

- When replacing a built-in type (e.g. `int`) with a user-defined type (e.g. `Complex`), many expressions may stop compiling.
    
- Missing functions fall into **two broad groups**:
    
    1. **Arithmetic operations** (type-specific):
        
        - Built-in types like `int` or `double` already provide them (`+`, `-`, `*`, `/`, etc.).
            
        - For user-defined types, you must overload these explicitly (e.g. `operator+`, `operator*`).
            
    2. **General value-type operations** (universal for all values):
        
        - Copy constructor, assignment operator, destructor, initialization, comparison.
            
        - Built-ins support these automatically.
            
        - For user-defined types, the compiler generates many of them unless disabled, but you may need to define them explicitly (→ special member functions).
            
- Key idea: first ensure your type supports the **general value-type operations**; only then extend with **arithmetic operations** as appropriate.
### Operator Families

- Operators naturally come in groups.
    
    - Example: if you support `+`, you probably want to support `+=`, `-`, `-=`, and unary `-`.
        
- The language doesn’t enforce families, but good design does.
    

---
**Style Guidance**

- Use **tab/indent size of 2 spaces**.
    
- Use **Allman bracing style**


---
**Initialization vs Assignment**

- Both can use `=` in syntax, but they are conceptually different.
**Initialization** = construct a new value, possibly binding an identifier. -> **constructor**
**Assignment** = change the value of an existing object.-> **assignment operator**


**Complex Class Guidance**

- For now, provide only the **minimum member functions needed** to support the abstraction.
    
- Everything else (like arithmetic operators) can and should be implemented as **non-member functions**.
    
- This is part of a bigger design principle: **“members vs non-members”** — when to use each. (Jonathon will explain later.)

### Class Design Principle

- Beginners often put _everything_ into a class to make it “complete.”
    
- This leads to clutter and harder-to-maintain designs.
    
- Better approach:
    
    - Identify a **minimal spanning set** of members (like a basis in linear algebra).
        
    - Anything else can be built as non-member functions without losing efficiency.
        
    - Example: For a `string`-like class, the minimal set includes memory management + insert/remove chars. Everything else (search, concat, etc.) can be non-member.
        

### Members vs Non-Members

- Rule of thumb:
    
    - Put the **minimal spanning set** of necessary functions as members.
        
    - Implement everything else as non-members (free functions).
        
- `std::complex` is a good example of this split:
    
    - **Members**: constructors, assignment,etc..
        
    - **Non-members**: arithmetic (`+`, `-`, `*`, `/`), comparisons,etc..

---

## Notes on `operator+=` (member) vs `operator+` (non-member)

### 1. Functions can be:

- **Member** of a class.
    
- **Friend** of a class.
    
- **Neither** (just a free function).
### 2. Functions that _must_ be members

- SMFs
    
- and few other odd balls such as:
    
    - `operator[]` (subscript)
        
    - `operator()` (function call)
        
    - `operator->` (member access)
        
- Possibly a few others.

### 3. When to make a function a member

- If it needs **access to private state** (e.g. mutates `real_`, `imag_`).
    
- Example: `operator+=` must change the internals of `Complex`.

### 4. When to make a function a non-

when that function can be implemented using the public interface of the class


In Jonathon's words: "Some functions require one (or more) instances of class _c_  to be passed as parameters, put can accomplish the task purely through the use of the public interface of the object.  _complex::operator+_ likely falls into this category because it can (and _should)_ be coded as inline wrapper around _complex::+=,_ thus guaranteeing semantic consistency."


Let’s say we have:
```cpp
struct Complex
 {     double real, imag;    
   Complex& operator+=(const Complex& other) 
   {
	real += other.real;
    imag += other.imag;
    return *this;
   }
 };
```


- `operator+=` **needs access** to the private members (`real`, `imag`) in order to mutate the state.  
    → That’s why it usually makes sense as a **member function**.
Now, what about `operator+`?

```cpp
Complex operator+(Complex lhs, const Complex& rhs) {
    lhs += rhs;   // reuse operator+=
    return lhs;
}
```

**The key point**: `operator+` does _not_ need direct access to `real` and `imag` because it can express itself entirely in terms of the **already-public `operator+= `** (using the public interface)

-> "`operator+` can be coded as an inline wrapper around `operator+=`, thus guaranteeing semantic consistency."

```
**Semantic consistency**

- If you change how `operator+=` works (say, switching from Cartesian to polar representation), then `operator+` automatically stays consistent, because it is defined in terms of `+=`.

imagine later you **change the representation** of `Complex` (e.g. from Cartesian `(real, imag)` to Polar `(r, θ)`), or you **add extra logic** (bounds checking, normalization, logging, etc.) inside `operator+=`.

Now you’d have to remember to update both functions. If you forget, you risk:
- `a += b` behaving one way
- `a + b` behaving differently
That’s **semantic inconsistency** — the two operators _look_ related, but _act_ differently.

```

---

### 6. Implicit coercions

**coercion**: Coercion = automatic type conversion by the compiler.
`double d = 3;   // int 3 is automatically coerced into double 3.0`

**Implicit coercion for user-defined types** :
If your class has a **single-argument constructor that isn’t marked `explicit`**, then the compiler is allowed to automatically convert values to your class type.

```cpp
struct C {
    int v;
    C(int x) : v(x) {}   // not explicit!
};

void f(C c) {}

int main() {
    f(10);  //  int 10 is automatically turned into C(10)
}

```

So here, `10` (an `int`) is **implicitly coerced** into a `C`.


in a member function:
```cpp
struct Complex {
    Complex(double) {}
    Complex operator+(const Complex& rhs) const;
};

Complex a(1.0);
a + 2.0;

```

this looks like this:
`a.operator+(2.0);`

a is the object.
coercion is available only for parameters. not for the object

in a free function:
```cpp
inline Complex operator+(Complex lhs, const Complex& rhs) {
    return lhs; // simplified
}

```

when you call `2.0 + a;`

it is really `operator+(2.0, a);

here the 2.0 will be implicitly converted to Complex (given the complex constructor is not marked explicit)

(i mean the complex constructor is not marked explicit for this exact purpose)

"For arithmetic types like numbers, complex numbers, and so on, the availability of implicit coercions in _both_ arguments of af an overloaded operator is convenient because allows for the expected symmetry without requiring a combinatorial explosion in the number of overloads that must be implemented, was part of the original motivation for supporting implicit coerceions in the early design of C+:"

```cpp
std::complex a(3.0, 2.0);

a + 2.0;   // i.e     operator + (a, std::complex(2.0))

2.0 + a;   // i.e     operator + (std::complex(2.0), a)
```

---
### 6. Why avoid friends?


We generally try to avoid the use of friend function , because it introduces a form of coupling between two types that is often undesirable

Coupling = how strongly one piece of code depends on another.

- **Loose coupling** → modules only depend on the _public interface_ of each other. They can evolve independently.
    
- **Tight coupling** → modules depend on each other’s _implementation details_. If one changes, the other breaks.

If a function is a `friend`, it can peek into your class’s private data. 
So if you change the implementation, all your friends might break.

"We generally try to avoid the use of _friend_s , because it introduces a form of coupling between two types that is often undesirable.,"



### 7) Client can add as many global functions as needed
7) Clients can always add more global functions (without risk of polluting the global namespace, because function overload resolution prevents the ‘wrong’ function from being picked up) but cannot add more class members.
- **Class maintainer** = the person who writes and owns the class (`Complex`).
    
- **Client** = anyone who _uses_ the class in their code.
    

Clients shouldn’t need to crack open the class definition to extend it — that would break encapsulation and make upgrades harder.



clients are **locked out** from adding members.

But clients _can_ add global (non-member) functions

Suppose `Complex` already exposes a minimal public interface (constructors, `+=`, getters).  
As a client, you can write:

```cpp
Complex operator*(Complex lhs, const Complex& rhs) {
    lhs *= rhs;    // reuse public operator*=
    return lhs;
}

```

or even:

```cpp
bool isZero(const Complex& c) {
    return c.real() == 0 && c.imag() == 0;   // assuming getters exist
}

```

These are **non-member functions** — they live in the client’s code, not inside `Complex`.

You didn’t have to touch the original `Complex` class

you add global / free function without polluting the global namesapce:

 lets say complex is defined in namespace math:
 
 ```cpp
 namespace math {
    struct Complex {
        Complex& operator+=(const Complex&);
        double real() const;
        double imag() const;
    };
}

 ```

as a client you can add :

```cpp
namespace math {
    Complex operator+(Complex lhs, const Complex& rhs) {
        lhs += rhs;
        return lhs;
    }
}

```

now when you write:

```cpp
math::Complex a, b;
a + b;    // picks up *your* operator+ automatically

```

`the compiler looks into the namespace of the argument types (`math`), finds your overload, and uses it.`

So you’re not “polluting” the global namespace with a random `operator+` for everything — it’s tied specifically to `math::Complex`.

- Clients can’t add new members to a class.
    
- But they _can_ add new non-member functions in the right namespace.
    
- C++ overload resolution ensures the right function is picked, so there’s no global mess.
    
- This is why we prefer to keep things like `operator+`, `operator==`, etc. as **non-members** — they can be added by clients, not only by maintainers.


"Putting this all together, we conclude that a class should aim to provide a minimal public interface that provides sufficient access functions to manipulate the type while preserving class invariants, and leave the clients and other libraries etc to augment the class with non member functions as needed."


# so for operator +=: what are the choices ?

## 1) make data members public -why this is badd

`struct Complex { public: double real, imag; };`

pro: Easy to write += anywhere.
**issues** :
 - Breaks encapsulation. You’re locked into the Cartesian layout; if you later switch to polar (r, θ), all client code that touched real/imag breaks.

- Invariants are hard to enforce.

## 2) Make `operator+=` a friend free function

```cpp
struct Complex {
private:
  double real, imag;
  friend Complex& operator+=(Complex& lhs, const Complex& rhs);
};
```

pro: Keeps members private, `+=` can still access internals.

**issues:**
- **Tight coupling** (friend depends on representation).
- **Kills implicit conversion on the first argument**:
     the signature needs  
`Complex& lhs` (non-const lvalue ref, because we mutate). You can’t bind a temporary to a non-const lvalue ref, so something like `2.0 += a` (if you had such a thing) or any case where the **lhs** would need to be implicitly constructed **won’t work**. More generally, you lose the “coercion symmetry” you get with non-mutating, non-member binary ops.


## First, what does the signature look like?

If `operator+=` is a **friend free function**, it must take the left-hand side (`lhs`) by **non-const reference** (because `+=` mutates it):

`friend Complex& operator+=(Complex& lhs, const Complex& rhs);`

Notice:

- `lhs` = `Complex&` (a non-const lvalue reference).
    
- `rhs` = `const Complex&`.
## Why does this kill coercion for `lhs`?

Because in C++:

- You can bind a **parameter** (`rhs`) to a temporary, so coercion works fine there.
    
- But you **cannot bind a non-const lvalue reference** (`Complex&`) to a temporary.
    

That means you can’t write:

`2.0 += a;   // try to make lhs from 2.0`

Why?

1. `2.0` is a `double`.
    
2. Compiler _could_ convert `2.0` into a `Complex(2.0)`.
    
3. But that would produce a **temporary Complex** object.
    
4. And you cannot bind a temporary to `Complex& lhs`.
    

So the call fails.

## Compare with the `rhs` (second argument)

`a += 2.0;`

This works because:

- `rhs` is taken as `const Complex&`.
    
- `2.0` gets implicitly converted into a temporary `Complex(2.0)`.
    
- A `const&` **can bind to a temporary**, so it’s allowed.

So symmetry is broken: the `rhs` can benefit from coercion, but the `lhs` cannot.

**basics**: 
- **A non-const lvalue reference (`T&`) cannot bind to a temporary object.**  
 -  **A const lvalue reference (`const T&`) _can_ bind to a temporary.**


more explanation:


- A **non-const lvalue reference (`T&`)** cannot bind to a temporary.
    ```cpp
    
    void f(int& x) {} 
    f(5);   // error
    
    ```
     
    
    Because `f` could modify `5` — but `5` isn’t a real variable, it’s just a temporary.
    
- A **const lvalue reference (`const T&`)** _can_ bind to a temporary.
    
    ```cpp
    void g(const int& x) {}
    g(5);   // ok`
     ```
    
    Why? Because the reference is `const`, so you’re not allowed to modify the temporary. It’s safe.
### 3) Make `operator+=` a **member**

```cpp
struct Complex 
{   
Complex& operator+=(const Complex& rhs) 
  {     
    // mutate *this using internals safely     
    return *this;   
  } 
};
```


- Full access to internals **inside** the class (no friend leakage).
    
- Keeps encapsulation; you’re free to change representation later.
    
-  Natural for a mutating operation (it modifies `*this`).
    
- As always with members: implicit conversion applies to **parameters** (rhs), not to `*this` (lhs). That’s fine here; `+=` is inherently about mutating an existing `Complex` on the left.
    


### And then: make `operator+` a non-member inline wrapper around `+=`


- **Semantic consistency**
    
-  **Coercion symmetry**
    
-  Minimal member interface; clients can add more free ops without touching the class.
    

---

# summary
- `+=` mutates the object → make it a **member** (encapsulation, safe access, future-proof representation).
    
- `+` doesn’t need internals → make it a **non-member** that calls `+=` (consistency + symmetric conversions).
    
- Avoid `friend` unless there’s a compelling reason (it couples external code to your internals and, for mutating ops, often blocks useful implicit conversions on the lhs).



- `+=` mutates → member.
    
- `+` non-mutating → free wrapper.
    
- Non-const refs don’t bind to temporaries.
    
- Friends couple code tightly, so avoid unless needed.



why we use const reference lhs for += and copy by value lhs for +?

+= mutate the object
and + :

- **Purpose**: Non-mutating, returns a new sum.
    
- **So signature**:

```cpp
inline Complex operator+(Complex lhs, const Complex& rhs) {
    lhs += rhs; // mutate the copy
    return lhs; // return new object
}

```

- - Take `lhs` **by value** → makes a copy of the left operand.
        
    - Safe to mutate this local copy.
        
    - Return it → gives the caller a new value, leaves originals unchanged.
So the **pattern** is:

- **Mutating operator (like `+=`)** → LHS must be a **non-const reference**.
    
- **Non-mutating operator (like `+`)** → LHS should be passed **by value**, mutated locally, and returned.


## random questions to check understnding:

- **Why `+=` as member, `+` as non-member?**  
    `+=` mutates the left operand, so it needs direct access to `*this` → member function returning `T&` for chaining. `+` is non-mutating; implement it as a free function taking LHS by value, then do `lhs += rhs` and return, which preserves symmetry of implicit conversions and guarantees consistent semantics.
    
- **Why avoid friends?**  
    Friends depend on your representation and bypass encapsulation, creating tight coupling. Prefer members for internal mutation and free functions that use the public interface; only use friends when you truly need access (e.g., performance or streaming).
    
- **Implicit conversions & symmetry**  
    Member `operator+` allows conversion on the **rhs** only; free `operator+` allows conversions on **both operands**, enabling `a + 2.0` and `2.0 + a` without extra overloads.

- **Why `operator+=` isn’t a free function by value**
     `+=` must **mutate** the original LHS. If you take LHS by value, you mutate a copy and the original doesn’t change → **wrong semantics**
- **Why `operator+` takes LHS by value**

     `+` is **non-mutating**, so make a copy of LHS up front, `lhs += rhs`, return the copy. This also enables copy-elision/move and keeps a single implementation of addition logic.
 - **ADL (Argument-Dependent Lookup) nuance**

    To have your free `operator+` found without qualification, define it in the **same namespace as the type** (not necessarily the global namespace). This is what avoids “polluting” global scope and lets ADL find the right overload.
           Pattern options:
    - **Out-of-class non-friend** in the type’s namespace (preferred when public interface suffices).
