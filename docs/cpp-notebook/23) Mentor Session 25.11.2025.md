
# Move Semantics (crashcourse)

- deep copying has cost
- it just transfer ownership

- x  (move)--> y
- y has the former stage of x
- x is in *moved-from* state now
- if you accidentally use a *moved-from* x, you invite disaster
- you specify how objects move with *copy ctor* and *copy assignment*

## value categories
- every expression  has 2 important characteristics - it's **type** and **value category**
- a value category describe what kind of operations are valid for this expression

- l value is anything that has a name and r value is anything that is not an lvalue
```cpp
SimpleString a{ 50 };
SimpleStringOwner b{ a }; // a is an lvalue
SimpleStringOwner c{ SimpleString{ 50 } }; // SimpleString{ 50 } is an rvalue
```

## lvalue and rvalue references
- you can communicate to the compiler that a function takes an l value or r values using *lvalue reference* and *rvalue reference*
- function can take a lvalue reference using **&** and r value reference using **&&**

compiler does excellent job in determining whether an expression is an l value or r value:

```cpp
void ref_type(int &x) { 
printf("lvalue reference %d\n", x);
}

void ref_type(int &&x) { 
printf("rvalue reference %d\n", x);
}

int main() {
auto x = 1;
ref_type(x); 
ref_type(2); 
ref_type(x + 2); 
}

output:
lvalue reference 1 
rvalue reference 2 
rvalue reference 3
```
## std::move function

- you can cast an lvalue reference to an r value reference using std::move
- c++ commitee should have named std::move as std::rvalue.
- remember: if you have l value at hand - moving is suppressed & if you r value at hand - moving is enabled

# Move Semantics (Mentorship notes)
```cpp
6   std::string foo(std::string x)
7   {
8       return x + "foo";
9       // return std::string( std::operator+(x, "foo's") / *std::string &&* / ); // move semantics
10  }

12  void bar(std::string x)
13  {
14      foo(x + "foo");
15  }
```


- x+"foo" is an r value
- std::operator+ in string class:
```cpp
std::string operator+(const std::string& lhs, const char* rhs) {
    std::string result = lhs; // start with the left side
    result.append(rhs);       // append the right side
    return result;            // returns the NEW object by value
}
```

- the operator+ (a non member func) returns a value.
- this is an r value
- the compiler sees this is an r value and flags it as r value and can search for a constructor which takes an r value.
and ofcousrse the std::string implementation has a contructor that takes an r value

```cpp

T::T(const T& r)
  : m_rep{r. m_rep}
{ // and deep copy here}

T::T(      T&& r_value)
  : m_rep{r_value.m_rep}
{
r_value.mrep = nullptr; // leave the source object in a well defined state
}

```

- r_value vs r value reference 
	- **r value** : the temp object
	- r value is safely **bound** to the parameter of the function which works on the r value , and the parameter of that function is the **rvalue reference**

##  std::move function
```cpp
std::string foo(std::string x)
{
return x + "foo"s;
}

void bar(std::string x)
{
std::string y = "fddf";
foo(y);
}
```

- in this code example, the in the function bar, after calling the foo() function, y is no longer necessary, which means, we could steal the resource from y instead of copying it.

- since y is a l value, the compiler will call copy construction when passed into the foo function. but as a programmer we know better:
  why not cast the y to a r value? then the compiler will call the corresponding move constructor in string class right?
  
  means i could do:

```cpp
foo(static_cast<std::string&&>(y))
```

this idiom was very useful enough to introduce the move!

```cpp
template<class type>
constexpr type&& std::move(type& mr)
{
return static_cast<type&&>(mr);
}
```

- if y was const, the move doesnt work: for move operation we need mutable variable

**Do not use a moved-from object in client logic.**

The moved-from state is intended to be used only for:

- destruction
    
- reassignment
    
- calling functions with **no preconditions**
    

Most types **do NOT** provide guarantees about what the object contains after being moved.

The standard library gives `std::string` stronger guarantees:

After being moved from:

- `s.size()` is valid
    
