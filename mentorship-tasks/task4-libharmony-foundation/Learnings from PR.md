- class names start with lower case - style preference
- `struct` and `class` are **identical in functionality**, except that
   `struct` defaults to **public** access,
   `class` defaults to **private** access.
- Rule of thumb: classes with trivial copy semantics whose size is that of two doubles or less are passed by value; anything larger, by const&.
When an object is:

- **≤ 16 bytes** (like two doubles or two ints), and
    
- **Trivially copyable** (no heap allocations, no special copy constructors),
    

then **passing by value** is faster or just as fast as passing by `const&`.

The essence of the guideline is: does copying a value invoke anything more expensive than ‘memcpy(x,y, 16)’ , which itself be obliged by the compiler to 2 register pushes . ..if so , avoid this cost by passing ref  
So even though the class may be small, if the constructor indirectly triggers a function call of some kind, you are better off passing by ref


example:

```cpp
struct TinyHeap {
    int* p;
    TinyHeap(const TinyHeap& other) { p = new int(*other.p); } // calls heap alloc!
};

```

Even though this struct is tiny (just 8 bytes), copying it runs code, allocates heap memory — way more expensive than a `memcpy`.


That’s his shorthand for the ideal case:

- A trivial 16-byte copy on most architectures can be done with 2 `mov` instructions (or 2 register pushes).
    
- That’s the threshold of “cheap enough.”
    

Anything beyond that — e.g., function call, heap allocation, reference counting — crosses the line.




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


### Mark accessors as `const`

Your current:


```cpp
int midi();
double frequncy();
```

make these accessors as constant
```cpp
int midi() const;
Frequency frequency() const;

```

why:

`const` member functions promise **not to modify the object**, allowing you to call them on `const Pitch&` or `const Note&`.

Without `const`, you can’t do this:
```cpp
void print_pitch(const Pitch& p) {
    std::cout << p.midi(); // ❌ error if midi() is not const
}

```

So adding `const` signals _intent_ and improves correctness.


### forward declaration

Telling the compiler that this class exist:

```cpp
namespace harmony {
  class frequency;  // allow name to appear in declaration before class defention is seen
  class pitch;
  class note;
  // -------------------
  // pitch Class
  // -------------------
  class pitch
  {
  public:
    // ---Special Member Functions ---
    pitch(int midi_note = 60);
    // ---Accessors---
    int get_midi() const;
    frequency get_frequency() const;
    // ---Mutating member operators---
    pitch& operator+=(int semitones);
    pitch& operator-=(int semitones);
  private:
    uint8_t midi_note_ = 60;  // 0–127

  };
```

