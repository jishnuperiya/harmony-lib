
- **constructor works recursively**
When you build an object, C++ automatically **recursively constructs all bases and members first, in declaration order, before your constructor body runs.**

The compiler walks down through each member and base, and ensures each is set up.

It has its own alogrithm to do that

user defined data type get its constructor called and fundamental type like int, no constructor call happens since they arent user defined. still the compiler c++ treats it as "the int subobject exist now"

for fundamental types the compiler just do memcpy (simply copying the underlying bytes in memory.)

- **more on constructor signature**
```cpp
complex(const T& re = T(), const T& im = T());

```

- You can call it with **0 args** → `complex<> c;`
    
- With **1 arg** → `complex<> c(5);` (imaginary defaults to `T()`)
    
- With **2 args** → `complex<> c(5, 6);`

- `T()` means “call the **default constructor** of `T`.”



```
basic:

double a;          // default-initialized → indeterminate (garbage)
double b = double(); // value-initialized → 0.0


```


- `T()` means “call the **default constructor** of `T`.”
    
- If `T = double`, then `T()` → `double()` → value-initialized → `0.0`.

### Recursive construction

When you do:

`complex<int> c;`  

- The `complex` constructor runs.
    
- Its members (say `T re; T im;`) are each constructed by calling `T()` — the default constructor of `int`.
    
- Even though `int`’s default constructor is trivial, the compiler still “recursively” ensures that all subobjects are constructed in order.

- every constructor call in C++ ensures that **all subobjects are properly constructed, recursively, down to trivial types.**




# Complex (3) is essentially Complex (static_cast<double> (3), double())?


When you write something like:

`std::complex<double> z(3);`

it looks like you’re just “passing a single integer,” but what really happens is equivalent to:

`std::complex<double> z(static_cast<double>(3), double());`


### Why?

1. The constructor is:
    
    `complex(const T& re = T(), const T& im = T());`
    
    For `T = double`:
    
    `complex(const double& re = double(), const double& im = double());`
    
2. If you pass one argument:
    
    `complex<double> z(3);`
    
    - `3` is an `int`.
        
    - It is implicitly converted to `double`.
        
    - So it becomes `re = static_cast<double>(3)`.
        
3. The second parameter `im` is omitted, so it takes its **default argument** → `double()`, which is **value-initialized to `0.0`**.
    

---

### So effectively:

`std::complex<double> z(3);  // == std::complex<double>(static_cast<double>(3), double());`

---

### This ties back to “constructors are recursive”

- The `complex<double>` constructor calls `double()` for the default imaginary part.
    
- Even fundamental types like `double` are “constructed” this way (trivially, just zero-initialization).
    
- That’s why he keeps emphasizing: _everything gets constructed, recursively_.


Complex(3) is essentially Complex(static_cast<double>(3), double())
he was illustrating what the compiler is doing under the hood:

First argument: convert 3 (int) to 3.0 (double).

Second argument: use the default parameter double(), which gives 0.0.

So yes — it’s implicit coercion, but shown with static_cast to make it crystal clear.


- “What happens if you construct `std::complex<double> z(3);`?”
    
- The strong answer isn’t just _“it works”_ but _“the int 3 is implicitly converted to double, the imaginary part is default-constructed as double(), i.e. 0.0.”_


- **a point about memcpy**

- `memcpy` works for **trivial types** (ints, doubles, POD structs).
    
- It’s **dangerous** for types that manage resources (like pointers, file handles, sockets).
    
- That’s why C++ introduced **special member functions** (copy/move constructors, assignment operators). They ensure copying is done _safely_, not just with raw bytes.