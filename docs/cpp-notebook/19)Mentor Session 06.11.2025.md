****
### static member functions

- nomral member functions has a this pointer
- static member fuctions doesnt need it

static member function belongs to the class. not to any object

- static functions are just normal global functions that happen to live in a class's scope for organization
the key differences:
- normal member function secretly takes a this pinter and a static member function doesnt

what static functions can and cannot do:

|Action|Allowed?|Explanation|
|---|---|---|
|Access static data members|✅ Yes|They belong to the class|
|Access non-static data members|❌ No|No `this` pointer|
|Call other static functions|✅ Yes|Same scope|
|Called via object instance|✅ (but discouraged)|Prefer `ClassName::func()`|
|Access `this`|❌ No|Doesn’t exist in static context|
lern later: static member fuctions and design patterns

### member function
- a normal function with one hidden parameter (this pinter) -> passsed a pinter to the structure in memory
##### object layout in memory

```cpp
class Point {
    int x;
    int y;
public:
    void move(int dx, int dy) { x += dx; y += dy; }
};

```

and when i do :

` Point p; `

memory for p look like this:

```cpp
+-----------+-----------+
|    x      |    y      |
+-----------+-----------+

```

total 8 bytes

thats it. no function code, no vtable unless you have virtual functions

only data members occupy the object's memory

###### member fucntions dont live inside the object

member functions are shared code. sotred once in program memory (text segment)

all objects of the same class reuse that same code.

when you call :

`p.move(5,10)`

what actually happens is :

`Point::move(&p, 5, 10);`

the function get this hidden pointer to the block of memory where data member lives

to explore:
--> **what about inheritance and polymorphism then? it contains and extra vtable ptr? - learn later**
hint:
```cpp
+---------+--------------+
| vptr →  |  &vtable     |  (8 bytes on 64-bit)
+---------+--------------+
| data    |   int data   |
+---------+--------------+

```

**`vptr`** = hidden pointer to a table of virtual functions (vtable).
The **vtable** itself lives in program memory, not in the object.


example of memory size:

```
struct A
{
int a;
int b;
}

sizeof(A) -> 8 bytes
```

```
struct B
{
virtual void f();
itn a;
}

sizeof(B) -> 16 bytes (vfptr+int+padding)
```

whats not in the object:
- member functions 
- static data members
- this pointer
- vtable

summary
- only non static data member and hidden vfptr (if polymorphism is present) takes up space
- fns , static members, class defenitions live eslewhere and are shared


## C++ Notes — Scope, Storage Classes, and the Linker

## Before `main()` is called

- Before `main()` executes, the compiler and runtime automatically call the **constructors of all global/static objects** in your program.


```cpp
#include <iostream>

struct A {
    A() { std::cout << "Global A constructed\n"; }
};

A a;  // global object

int main() {
    std::cout << "Inside main\n";
}

```

output:

```cpp
Global A constructed
Inside main
```

✅ Order:

1. All **global and static** objects’ constructors run before `main()`.
    
2. Their **destructors** run _after_ `main()` exits.


|Concept|Meaning|
|---|---|
|**Scope**|_Where_ a name (variable/function/class) is visible in the code.|
|**Lifetime**|_When_ the object exists in memory (created → destroyed).|

### Storage class: _automatic_

- Variables declared inside a function (without `static`) have **automatic storage duration**.
    
- They live on the **stack**.
    
- Created when execution enters their scope, destroyed when it leaves.

example:

```cpp
void foo() {
    int x = 5;   // automatic
}  // x destroyed here

```

### File scope

- Variables or functions defined **outside any function** have **file scope** (also called _global scope_).
    
- They are visible from the point of declaration to the end of the translation unit.
    

Example:

```cpp
int g = 10;   // file scope, visible to all code below

```

### Forward declarations and scope

A **forward declaration** _makes a name visible earlier_ so that other code can refer to it, even before the full definition is known.


```cpp
struct A;   // forward declaration

void f(A* ptr);  // can use pointer/reference before full type is defined

```

struct A;   // forward declaration

void f(A* ptr);  // can use pointer/reference before full type is defined

## The Linker

After compilation, each `.cpp` file becomes an **object file (.o / .obj)** containing:

- machine code with **placeholders** for addresses,
    
- symbol tables (variable/function names),
    
- relocation info.

### The linker’s job:

- **Assign final addresses** to all global functions and variables.
    
- **Patch jump instructions**
- **Resolve external symbols** between translation units.
(the compiler writes something like “`call _foo`” with no address yet,  
and the linker later fills in the _real memory address_ of `foo`.)


#### use of static in filescope:

imagine you have 2 files:

file1.cpp
```cpp
#include <iostream>

static int x = 42;   // <-- static global
int y = 100;         // <-- normal global

void printVars() {
    std::cout << "x = " << x << ", y = " << y << '\n';
}

```

file2.cpp:

```cpp
extern int y;  // tell compiler "there is a y somewhere"
extern int x;  // try the same for x

int main() {
    printVars();
    std::cout << "y = " << y << '\n';
    std::cout << "x = " << x << '\n';   // <--- will cause linker error
}

```

step 1: compiler phase:

Each `.cpp` file is compiled _separately_ into an object file (`file1.o`, `file2.o`).

- `file1.o` has:
    
    - symbol **`x`**, but it’s **marked private** (because of `static`)
        
    - symbol **`y`**, marked **global** (exported so others can use it)
        
    - function **`printVars()`**, marked global
        
- `file2.o` has:
    
    - references to **`x`** and **`y`** (placeholders, it doesn’t know their addresses yet)

## ⚙️ Step 2: linker phase

The linker’s job is to **match** all the “names I need” with “names that exist”.

|From file2.o (needs)|Can find in file1.o?|Result|
|---|---|---|
|`y`|✅ yes, exported|link successful|
|`x`|❌ no, hidden (static)|linker error: _undefined reference to `x`_|


## 📦 What “internal linkage” really means

- Each `.cpp` (translation unit) is like its own _mini world_.
    
- `static int x;` means “this variable belongs only to this world.”
    
- Even if another file says `extern int x;`, the linker cannot connect them.
    

Whereas:

- `int y;` is **external linkage** — visible to other files.  
    The linker can match `extern int y;` across files.

