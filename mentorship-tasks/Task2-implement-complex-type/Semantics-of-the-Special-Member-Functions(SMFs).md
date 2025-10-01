

### Default constructor

**Syntax:**

`T();`

**Semantics:**  
Creates a new object with no arguments.

- Fundamental-type members: left uninitialized (default-init) or zeroed (value-init).
    
- Class-type members: their default constructors are called.
    

---

### Non-default constructor

**Syntax:**

`T(double, double);`

**Semantics:**  
Creates a new object with explicit values. Members are initialized from parameters.

---

### Copy constructor

**Syntax:**

`T(const T&);`

**Semantics:**  
Creates a new object as a copy of another existing object.

- Invoked during initialization (`T y = x;`, pass-by-value).
    
- Performs memberwise copy unless customized.
    

---

### Copy assignment operator

**Syntax:**

`T& operator=(const T&);`

**Semantics:**  
Replaces the state of an existing object with that of another.

- Invoked on assignment (`x = y;`).
    
- Needs to handle self-assignment safely.
    
---

### Destructor

**Syntax:**

`~T();`

**Semantics:**  
Destroys an object at the end of its lifetime.

- Calls destructors of class-type members.
    
- Does nothing for fundamental types.
    
- Used to release resources (RAII).