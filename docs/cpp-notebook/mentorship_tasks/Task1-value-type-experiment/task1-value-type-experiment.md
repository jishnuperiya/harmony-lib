
  
 - Task Given: Explore what it means to be a **value type** in C++. 
 - Focus: Built-in-like behavior (copy, assign, pass to functions, use in expressions)
 - Date: Sep 2025

**Goal** : Understand what it takes for a user-defined type to behave like a **value type**, just like int or double.
## Exercise 1 – Playing with int
### What I Did

Wrote a function that takes two ints and explored all operations I could perform with them:

- Assign one to another: `x = y;`

- Copy construction: `int z = x;`
 
- Equality comparison: `x == y`

- Pass to another function: `do_nothing(x, y);`

- Truth test: `if (x) { ... }`

- Arithmetic: `+`, `-`, `*`, `/`

- Bitwise: `&`, `|`, `^`, `~`, `<<`, `>>`

- Increment/decrement: `x++`, `--x`

- Compound assignment: `+=`, `-=`, etc.


### What I Learned

- **Assignment (`x = y`)** uses the **copy assignment operator**.
    
- **Copy (`int z = x`)** uses the **copy constructor**.
    
- **Comparison (`x == y`)** works out of the box for ints.
    
- **Truth testing** (`if (x)`) is supported implicitly: any non-zero `int` is `true`.
    
- **Arithmetic, Bitwise, and Compound ops** are all available for `int` by default.
    
- `int` supports both:
    
    - **Non-destructive** operations (`z = x + y`)
        
    - **Destructive** operations (`x += y`, `x++`)


## Exercise 2 – Typedef Alias

### What I Did

Replaced int with an alias:

`using value = int;`

Confirmed that everything still compiled and behaved the same.


## Exercise 3 – Replace `int` with User-Defined `Complex`

### What I Did

Defined:
```cpp
struct complex{
int real;
int imaginary;
}
```
```cpp
using value = Compley
```
Then tested the same function with `value = Complex`.

### What Worked

Pass to function: `do_nothing(x, y)`  
Copy assignment: `x = y;`  
Copy constructor: `value z = x;`

**I learned that** These work because the compiler generates the **special member functions** automatically

### What Did NOT Work 

`x == y`  No `operator==` defined  
`if (x)`  No implicit conversion to `bool`  
`x + y`, `x * y`, `x += y`, etc. No arithmetic operators defined . both destructive as well as non destructive
Bitwise operations also fail - both destructive and non destructive.