- `s.empty()` is valid
    

And you may call other functions that **have no preconditions** (e.g., `clear()`).  
But this is type-specific — you **must not** rely on it in general code.

Write code assuming that a moved-from object is only good for:

- destruction
    
- reassignment
    
- calling methods that require no invariants
    

Relying on a specific moved-from state is fragile


# Templates

topics:
- template function
- template class
- template alias
- template member function
- template value
- template specialization
- template partial specialization
- template instantiation
- template explicit instantiation
- overloading function templates
- forwarding references
- perfect forwarding
- template and meta programming


## template function

### Polymorphism

**polymorphism allow the same interface to behave differently depending on the argument types**

there are 2 kinds:
- ad-hoc polymorphism -> function overloads
- parametric polymorphism -> templates
### 1. Ad-hoc polymorphism (Function overloading)

adhoc means special case, custom.

example:

```cpp
int add(int a, int b);
double add(double a, double b);
std::string add(const std::string&, const std::string&);
```

each overload has a different implementaiton

compiler picks on based:
- argument types
- conversions
- overload resolution rules
**bad practice** : when each overload does something completely different

### 2. Parametric polymorphism (Templates)

example:

```cpp
template<typename T>
T add(T a, T b) { return a + b; }
```

- compiler generate seperate functions for each type used
- template functions are way of telling the compiler: for any type you can use my body as a rule how to generate fucntion for the given type


**Overloading** = you write MANY versions manually.                                    -> special-case behaviour
**Templates** = you write ONE version, compiler generates needed variants. -> uniform behaviour


### Templates have **two layers**:
A C++ template has **two meanings at the same time**:
1. **Operational semantics** → what the compiler _does_ with the template
2. **Logical semantics** → what the template _means_ as a general function for _any type_

**Layer 1: Operational Semantics (compiler behaviour)**
this answers: "what happens inside the compiler when you write a template?"

key ideas:
 - template is not a funtion
 - it is a pattern for generating a fn
 - a real fn only exist after instatiation
eg.
```cpp
template<typename T>
T square(T x) {
    return x * x;
}

```

this template is a recipie.
nothing is generated yet.

but when you call:

```cpp
square(3);
```

the compiler now generates:

```cpp
square<int>(int x) { return x * x; }
```
this process of template instantiation is the operational semantics.

**Layer 2: logical semantics (conceptual meaning)**

answers the question: "what does the function mean logicall for any type T?"

we interpret the template as a generic rule:

```bash
For any type T that supports operator*:
    square returns x * x
```

logical semantics: general rule described by the template for all the valid types T

**note on template funtions**

look at this template funtion:
```cpp
template<typename T>
size_t size_of_native_array(size_t n)
{
 return n* sizeof(T);
}
```

this template funtion doesnt take parameter T as argument.
so when calling this function , we can't rely on type inference anymore:

```cpp
size_t n  = size_of_native_array(13);  // compiler cant instantiate 
```

so you have to do this:

```cpp
size_t n = size_of_native_array<double>(13);
```

### Note:
Before templates existed, C++ programmers often used **preprocessor macros** to write “generic” code.  
```cpp
#define SQUARE(x) ((x) * (x))
```
But macros are unsafe: they do simple text substitution, have no type checking, cannot be debugged, and can even cause **undefined behavior** (e.g., `SQUARE(++i)` becomes `++i * ++i`).

Modern C++ replaces macros with **function templates** and **constexpr variables**, which are type-safe, scoped, debuggable, and evaluate arguments only once.  
Templates let you define a single function that works for any type.


**abbreviated function template** (c++20)
instead of writing:
```cpp
template<typename T>
T square(T x) {
    return x * x;
}
```
you can write:
```cpp
auto square(auto x) {
    return x * x;
}
```
- used for tiny generic functions
## Template Class

remember, what are the 3 things that you can put in a class?
- special member functions
- ordinary member functions
- data

lets write the simplest vector class having a data and ordinary member function:

