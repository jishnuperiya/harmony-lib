- **Task Given:** Implement a user-defined string type with explicit **special member functions**.  
- **Focus:**  
- **Date:** october 2025  

**Goal:** Implement string type with explicit special member functions and understand how it differs form the previous complex type implementation (task2)

---

## Exercise 1 – Value type experiment

### What I Did
- Defined a minimal struct:
```cpp
struct my_string {
    char* data;
};
```

- Passed onto a function (in the value-type-experiment branch) to observe the value behaviour:

```cpp
using value = my_string;

void do_nothing(value a, value b) {}

void playing_with_value_type(value x, value y) {
    std::cout << "string 1 value is: " << x.data << '\n';
    std::cout << "string 2 value is: " << y.data << '\n';

    // 1) Pass by value → invokes copy ctor (default)
    do_nothing(x, y);

    // 2) Copy assignment operator (default)
    x = y;
    std::cout << "string 1 after x = y → " << x.data << '\n';

    // 3) Copy construction (default)
    value z = x;
    std::cout << "z (copy of x) → " << z.data << '\n';

    // 4) Show addresses of pointers
    std::cout << "x.data address: " << static_cast<void*>(x.data) << '\n';
    std::cout << "z.data address: " << static_cast<void*>(z.data) << '\n';
}

```
---
### What I Learned

#### General

the sample output looked like this:

```cpp
string 1 value is: hello
string 2 value is: world
string 1 after x = y → world
z (copy of x) → world
x.data address: 0x601fdeb70019
z.data address: 0x601fdeb70019
```

- The compiler generated special member functions 'kind of worked'. 
- Copy constructor, Copy assignment operator etc seemed to work at first 
- But there is small twist: To construct a data member (in a user-defined type), the constructor will do a bitwise copy. 
- And in this case the  **data** member in the my_string struct is holding the value something like  **0x601fdeb70019** (which actually points to a character array in a contiguous block of memory). And the compiler just bitwise copy this value to the other object when you do the copy assignment or copy construction. 
  
for example, in this case:  
  ```
  value z = x;
  ```
the value z is an object of type my_string with a member which has value **0x601fdeb70019** and the value x is also an  object of type my_string with a member which has the same value **0x601fdeb70019** since the members were bitwise copied by the compiler.

means it both points to the same contiguous block of memory. 

**insight:**
When the compiler-generated copy constructor or assignment operator runs, it just **copies this 8-byte pointer value** from one object to another. it doesn’t copy the actual characters.


## Exercise 2– Implementing explicit special member functions for my_string type

**Goal**: improve the previously defined my_string type such that, upon copying the object, the value itself is copied. not just the pointer

### What I Did

- Defined a minimal struct:

```cpp
struct my_string {
    char* data;
    unsigned long long size;
};
```

-  implemented the constructor, copy ctor, copy assignment operator and the destructor

---

### What I Learned

#### General

- string literals are of type const char[]
- string literals (and arrays) decays to pointer when passed to a function. 
  `string b("hello");` -> the constructor is receiving a const char*
- when you de-reference a null pointer, you get segfault error- so always check if the pointer is pointing to a valid memory location.
---

### Default Constructor

- **Semantics**: creates an empty string object with `data_ = nullptr` and `length_ = 0`.
    
- **When invoked**:  
    `string a;`
    
- **Behavior**:
    
    - Initializes members safely to `nullptr` and `0`.
        
    - Prevents undefined behavior if object used before assignment.

### Parameterized Constructor (`const char*`)

- **Semantics**: constructs a new string object from a C-style string.
    
- **When invoked**:  
    `string b("hello");`
- **steps i did:**
- Calls `my_strlen()` to measure the length.
- Allocates new heap memory block (`new char[length_ + 1]`).
- Copies characters using `memcpy` 
- Appends null terminator (`'\0'`).
learnings:
- use memcpy to copy the contents the pointer points to. not the pointer
- string literals are constant(thats why const char*)
### Copy Constructor

- **Semantics**: creates a new object as a copy of another
    
- **When invoked**:
    - `string b = a;`
    - Passing by value or returning by value.
- **steps i did:**
    1. Copies the length from `other`.
    2. Allocates new memory on the heap.
    3. Copies the content (`memcpy`).
- **why is it needed**
when you allow the compiler to generate a copy ctor for you, it does a bitwise copy and copies the pointer value for you. then you end up with 2 objects having same pointer value -> 2 objects pointing to same block of memory. what happens when you delete one object?

### Copy Assignment Operator

- **Semantics**: replaces the contents of an existing string with another string’s data.
    
- **When invoked**:  
    `a = b;`
- **steps i did**
- pretty similar except you have to free up the existing data before copying
- **why you need it?**
- same reason as above
### Destructor
- **Semantics**: releases heap-allocated memory when the object’s lifetime ends.
- **When invoked**:
    - Automatically at scope exit, or when `delete` is called(if you make the string object on heap)
- **steps i did**
- delete[] data_; -> since data_represents an array
