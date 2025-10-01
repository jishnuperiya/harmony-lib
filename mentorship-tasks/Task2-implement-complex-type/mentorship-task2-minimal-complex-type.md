- **Task Given:** Implement a user-defined `complex` type with explicit **special member functions**.  
- **Focus:**  
- **Date:** Sept 2025  

**Goal:** Understand the semantics of each SMF, when the compiler calls them implicitly, how to declare them manually, and what the compiler does if you don’t.

---

## Exercise 1 – Minimal `complex` struct

### What I Did
- Defined a `struct Complex` with two private members:
    
    `double real_; double imag_;`
    
- Explicitly wrote out the following special member functions:
    
    - **Default constructor** → initializes `real_` and `imag_` to `0.0`.
        
    - **Non-default constructor** → takes two `double`s and sets `real_`, `imag_`.
        
    - **Copy constructor** → constructs a new `Complex` from another `Complex`.
        
    - **Copy assignment operator** → assigns values from one `Complex` to an existing one (with self-assignment check).
        
    - **Destructor** → prints a message so I can see when objects are destroyed.
        
- Added `std::cout` messages inside each function to observe when they’re called.
    
- Wrote a small `main.cpp` driver to test:
    
    - Default construction
        
    - Non-default construction
        
    - Copy construction
        
    - Copy assignment
        
    - Passing `Complex` by value
        
    - Returning `Complex` by value

---

### What I Learned

#### General

- Special member functions (SMFs) are **functions the compiler may generate for you**:
    
    - Default ctor
        
    - Copy ctor
        
    - Copy assignment
        
    - Move ctor
        
    - Move assignment
        
    - Destructor
        
- They form the _fundamental functionality_ of a class: construction, copy/move semantics, assignment, cleanup.
    
- Rules:
    
    - **Rule of 0**: prefer no explicit SMFs when members handle themselves.
        
    - **Rule of 3**: traditionally, if you define copy ctor, copy assignment, or dtor, define all three.
        
    - **Rule of 5**: modern C++ — includes move ctor and move assignment.
        
    - **Rule of 6**: same as Rule of 5, but also counting the default ctor.
        
---
#### Default constructor

- **Semantics**: constructs a new object without arguments.
    
- **When invoked**: `Complex a;` or `Complex a{};`.
    
- **Manual declaration**:
    
    `Complex();`
    
- **Compiler behavior**:
    
    - Generated if no other constructor is declared _and_ all members are default-constructible.
        
    - Disabled if another constructor exists or a member lacks a default ctor.
        
- **Observation**:
    
    - `Complex a;` leaves fundamental members uninitialized (garbage).
        
    - `Complex a{};` value-initializes → zeroes fundamentals and calls default ctors of members.
        
- **Guideline**: prefer `= default` instead of writing an empty ctor; prefer `{}` initialization.
    
- **Trap**: avoid vexing parse — `Complex a();` declares a function, not an object.
    

---

#### Destructor

- **Semantics**: cleans up object state at end of lifetime.
    
- **When invoked**: scope exit, `delete`, container element removal.
    
- **Manual declaration**:
    
    `~Complex();`
    
- **Compiler behavior**:
    
    - Always generates one if you don’t.
        
    - Generated dtor calls member dtors for class types; does nothing for fundamentals.
        
- **Observation**:
    
    - For `std::string`, dtor releases memory automatically.
        
    - For raw pointers (`Resource*`), user must release resources manually.
        
- **Guideline**: only define when owning resources (RAII). Never write an empty dtor.
    

---

#### Copy constructor

- **Semantics**: constructs a new object as a copy of an existing one.
    
- **When invoked**:
    
    - Initialization: `Complex c = b;`
        
    - Pass-by-value: `foo(b)`
        
    - Return-by-value (if move not available).
        
- **Manual declaration**:
    
    `Complex(const Complex& other);`
    
- **Compiler behavior**:
    
    - Generated if not declared, unless move operations exist or a member is non-copyable.
        
    - Performs memberwise copy (shallow for pointers).
        
- **Observation**: distinct from assignment: it runs at object _creation_.
    
- **Guideline**: provide explicit copy if shallow copy is unsafe (e.g. owning raw pointer).
    

---

#### Copy assignment operator

- **Semantics**: replaces the state of an existing object with another.
    
- **When invoked**: `a = b;`.
    
- **Manual declaration**:
    
    `Complex& operator=(const Complex& other);`
    
- **Compiler behavior**:
    
    - Generated if not declared, unless move operations exist or a member is non-assignable.
        
    - Performs memberwise assignment.
        
- **Observation**:
    
    - Must handle self-assignment safely.
        
    - Different from copy ctor: works on an _already existing_ object.
        

---

#### Move operations (to learn later)


---

### Big Picture Takeaway

