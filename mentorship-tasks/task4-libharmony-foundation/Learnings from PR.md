- class names start with lower case - style preference
- `struct` and `class` are **identical in functionality**, except that
   `struct` defaults to **public** access,
   `class` defaults to **private** access.
- Rule of thumb: classes with trivial copy semantics whose size is that of two doubles or less are passed by value; anything larger, by const&.
When an object is:

- **≤ 16 bytes** (like two doubles or two ints), and
    
- **Trivially copyable** (no heap allocations, no special copy constructors),
    

then **passing by value** is faster or just as fast as passing by `const&`.

----------------
- Frequency hz should be always positive:
- **“value-type correctness”** — that objects should always represent _valid domain values_.
Jonathan is emphasizing **“value-type correctness”** — that objects should always represent _valid domain values_.  
That way:

- You can safely do math with them (e.g., divide by frequency),
    
- You catch invalid states early,
    
- And your design better matches real-world semantics (frequencies are > 0).
    

This kind of defensive design is exactly what he means when he talks about _value semantics_ and _semantic invariants_ — one of his key teaching points.

------------------------------------------

- on opertor+ andoperator- in the frequency class:
- **Frequency** itself is a _raw quantity_ — you don’t “add” two frequencies (e.g., 440 Hz + 880 Hz doesn’t produce a meaningful musical result).
    
- Instead, you perform **multiplicative or logarithmic relationships**, e.g. “transpose up by one octave” (multiply by 2).
    
- So, your arithmetic operators `operator+` and `operator-` don’t make semantic sense in this domain.
proper operation on frequency space is **multiplicative**, not additive.

---