```cpp
class vector
{
public:
size_t size() const { return size_;};

private:
size_t size_;
double* x_;
}
```
but then you realize you can have a vector of anything.

```cpp
template<scalar_t>
class vector
{
public:
size_t size() const {return size_;};

private:
size_t size_;
scalar_t* x_;
}
```


**template class** : Takes a type and produces a type
**template function** : Takes a function and produce another function instance

## Template Variables

- for producing a value depending on T
- produces a compile time constant

```cpp
template<typename T>
size_t foo = sizeof(T) * 2;
```

all these are created at compile time:

```cpp
foo<int>    → sizeof(int) * 2 → 8
foo<double> → sizeof(double) * 2 → 16
foo<char>   → sizeof(char) * 2 → 2
```

it produces a **constant with internal linkage for each type T**


## Full Template specialization
A **full specialization** replaces the entire implementation of a primary template **for one specific type**.
You use this when:
- the general template works for most types
- **but one specific type needs a completely different representation or behavior**

a template defines a general rule for all types T:

```cpp
template<typename T>
class vector {
    // general implementation
};
```


But sometimes, for a **specific type**, the general implementation is:
- slow
- inefficient
- impossible
- or needs special logic
So C++ allows you to write a **special version** of the template for a specific type:

```cpp
template<>
class vector<bool> {
    // special implementation just for bool
};
```

this is called **full template specialization**


**why we need full template specialization?**

Because sometimes, the “normal” implementation is not the best for some types.

Example: storing `bool` efficiently.

Normally, vector stores elements like this:

`T T T T T ...`

Each `T` is stored separately in memory.

But storing bools like this is VERY wasteful:

- `bool` normally takes **1 byte**
    
- but it only needs **1 bit**
    

So vector<bool> has a special implementation that packs bits tightly:

`0101101010010110...`

Instead of storing:

`true  false  true  true  false ...`

as separate bytes.

This saves **8× memory**.

### Vector example (simplified)

General vector:
```cpp
template<typename T>
class vector {
    T* data_;
    size_t size_;
};
```
Specialized version for bool:

```cpp
template<>
class vector<bool> {
    unsigned char* bits_;
    size_t size_;
};

```

### Note: Template specialization can break uniformity

Template specialization is powerful, but dangerous, because:

- your special case must behave **almost** like the primary template
    
- but small differences cause confusion
    

Example:

```cpp
vector<bool> v;
bool& b = v[0];   // error — cannot get reference
```
Because the element is packed inside a bit, not a real bool.

So the operator[] returns a **proxy object**, not a bool reference.


primary template:
```cpp
template<typename T>
struct vector
{
    size_t size() const;

    T operator[](size_t i) const { return x_[i]; }

    T* x_;
};

```

This is the **general rule** for all `T`:

- store `T* x_`
    
- return `T` from `operator[]`
    

Example instantiations:

- `vector<int>`
    
- `vector<double>`
    
- `vector<std::string>`
    
- `vector<Note>`
    

All follow this implementation.

Full Specialization (for bool only):
```cpp
template<>
struct vector<bool>
{
    size_t size() const;

    bool operator[](size_t i) const { /* ??? */ }

    unsigned long* x_;
};

```
Each `unsigned long` contains 64 bits (on most platforms), so each bit represents one boolean.


and this is a completey different implmentation used only when:
vector<bool> v;


In the real `std::vector<bool>`, `operator[]` does **not** return `bool`.  
It returns a special proxy object.

Because you cannot return `bool&` (there is **no actual bool** stored anywhere!).

In your teacher's simplified example:

`bool operator[](size_t i) const { /* weird bit manipulation */ }`

This represents:

- fetch the correct bit
    
- extract it
    
- return true/false
    

But you cannot return `bool&` because the bit is not a variable.

This is why `vector<bool>` is so unpopular — it behaves differently from all other `vector<T>` types.


# ⭐ **Partial Specialization — What It Is**

**Partial specialization** lets you specialize a class template for a _family_ of types, not just one exact type.

- **Full specialization** = special case for **one exact type**  
    Example: `vector<bool>`
    
