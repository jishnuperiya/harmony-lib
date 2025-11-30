- **Task Given:** Implement a user-defined string type with explicit **special member functions**.  
- **Focus:**  Deep copy, ownership semantics, and resource safety.
- **Date:** october 2025  

**Goal:** Implement a custom string class that manages its own heap-allocated memory safely, understand how compiler-generated SMFs behave for pointer members, and see how this differs from the previous `Complex` (pure value type) implementation.

---

## Exercise 1 – Value type experiment (Shallow copy experiment)

### What I Did
- Defined a minimal struct:
```cpp
struct my_string {
    char* data;
};
```

I tested copying, assigning, and passing this struct by value to see how the compiler-generated SMFs behave when a type owns a pointer.

```cpp
using value = my_string;

void do_nothing(value a, value b) {}

void playing_with_value_type(value x, value y) {
    std::cout << "string 1 value is: " << x.data << '\n';
    std::cout << "string 2 value is: " << y.data << '\n';

    do_nothing(x, y);             // copy ctor (default)
    x = y;                        // copy assignment (default)
    value z = x;                  // copy construction (default)

    std::cout << "x.data: " << static_cast<void*>(x.data) << '\n';
    std::cout << "z.data: " << static_cast<void*>(z.data) << '\n';
}


```
---
### What I Observed

```cpp
string 1 value is: hello
string 2 value is: world
string 1 after x = y → world
z (copy of x) → world
x.data address: 0x601fdeb70019
z.data address: 0x601fdeb70019

```

Both `x` and `z` ended up pointing to the same address — confirming that the compiler-generated SMFs performed **bitwise copies**.  
The underlying characters weren’t duplicated, only the pointer value was copied.

### Insight

Default SMFs **“work”** only when members are true values.  
For pointer members, they just copy the address, not the data-> causing aliasing.  
Both objects now think they own the same heap block → **double-free risk** when destructors run.

This experiment shows _why_ defining explicit SMFs is critical for resource-owning types

## Exercise 2 – Implementing Explicit SMFs for `my_string`

**Goal**: Redesign the `string` class so that:

- Each instance owns its **own heap block**.
    
- Copies duplicate the characters, not just the pointer.
    
- The destructor safely releases the owned block.

### What I Did


```cpp
struct string {
    char* data_ = nullptr;
    std::size_t length_ = 0;

public:
    string(const char* s = "");             // param constructor
    string(const string& other);            // copy ctor
    string& operator=(const string& other); // copy assignment
    ~string();                              // destructor
};

```

---

### What I Learned

#### General

- String literals are of type `const char[]` and decay to `const char*`.
    
- Always check for `nullptr` before dereferencing.
    
- `std::strcpy` is safer than `memcpy` for text since it also handles the null terminator.
    
- Prefer `std::size_t` over `unsigned long long` for size — it’s portable and matches the STL.

---

### Default / Parameterized Constructor
```cpp
string::string(const char* s) 
{
  length_ = std::strlen(s);
  data_ = new char[length_ + 1];
  std::strcpy(data_, s);
}
```

- **Default argument:** `""` instead of `nullptr`, ensuring a valid empty string even when no argument is passed.
    
- **Steps:** measure length, allocate `length_ + 1`, copy content including `'\0'` (strcpy does that).
    
- **Why:** prevents crashes from dereferencing null pointers.

### Copy Constructor (Deep Copy)

```cpp
string::string(const string& other)
  : string(other.data_) // constructor chaining (delegates to main ctor)
{}
```
- **Semantics:** creates a deep copy.
    
- **Technique:** **constructor chaining (delegating constructor)** : instead of duplicating allocation/copy code, the copy constructor reuses the main constructor by passing `other.data_`.
    
- **Benefit:** avoids code duplication, improves maintainability.
    
- **Learning:** use initializer list to call another constructor of the same class.

### Copy Assignment Operator
```cpp
string& string::operator=(const string& other) 
{
    if (this != &other) {
        delete[] data_;                // release existing memory
        length_ = other.length_;
        data_ = new char[length_ + 1];
        std::strcpy(data_, other.data_);
    }
    return *this;
}

```

- **Semantics:** replaces current content with a copy of `other`.
    
- **Steps:**
    
    1. Check for self-assignment.
        
    2. Free old buffer.
        
    3. Allocate new block and copy text.
        
- **Mentor note:** prefer `std::strcpy` over `memcpy` for safety.
    
- this ensures that each string manages its own heap resource exclusively . no shared ownership.
### Destructor

```cpp
string::~string() 
{
  delete[] data_;
}

```
- **Semantics**: releases heap-allocated memory when the object’s lifetime ends.

## Mentor Feedback Reflection

Jonathan emphasized that while my explanation of _how_ SMFs work was accurate, the **core design issue** is _ownership_.
```
“When a class holds a pointer to a resource, the fundamental question is:  
 Who owns the resource?”
```

In this string class:

- Each instance **owns its own memory**.
    
- Copy operations **allocate new blocks** and copy data.
    
- The destructor **always deletes** its block.
    
- The assignment operator **guards against self-assignment**.
## Final Takeaways

- Compiler-generated SMFs are fine for _pure value types_, but not for _resource-owning types_.
    
- Always start by answering: **“Who owns the resource?”**
    
- Constructor chaining simplifies code and reduces maintenance burden.
    
- `std::size_t`, `""` defaults, and standard library functions (`std::strcpy`, `std::strlen`) make code safer and more idiomatic.