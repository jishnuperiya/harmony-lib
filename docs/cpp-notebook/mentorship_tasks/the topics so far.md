
### _Every topic, subtopic, exercise, insight, and failure mode preserved._

---

## **Week 0 — Warm-up (Sep 2025)**

### **Topic:** Value types via `int`

### **Depth:** ⭐⭐⭐

### **What we did:**

- Explored how `int` behaves as a perfect value type
    
- Assignment, copy construction, equality, truth testing
    
- Arithmetic operators: `+ - * /`
    
- Bitwise operators: `& | ^ << >>`
    
- Increment/decrement: `++x`, `x++`
    
- Destructive vs non-destructive operations
    
- Passing by value, returning by value
    

### **Key Learnings:**

- Copy constructor vs copy assignment
    
- Built-in types support extremely rich operator semantics → goal for user-defined types
    
- Truth testing is implicit for integers
    

---

## **Week 1 — Complex Number Type (Late Sep 2025)**

### **Topic:** First real value type with SMFs

### **Depth:** ⭐⭐⭐⭐⭐

### **What we did:**

- Implemented `struct complex { int real; int imaginary; }`
    
- Swapped `using value = int` → `using value = Complex`
    
- Realized many operations fail without defining operators
    

### **Learned About Special Member Functions (SMFs):**

- Default constructor
    
- Copy constructor
    
- Copy assignment
    
- Destructor
    
- When they are auto-generated
    
- When compiler deletes them
    
- Why deep copying matters
    
- What value-type semantics really mean
    

### **Key Failure / Fix:**

- `operator==` missing
    
- No arithmetic → must be implemented
    
- Truth testing missing → must provide explicit conversion
    

---

## **Week 2 — String & Ownership Concepts (Early Oct 2025)**

### **Topic:** Memory management & Rule of 3/5

### **Depth:** ⭐⭐⭐⭐⭐

### **What we did:**

- Manually implemented a small string to understand:
    
    - Dynamic allocation
        
    - Deep vs shallow copy
        
    - Move ctor and move assignment
        
    - Destructor correctness
        
- Tested all combinations of:
    
    - Assignment
        
    - Copying
        
    - Destruction
        
    - Passing by value
        

### **Key Learnings:**

- Why modern C++ prefers value types with RAII
    
- How to avoid double frees
    
- When to follow Rule of 0
    

---

## **Week 3 — Mini I/O Library + Bridge Pattern (Early Oct 2025)**

### **Topic:** `ostream` + `streambuf` + Bridge Pattern

### **Depth:** ⭐⭐⭐⭐⭐⭐ (very deep)

### **What we did:**

- Implemented:
    
    - `my_streambuf` (abstract)
        
    - `my_consolebuf`
        
    - `my_filebuf`
        
    - `my_ostream`
        
    - `operator<<` overload
        
- Rebuilt the conceptual skeleton of C++ I/O by hand
    
- Saw how abstraction (`ostream`) is separated from implementation (`streambuf`)
    
- Used composition over inheritance
    
- Understood chaining: `os << x << y << z`
    

### **Key Learnings:**

- Why `printf` is not type-safe
    
- Why operator overloading is the C++ way to extend built-in behavior
    
- Why `ostream <<` returns `ostream&`
    
- How Bridge enables:
    
    - extensibility
        
    - destination-agnostic I/O
        
    - user-defined types
        

---

## **Week 4 — Harmony Library Foundations (Mid Oct 2025)**

### **Topic:** `pitch`, `frequency`, `note`

### **Depth:** ⭐⭐⭐⭐⭐

### **What we did:**

- Implemented:
    
    - `class pitch` with semitone math
        
    - `class frequency` with Hz manipulation
        
    - `class note` with musical semantics
        
- Designed API to make calculations clean
    
- Practiced forward declarations
    
- Single header (`harmony.hpp`)
    

### **What we learned:**

- Octave equivalence:
    
    - difference modulo 12
        
    - frequency ratio = power of 2
        
- How to convert MIDI ↔ frequency
    
- How to structure a small musical domain model
    
- Designed non-mutating and mutating methods properly
    
- Why forward declarations matter
    
- When forward declarations are **not** enough (incomplete types)
    

---

## **Week 5 — Inheritance, Vtables, Multiple Inheritance (Late Oct 2025)**

### **Topic:** Class design + polymorphism rules

### **Depth:** ⭐⭐⭐⭐⭐⭐

### **What we did:**

- Understood:
    
    - When to use inheritance (only for _is-a_)
        
    - Pure virtual classes → interfaces
        
    - Why interfaces shouldn’t have data members
        
    - Vtable construction patterns
        
    - Object layout under inheritance
        
    - Multiple inheritance:
        
        - safe for interfaces
            
        - dangerous for classes with data
            
    - Diamond problem
        
    - Virtual inheritance
        

### **C++ iostream Special Case:**

- `iostream` inherits from both `istream` and `ostream`
    
- Both share `ios` via **virtual inheritance**
    
- Why it prevents double-copy of base class
    
- Why both talk to same `ios` pointer
    

### **Decorator Pattern:**

- How you can chain streams
    
- Why it’s “a chain of bridges”
    

---

## **Week 6 — Chords, Templates, Voicing (Early Nov 2025)**

### **Topic:** Musical structures + template container acceptance

### **Depth:** ⭐⭐⭐⭐⭐

### **What we did:**

### **Chord**

- Implemented:
    
    - `root_`
        
    - `quality_`
        
    - chord naming logic
        
    - semitone patterns
        
- Wrote `get_notes()`
    
- Wrote `get_pitches(octave)`
    

### **Key Learnings:**

- Inside const functions:
    
    - `this` becomes `const*`
        
    - So mutating functions cannot be called
        
- Fix:
    
    - non-mutating operator+
        
    - avoid mutating `transpose` inside const functions
        

### **ChordProgression**

- Template constructor:
    
    - Accept any STL container
        
- Dedicated `initializer_list` overload because `{…}` is NOT a container
    

### **Voicing**

- Implemented simple voicing strategy:
    
    - just stack chord tones in fixed octave
        
- Prepared API for:
    
    - smooth voicing in future
        
    - voice-leading strategies
        

---

## **Week 7 — Misc Discussions, Debugging, Testing (Mid Nov 2025)**

### **Topic:** doctest, verifications, architectural patterns

### **Depth:** ⭐⭐⭐

### **What we did:**

- Wrote doctest tests for:
    
    - pitch math
        
    - frequency conversions
        
    - note transposition
        
    - chord voicing
        
- Verified operator outputs
    
- Checked correctness of intervals
    
- Discussed API names and clarity
    
- Cleaned the architecture for future extensions