- **Partial specialization** = special case for **a pattern of types**  
    Example: “all pointers”, or “all pairs of T and U where T = int”.
    

You cannot partially specialize **function templates** (C++ forbids it).  
But you **can** partially specialize **class templates** and **variable templates**.

---

# ⭐ Simple Example

### Primary template:

`template<typename T> struct MyType {     static void info() {         std::cout << "General type\n";     } };`

### Partial specialization for pointer types:

`template<typename T> struct MyType<T*> {     static void info() {         std::cout << "Pointer type\n";     } };`

### Usage:

`MyType<int>::info();      // General type MyType<double*>::info();  // Pointer type`

---

# ⭐ Why partial specialization?

Use partial specialization when:

- You want different behavior for **groups of related types**
    
- You don’t know the exact type at compile time, but you know its pattern
    
- You want to gate code based on type categories
    

### Examples of patterns:

- “every pointer type” → `T*`
    
- “every array type” → `T[N]`
    
- “every type wrapped in std::vector” → `vector<T>`
    
- “pair where T = int” → `pair<int, U>`
    
- “every floating point type” → `std::enable_if<>` tricks




# ⭐ Real examples in the standard library

The C++ STL uses partial specialization everywhere:

### 1. `std::is_pointer<T>` works because of partial specialization:

`template<typename T> struct is_pointer : std::false_type {};  template<typename T> struct is_pointer<T*> : std::true_type {};`

### 2, `std::remove_reference<T>`, `std::tuple<Ts...>`

Many type traits rely on patterns (`T&`, `T&&`, etc.)

---

# ⭐ Partial vs Full Specialization — Summary Chart

|Feature|**Full Specialization**|**Partial Specialization**|
|---|---|---|
|Applies to|One specific type|Pattern / family of types|
|Example|`vector<bool>`|`vector<T*>`|
|Flexibility|Low|High|
|Similar to|Exact match|Pattern matching|
|Used for|One-off special cases|Generic behavior for type categories|

---

# ⭐ Perfect one-sentence definition (for notes)

> **Partial specialization** customizes a class template for a whole family of types matching a specific pattern, such as all pointers, references, or container-wrapped types.



## code partial + full

```cpp
// Primary template
template<typename T>
struct vector
{
    // general case
};

// Partial specialization for pointer types
template<typename V>
struct vector<V*>
{
    // specialized behavior for all pointer types
};

// Full specialization for int*
template<>
struct vector<int*>
{
    // completely specialized for int*
};

// Full specialization for bool
template<>
struct vector<bool>
{
    // completely specialized for bool
};

```


# Next week Task

# **1. BEGIN with the simple version**

Using the raw STL:

```cpp
using notes_t = std::set<note>;

```
Practice:

- adding notes
    
- removing notes
    
- looping through notes
    
- using `std::set_intersection`
    
- using `std::set_union`
    
- using `.begin()`, `.end()`, `.find()`, `.insert()`, `.erase()`
    

**Goal:** Understand how set operations behave on musical notes.


# **2. THEN replace `notes_t` with your own value type**

Create:

```cpp
struct notes {
    // later: bit pattern or int-backed representation
};

```

BUT it must behave exactly like `std::set<note>` **from the outside**.

He said:

> “We will end up with a class that is _isomorphic_.”

This means:

- same public behavior
    
- different internal representation

# **Your final `notes` class must have:**

### ✔️ Only the obvious essential interface (NOT the entire std::set API!)

He wants you to **avoid re-implementing all of std::set**.

Take only:

### **Special Member Functions**

- ctor
    
- copy ctor
    
- move ctor
    
- dtor
    
- copy/move assignment
    

(because every value type must have them)

### **Easy member functions**

- `begin()`, `end()` (iterators)
    
- `find(note)`
    
- `contains(note)`
    
- `insert(note)`
    
- `erase(note)`
    
- `size()`, `empty()`
    

That’s _all_.

He said:

> “set has a huge interface. Don’t take all. Take only obvious things.”


# **4. IMPORTANT: `std::set_intersection` must work on your class**

He said:

> “intersection takes iterators — polymorphic, works on any type with iterators.”

So your class MUST provide:

```cpp
iterator begin();
iterator end();

```

that behave exactly like `std::set<note>` iterators.

Otherwise:

```cpp
notes a, b, c;
std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), ...);

```

WILL NOT WORK.

This is why the iterators are necessary

# **5. Two possible internal representations**

He explicitly told you:

1. **bit pattern** (12 bits representing pitch classes)
    
    - fast
        
    - compact
        
    - trivial copy/move
        
    - perfect for music theory sets
        
2. **16-byte integer (128-bit)**
    
    - store 12 bits in low part
        
    - trivial copy/move
        

He said:

> “resulting class has trivial copy and move”

Meaning:

- no dynamic memory
    
- no pointers
    
- a pure value type
    
- very cheap to pass around

# **6. Step-by-step Implementation Plan (Jonathan’s expectation)**

### **Phase 1 — Simple version (std::set<note>)**

You already did:

```cpp
notes_t cmaj = { note("C"), note("E"), note("G") };
notes_t cmin = { note("C"), note("Eb"), note("G") };

std::set_intersection(...);
std::set_union(...);

```

Write a **test** for this.

---

### **Phase 2 — Your own `notes` type (set wrapper)**

Implement:

```cpp
struct notes {
    std::set<note> data_;

    using iterator = std::set<note>::iterator;
    using const_iterator = std::set<note>::const_iterator;

    iterator begin() { return data_.begin(); }
    iterator end()   { return data_.end(); }

    iterator find(const note& n) { return data_.find(n); }
    bool contains(const note& n) const { return data_.find(n) != data_.end(); }

    void insert(const note& n) { data_.insert(n); }
    void erase(const note& n)  { data_.erase(n); }

    // special member functions
};
```

This is a **wrapper**.

He said:

> “so that above code works”

Meaning:  
The code using `std::set` should work unchanged when replaced by `notes`.

Write test code demonstrating this.


### **Phase 3 — Replace internal set with bit pattern**

Once tests pass with the wrapper version, **remove std::set** and replace with:

```cpp
uint16_t bits_; // only 12 needed
```

Then:

- `insert()` sets a bit
    
- `erase()` clears a bit
    
- `contains()` tests a bit
    
- iterators walk through bits 0–11 and yield `note` objects
    

He mentioned:

> “you can use a bit pattern”  
> “or a 16-byte integer”  
> “ending class has trivial copy and move”

Because this is the real value-type representation.

---

# ⭐ **7. Write test cases**

He said:

> “write a test case”

Meaning:

- test adding
    
- test removing
    
- test iteration
    
- test intersection
    
- test union
    
- test contains
    
- test find
    

Both with the wrapper version _and_ the final version.

---

# ⭐ Final Reconstructed Assignment (summary)

Here is the **exact assignment** in one clear list:

---

# ✔️ **Jonathan’s Task (Full)**

### **Step 1 — Using `using notes_t = std::set<note>`**

- add/remove notes
    
- iterate
    
- implement contains/find
    
- use `std::set_intersection` and `set_union`
    
- write test code
    

---

### **Step 2 — Create your own `notes` wrapper class (using std::set internally)**

- same interface as before
    
- implement only essential functions
    
- must work with `std::set_intersection`
    
- write test code to confirm behavior
    

---

### **Step 3 — Replace internal storage with a bit pattern**

- eliminate std::set
    
- implement bit-based iterator
    
- trivial copy/move
    
- same interface
    
- must still work with `std::set_intersection`
    
- write final test code
    

---

# ⭐ If you want:

I can now generate:

### ✔️ Full starter code (wrapper version)

### ✔️ Full bit-pattern version

### ✔️ Iterator implementation

### ✔️ Test program

### ✔️ Doxygen comments

### ✔️ Harmony-style header file

### ✔️ CMake snippet

Just say: **“Give me the full code for version 1”** or **“Give me the bit-pattern final version”**.