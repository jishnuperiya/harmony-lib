
# Inheritance

if B derives from A, B is A
client can talk to B through A

A - pubic inteface

runtime polymorphism (virtual funcs)

if A has no data member (other than vtable) -> A is abstract class. all members are pure virtual functions.

inherit data members -> extra bagage and constraints for the inherited class

java has something called interface (no member)

there are 2 cases when to use inhertianc : i forgot what he said here

------
## chatgpt:
## 🧩 Inheritance — Jonathan’s Lesson (Reconstructed & Organized)

### 1. Core Concept

- When **`B` derives from `A`**,  
    → **“B _is an_ A.”**  
    That’s the _is-a_ relationship — the essence of inheritance.
    
- A **client** can interact with `B` objects _through_ the interface of `A`:

```cpp
A* obj = new B();  // works because B is-a A
obj->f();          // polymorphic call if A::f is virtual
```
### 2. Public Interface (the “Contract”)

- Class **`A` defines the public interface** — the functions that any subclass promises to implement.
    
- This interface should describe _behaviour_, not _state_.
    
- Clients depend only on the **interface**, not on the concrete subclass.
    

### 3. Runtime Polymorphism

- Enabled via **virtual functions**.
    
- Calls are dispatched through a **vtable** — a table of function pointers unique per class.
    
- If `A` has **no data members other than the vtable pointer**, it’s an **abstract base class** (ABC).

```cpp
struct Shape {
    virtual void draw() const = 0;  // pure virtual => abstract
    virtual ~Shape() = default;     // virtual dtor for polymorphic cleanup
};

```
### 4. Abstract Classes vs. Interfaces

- In C++, we often use **abstract base classes** to represent _interfaces_.
    
- Java has a keyword `interface`, but in C++ we simulate it by:
    
    - All members being pure virtual (`= 0`),
        
    - No data members.
        
- This ensures subclasses only define _behaviour_, not state.
    

### 5. The Cost of Inheriting Data

- Inheriting **data members** from a base introduces:
    
    - **Extra baggage** (memory footprint in every derived object),
        
    - **Constraints** on layout and construction,
        
    - **Tighter coupling** — derived class can’t easily change representation.
        
- That’s why base classes that are meant to be interfaces **should avoid data members** entirely.
    

### 6. When to Use Inheritance ✅

(These are the two classic, Jonathan-style “good reasons.”)

1. **To model substitutability** — when `B` truly _is a kind of_ `A` (semantic inheritance).
    
    > e.g., `Circle` is a `Shape`, `FileStream` is an `IStream`.
    
2. **To reuse polymorphic behaviour** — when you need a family of types sharing the same interface that can be used interchangeably at runtime.
    
    > e.g., plugin architectures, GUI widgets, IO streams.
    

### 7. When _Not_ to Use Inheritance ❌

- Don’t inherit just for **code reuse** — use **composition** instead.
    
- Don’t inherit from **concrete classes with data** unless you really need to extend them in kind.
    
- Avoid deep hierarchies — prefer **flat, composable designs**.
    

### 8. Key Quotes / Takeaways (likely Jonathan lines)

> “Inheritance should express an _is-a_ relationship, not a _has-a_ one.”  
> “If your base has state, your derived class is married to it.”  
> “Composition gives you flexibility; inheritance gives you identity.”


## 🧩 Multiple Inheritance and Mixins

### 1. Multiple Inheritance — the Good and the Bad

- **Multiple inheritance of _interfaces_** (abstract base classes with no data)  
    ✅ **is fine** — and often quite powerful.
    
    - Because such bases don’t carry **state**, there’s **no ambiguity** or **diamond problem** in object layout.
        
    - They only bring in _contracts_ (pure virtual methods), not data members.
```cpp
struct Drawable {
    virtual void draw() const = 0;
};
struct Serializable {
    virtual std::string serialize() const = 0;
};
struct Shape : Drawable, Serializable {
    // no issue here — both are pure interfaces
};

```

**Multiple inheritance from classes with data**  
❌ is dangerous — introduces:

- **Ambiguity** (e.g., diamond inheritance)
    
- **Duplicate subobjects**
    
- **Complex constructor chains**
    
- Hard-to-track memory footprint

```cpp
struct A { int x; };
struct B : A {};
struct C : A {};
struct D : B, C {}; // ❌ D now has *two* copies of A::x

```

### 2. Mixins — a Design Pattern for Safe Multiple Inheritance

- A **mixin** is a small, composable class that provides _behaviour_ (usually via templates), meant to be **inherited** by other classes.
    
- Mixins are designed to be **stateless or self-contained**, so inheriting them doesn’t cause layout conflicts.
```cpp
template<typename Derived>
struct Printable {
    void print() const {
        std::cout << static_cast<const Derived&>(*this).to_string();
    }
};

struct Point : Printable<Point> {
    std::string to_string() const { return "(x,y)"; }
};

```

- - Here, `Printable` is a **CRTP mixin** (Curiously Recurring Template Pattern).
        
    - It adds `print()` behaviour to any class that defines `to_string()`.
        
    - No virtual calls, no multiple inheritance issues, and no extra data.
        

### 3. Why It Works

- Multiple inheritance is **safe** as long as:
    
    - Bases are **pure interfaces** (no data members),
        
    - Or are **mixins** carefully designed to be independent and composable.
        

### 4. Jonathan’s likely summary line:

> “Multiple inheritance of _interfaces_ gives you flexibility — multiple inheritance of _implementation_ gives you pain.”

## 🧩 Diamond Inheritance (the “Deadly Diamond”)


```cpp
struct A {
    int x;
};

struct B : A { };
struct C : A { };
struct D : B, C { }; // <- the diamond

```

```bash
        A
       / \
      /   \
     B     C
      \   /
       \ /
        D

```

### 🧠 What Happens Here

- `B` and `C` **each inherit** their own copy of `A`.
    
- So `D` actually **contains two A subobjects**:
```cpp
D
├── B::A
└── C::A

```

That’s why this fails:

```cpp
D d;
d.x = 5;   // ❌ ambiguous: which A::x?

```

### Fix: Use _Virtual Inheritance_

```cpp
struct A {
    int x;
};

struct B : virtual A { };
struct C : virtual A { };
struct D : B, C { };  // now D has only one A

```

### Diagram (Virtual Inheritance)

```bash
         A
       /   \
  (virtual) \
     B       C
      \     /
       \   /
         D

```

- Now `B` and `C` share a **single shared A base**, managed virtually.
    
- But this introduces **constructor ordering complexity**, so it’s not free.
    

---

### Jonathan’s likely takeaway line:

> “If you ever see a diamond, ask: do these bases _share state_ or just _share behaviour_?  
> If they share state — trouble.  
> If they only share interface — you’re safe.”


## 🧱 Misuse of Multiple Inheritance — Data Reuse Trap

jonathon:

> “People tend to use multiple inheritance from base classes that _have data in them_.”

That’s a **design smell** — because it’s not inheritance of _behaviour_ or _contract_, it’s inheritance of _implementation and state_.  
When those base classes each carry their own data members, the derived class ends up with **duplicated or conflicting state**.

#### Example

```cpp
struct Window {
    int width, height;
};

struct Button {
    bool pressed;
};

struct FancyButton : Window, Button {
    // 🚫 inherits data members from *two* concrete bases
};

```

Now `FancyButton` physically contains all of:

- `Window::width`, `Window::height`
    
- `Button::pressed`
    

It’s effectively **composing** them — but in the _wrong way_ (via inheritance).

---

### 2. Why It’s Problematic

- **Object layout conflicts** — each base contributes its own subobject and constructor/destructor path.
    
- **Tight coupling** — `FancyButton` can’t change how `Window` or `Button` store their data.
    
- **Ambiguity** — shared function or member names can collide.
    
- **Fragile base problem** — changing a base breaks all derived classes.
    

Jonathan likely phrased it like:

> “You’ve now _inherited implementation_ rather than _extended an interface._  
> That’s where C++ programmers get into trouble.”

---

### 3. The Right Approach — Use Composition Instead

Instead of:

```cpp
struct FancyButton : Window, Button { ... };

```

prefer:

```cpp
struct FancyButton {
    Window window;   // has-a Window
    Button button;   // has-a Button
};

```

Now:

- You can control lifetime and initialization order yourself.
    
- There’s no ambiguity or multiple inheritance issues.
    
- You still reuse the logic, but **through composition**.
    

Jonathan would sum it up like:

> “Inherit for _polymorphism_.  
> Compose for _code reuse_.”

---

### 4. When Multiple Inheritance _Is_ Okay

- When all bases are **pure interfaces** (`=0` virtuals, no data).
    
- When using **CRTP mixins** that don’t carry shared state.
    
- When the purpose is **orthogonal behaviours**, not shared data.


---- 
he said: istream and ostream inherit from iostream. and said something like a keep a pointer to ios members and talk thru that pointer

## 🧩 The `ios` / `istream` / `ostream` / `iostream` Hierarchy

### 1. The Class Relationship

```bash
     ios_base
         ↑
        ios
  ↑           ↑
 istream   ostream
      ↖   ↗
      iostream

```

So:

- **`ios_base`** – the _lowest-level base_ that manages global stream state (flags, formatting, locales, etc.).
    
- **`ios`** – inherits from `ios_base`, and **adds the link to the buffer** (`streambuf*`) + error state bits.
    
- **`istream` / `ostream`** – public interfaces for input and output, both derived from `ios`.
    
- **`iostream`** – inherits from _both_ `istream` and `ostream` → a classic example of **multiple inheritance of base classes with shared state** — handled carefully by design.

### 2. Why Multiple Inheritance Here Works (and How They Avoid Ambiguity)

Jonathan’s line:

> “`istream` and `ostream` inherit from `ios` —  
> and they keep a pointer to `ios` members and talk through that pointer.”

He’s referring to the **controlled sharing** of the common base `ios` between `istream` and `ostream`.

- `iostream` _inherits_ from both `istream` and `ostream`.
    
- Both of those themselves _contain_ an `ios` subobject.
    
- But to avoid **two copies of `ios`**, they use **virtual inheritance**.

```cpp
class ios : virtual public ios_base {
protected:
    streambuf* sbuf;
};

class istream : virtual public ios { /* input operations */ };
class ostream : virtual public ios { /* output operations */ };

class iostream : public istream, public ostream { };

```

Now:

- `iostream` only has **one shared `ios` subobject**.
    
- Both `istream` and `ostream` _refer to_ that shared base via a pointer (internally).
    
- When you call methods like `setstate()` or `rdbuf()`, both input and output sides “talk” to the **same shared `ios` data**.
    

---

### 3. The Pointer Reference He Mentioned

The phrase:

> “Keep a pointer to ios members and talk through that pointer.”

means:

- `istream` and `ostream` don’t each manage separate copies of the `ios` state (format flags, error bits, etc.).
    
- They each hold **pointers** (or virtual base references) to the _single shared `ios` subobject_.
    
- That’s how `iostream` stays consistent: when output sets a failbit, input sees it too.
    

So conceptually:


```bash
iostream
├── istream (has pointer → shared ios)
├── ostream (has pointer → shared ios)
└── ios (shared virtual base)

```

### 4. Why It’s a “Bridge-Like” Design

- `ios` → manages connection to a `streambuf*` (the **Bridge** implementation side).
    
- `istream` / `ostream` → provide the **abstraction** layer for input/output operations.
    
- They all **delegate actual reading/writing** through that `streambuf*`.
    

Jonathan’s teaching thread ties this together:

> “See how the _abstraction hierarchy_ (istream, ostream, iostream)  
> is separated from the _implementation hierarchy_ (streambuf, filebuf, stringbuf)?  
> That’s the Bridge pattern in action.”

## 5. Summary Diagram

```bash

              Abstraction side (user-facing)
        ┌──────────────────────────────────┐
        │            iostream              │
        │        /             \           │
        │   istream             ostream    │
        │        \             /           │
        │             ios                 │  ← shared state (via virtual base)
        └──────────────────────────────────┘
                        │
                        ▼
          Implementation side (Bridge target)
                  streambuf*
                     │
          ├──────────┴───────────┐
       filebuf              stringbuf

```

### Jonathan’s likely takeaway line:

> “They solved the diamond the right way —  
> by _sharing one ios subobject_ and letting both sides talk through a pointer.  
> That’s why `iostream` behaves as one unified stream.”


## 🧩 `streambuf`, `filebuf`, and `fstream` — The Implementation Side

### 1. The Bridge Connection

- The **`ios` / `istream` / `ostream` / `iostream`** hierarchy is the **abstraction side** (the public API).
    
- The **`streambuf`** hierarchy is the **implementation side** (the data sink/source).
    

They’re connected through a pointer:

```cpp
class ios {
protected:
    streambuf* _M_streambuf;  // The bridge!
};

```

so when you write:

`std::cout << "Hello";`

`ostream` forwards to its underlying `streambuf` to actually push characters.


### 2. The `streambuf` Base Class

Jonathan’s line:

> “`streambuf` has implementations like `putc`, `getc` — all derived buffers get these.”

Exactly.  
`std::streambuf` defines **low-level virtual functions** that control character transfer between your program and a device.

#### Key virtuals (simplified view)

```cpp
class streambuf {
public:
    virtual int_type sputc(char_type ch);     // put one char (output)
    virtual int_type sbumpc();                // get one char (input)
    virtual int_type sgetc();                 // peek one char
    virtual std::streamsize sputn(const char*, std::streamsize n);  // write block
    virtual std::streamsize sgetn(char*, std::streamsize n);        // read block
    // ... plus sync, underflow, overflow, etc.
};

```
- These are the **hooks** that derived buffer types override.
    
- So every custom `streambuf` defines _how_ data physically moves (to console, file, string, socket, etc.).
    
- All higher layers (`istream`, `ostream`, etc.) eventually funnel through these.
    

---

### 3. Derived Buffers — Concrete Implementations

Common derived classes:

- **`filebuf`** → reads/writes to files (`FILE*` / OS handle)
    
- **`stringbuf`** → reads/writes to an in-memory string buffer
    
- **`stringstreambuf`** → similar, used by `std::stringstream`
    
- **`consolebuf`** (internal) → connects `cin` / `cout` to terminal
    

Jonathan’s phrasing:

> “All derived buffers _get_ these functions — they just override them to define where the bytes go.”

So conceptually:


```bash
   streambuf (base)
      ↑
 ├── filebuf
 ├── stringbuf
 └── ...

```

### 4. `fstream` — the Wrapper on Top

> “`fstream` is an `iostream` with a `filebuf` embedded in it.”

Yes — that’s the final composition step of the Bridge pattern.

```cpp
class fstream : public iostream {
    filebuf _fb;  // the implementation (concrete buffer)
public:
    fstream(const char* filename, ios_base::openmode mode)
      : iostream(&_fb), _fb(filename, mode) {}
};

```

So:

- `fstream` inherits all the I/O **interface** from `iostream`.
    
- It **owns** a `filebuf` member.
    
- It connects that `filebuf` to its `ios` bridge pointer in the constructor.
    

Hence:

> “It’s a wrapper — `iostream` on top, `filebuf` underneath.”

This design allows:

```cpp
std::fstream file("data.txt", std::ios::out);
file << "Hello";  // goes: ostream → ios → filebuf → OS

```

### 5. Putting It All Together — The Full Bridge

```bash
         Abstraction side (public API)
   ┌───────────────────────────────┐
   │           iostream            │
   │        /           \          │
   │   istream           ostream   │
   │        \           /          │
   │            ios                 │
   │             │ (bridge pointer) │
   └─────────────┼─────────────────┘
                 │
                 ▼
        Implementation side (streambuf)
                 │
           ┌────────────┐
           │  filebuf   │ ← fstream embeds this
           │  coutbuf   │
           │  stringbuf │
           └────────────┘

```

### Jonathan’s likely wrap-up lines

> “The beauty here is in the layering:
> 
> - `iostream` gives polymorphism on the _abstraction_ side,
>     
> - `streambuf` gives polymorphism on the _implementation_ side.
>     
> - And the pointer between them is the bridge.”
>     

> “`fstream` just glues the two — an `iostream` whose bridge points to a `filebuf` it owns.”


----
## 🧩 Decorator Pattern — “Chain of Bridges”

### 1. Context: From Bridge → to Decorator

- **Bridge** separates an _abstraction_ from its _implementation_.
    
    - `ostream` ↔ `streambuf` is a classic example.
        
- **Decorator** wraps an existing object of the same interface to _extend or modify_ its behaviour dynamically.
    

Jonathan’s phrase:

> “Decorator pattern — a chain of bridges.”

means:

- You can **stack multiple bridges** (or bridge-like layers),  
    each forwarding to the next — forming a _chain of responsibility_.
    
- Each layer decorates or modifies data before passing it further down.


## 2. Classic Decorator Structure

```cpp
struct Stream {
    virtual void write(const std::string& data) = 0;
    virtual ~Stream() = default;
};

struct FileStream : Stream {
    void write(const std::string& data) override {
        std::cout << "[FILE] " << data << '\n';
    }
};

// Decorator base
struct StreamDecorator : Stream {
protected:
    Stream& next;
public:
    StreamDecorator(Stream& s) : next(s) {}
};

// Example decorator: adds buffering
struct BufferedStream : StreamDecorator {
    using StreamDecorator::StreamDecorator;
    void write(const std::string& data) override {
        std::string buf = "Buffered(" + data + ")";
        next.write(buf);  // forward down the chain
    }
};

// Another decorator: compression
struct CompressedStream : StreamDecorator {
    using StreamDecorator::StreamDecorator;
    void write(const std::string& data) override {
        std::string compressed = "Compressed(" + data + ")";
        next.write(compressed);
    }
};

```

usage:

```cpp
FileStream file;
BufferedStream buf(file);
CompressedStream zip(buf);

zip.write("Hello");
// Output: [FILE] Compressed(Buffered(Hello))

```


## 5. Summary Diagram

```bash
   ┌──────────────────────────────┐
   │       Abstraction Layer      │
   │     (ostream, your Stream)   │
   └────────────┬─────────────────┘
                │
                ▼
         ┌──────────────┐
         │ Decorator 1  │ → modifies data → forwards to next
         ├──────────────┤
         │ Decorator 2  │ → modifies again → forwards to next
         ├──────────────┤
         │ Base stream  │ → final destination (file, socket)
         └──────────────┘

```

So it’s literally a **chain of bridges** — each forwarding operation through the same abstract interface, possibly transforming it.

---

### Jonathan’s likely takeaway line

> “The decorator is like a chain of bridges —  
> each link forwards through the same interface,  
> but can intercept, modify, or extend the call before passing it along.”

> “Bridge separates abstraction from implementation.  
> Decorator extends implementation _without_ changing abstraction.”




then he said something about constructional patterns:

## 🧩 “Constructional Pattern” — How Virtual Tables Are Built

### 1. Background: Virtual Functions → Vtables

When a class declares **virtual functions**,  
the compiler builds a hidden **virtual table (vtable)** — a table of function pointers.  
Every object of that class contains a **hidden pointer** to its class’s vtable (the _vptr_).


```cpp
struct A {
    virtual void f();
    virtual void g();
};

```

at runtime:
```cpp
vtable for A:
 +----+-------------+
 | 0  | &A::f()     |
 | 1  | &A::g()     |
 +----+-------------+

object of A:
 [vptr] → vtable for A

```

Calls like `a.f()` become:  
→ `a.vptr[0](a)` (the compiler substitutes the correct entry at runtime).

---

### 2. Virtual Tables and Inheritance

When a derived class **overrides** virtual functions,  
its vtable entries point to the new overrides.

```cpp
struct B : A {
    void f() override;
};

```

now

```cpp
vtable for B:
 +----+-------------+
 | 0  | &B::f()     |  // overrides A::f
 | 1  | &A::g()     |  // inherits A::g
 +----+-------------+

```

Each polymorphic object carries a pointer to **its** vtable.

---

### 3. What He Meant by “You then have two different tables”

He was describing **what happens under multiple inheritance** —  
each base subobject gets **its own vtable pointer**, because each base may define its own virtuals.

#### Example

```cpp
struct A { virtual void fa(); };
struct B { virtual void fb(); };
struct C : public A, public B {
    void fa() override;
    void fb() override;
};

```
Memory layout of a `C` object:
```bash
+-------------------+
| vptr_A → vtableA  |
| A subobject data  |
+-------------------+
| vptr_B → vtableB  |
| B subobject data  |
+-------------------+
| C's own members   |
+-------------------+

```


Each base (`A`, `B`) brings its **own virtual table**,  
so `C` carries **two vptrs → two vtables**.

That’s what Jonathan meant by:

> “You then have two different tables.”

Each subobject within `C` has its _own_ vtable;  
virtual dispatch happens through whichever base pointer you’re using.

---

### 4. Why He Called It a “Constructional Pattern”

Jonathan often uses that phrasing to highlight how **object construction + virtual dispatch setup** are _patterns of memory layout_, not just language magic.

He probably meant:

> “This is part of the _constructional pattern_ of C++’s runtime polymorphism —  
> each base contributes its own vtable, and during construction,  
> the compiler wires those pointers to the right tables.”

So:

- It’s “constructional” because it governs how the object is _constructed in memory_ (with multiple subobjects and vptrs).
    
- It’s not a design pattern like Bridge/Decorator, but a **mechanical pattern** of object layout and vtable wiring.
    

---

### 5. In Summary

|Concept|What Happens|Key Detail|
|---|---|---|
|**Single inheritance**|One vtable, one vptr|Simpler layout|
|**Multiple inheritance**|Multiple vtables, one per base subobject|Each base’s virtual funcs resolved separately|
|**Virtual inheritance**|Shared base → extra indirection|One shared subobject, pointer adjustment|
|**Jonathan’s point**|“Constructional pattern” = how these vtables are built and connected at construction time|Helps understand why virtual calls behave correctly from any base pointer|

---

### Likely Jonathan Quote

> “When you have multiple bases, each one gets its own table —  
> so the compiler constructs _two tables, two vptrs_.  
> That’s part of the object’s constructional pattern —  
> the internal wiring of its polymorphic structure.”

chatgpt implementaiton of ios class

```cpp
// tiny_io.hpp (single-file demo)
#pragma once
#include <cstdio>
#include <cstring>
#include <string>
#include <memory>
#include <stdexcept>
#include <cctype>

namespace tiny {

// ======================= Implementation side (Bridge target) =======================
class streambuf {
public:
    using int_type = int;

    virtual ~streambuf() = default;

    // Output core hooks
    virtual int_type sputc(char ch) { (void)ch; return EOF; }
    virtual std::size_t sputn(const char* s, std::size_t n) {
        std::size_t written = 0;
        while (written < n) {
            if (sputc(s[written]) == EOF) break;
            ++written;
        }
        return written;
    }
    virtual int sync() { return 0; } // 0 => success

    // Input core hooks
    virtual int_type sbumpc() { return EOF; } // get and advance
    virtual int_type sgetc()  { return EOF; } // peek
    virtual std::size_t sgetn(char* s, std::size_t n) {
        std::size_t got = 0;
        while (got < n) {
            int_type c = sbumpc();
            if (c == EOF) break;
            s[got++] = static_cast<char>(c);
        }
        return got;
    }
};

// Console buffer (stdout only, for demo)
class consolebuf : public streambuf {
public:
    explicit consolebuf(std::FILE* f = stdout) : file_(f) {}
    int_type sputc(char ch) override {
        return std::fputc(static_cast<unsigned char>(ch), file_);
    }
    std::size_t sputn(const char* s, std::size_t n) override {
        return std::fwrite(s, 1, n, file_);
    }
    int sync() override { return std::fflush(file_); }
private:
    std::FILE* file_ = nullptr;
};

// File buffer (read/write)
class filebuf : public streambuf {
public:
    filebuf() = default;
    ~filebuf() override { close(); }

    bool open(const char* path, const char* mode) {
        close();
        f_ = std::fopen(path, mode);
        return f_ != nullptr;
    }
    void close() {
        if (f_) { std::fclose(f_); f_ = nullptr; }
    }

    int_type sputc(char ch) override { return f_ ? std::fputc(static_cast<unsigned char>(ch), f_) : EOF; }
    std::size_t sputn(const char* s, std::size_t n) override { return f_ ? std::fwrite(s,1,n,f_) : 0; }
    int sync() override { return f_ ? std::fflush(f_) : 0; }

    int_type sbumpc() override { return f_ ? std::fgetc(f_) : EOF; }
    int_type sgetc()  override {
        if (!f_) return EOF;
        int c = std::fgetc(f_);
        if (c != EOF) std::ungetc(c, f_);
        return c;
    }
    std::size_t sgetn(char* s, std::size_t n) override { return f_ ? std::fread(s,1,n,f_) : 0; }

private:
    std::FILE* f_ = nullptr;
};

// String buffer (in-memory)
class stringbuf : public streambuf {
public:
    const std::string& str() const { return buf_; }
    void str(std::string s) { buf_ = std::move(s); pos_ = 0; }

    // output appends
    int_type sputc(char ch) override { buf_.push_back(ch); return static_cast<unsigned char>(ch); }
    std::size_t sputn(const char* s, std::size_t n) override { buf_.append(s, n); return n; }
    int sync() override { return 0; }

    // input reads from internal buffer
    int_type sbumpc() override {
        if (pos_ >= buf_.size()) return EOF;
        return static_cast<unsigned char>(buf_[pos_++]);
    }
    int_type sgetc() override {
        if (pos_ >= buf_.size()) return EOF;
        return static_cast<unsigned char>(buf_[pos_]);
    }
    std::size_t sgetn(char* s, std::size_t n) override {
        std::size_t rem = buf_.size() - pos_;
        std::size_t take = n < rem ? n : rem;
        std::memcpy(s, buf_.data() + pos_, take);
        pos_ += take;
        return take;
    }

private:
    std::string buf_;
    std::size_t pos_ = 0;
};

// ======================= Shared state base =======================
class ios_base {
public:
    using iostate = unsigned;
    static constexpr iostate goodbit = 0x0;
    static constexpr iostate eofbit  = 0x1;
    static constexpr iostate failbit = 0x2;
    static constexpr iostate badbit  = 0x4;

    bool good() const { return state_ == goodbit; }
    bool fail() const { return (state_ & (failbit | badbit)) != 0; }
    bool bad()  const { return (state_ & badbit) != 0; }
    bool eof()  const { return (state_ & eofbit) != 0; }

protected:
    void clear(iostate s = goodbit) { state_ = s; }
    void setstate(iostate s) { state_ |= s; }

private:
    iostate state_ = goodbit;
};

// In practice, some lib impls use virtual inheritance to avoid duplicates.
// We'll do that to illustrate the diamond resolution.
class ios : public virtual ios_base {
public:
    ios() = default;
    explicit ios(streambuf* sb) : sbuf_(sb) {}

    streambuf* rdbuf() const { return sbuf_; }
    streambuf* rdbuf(streambuf* sb) { streambuf* old = sbuf_; sbuf_ = sb; return old; }

protected:
    void init(streambuf* sb) { sbuf_ = sb; clear(); }

private:
    streambuf* sbuf_ = nullptr; // the Bridge pointer
};

// ======================= Abstraction side =======================
class ostream; // forward for manip type

using manip_t = ostream& (*)(ostream&);

class ostream : public virtual ios {
public:
    ostream() = default;
    explicit ostream(streambuf* sb) : ios(sb) {}

    // core put
    ostream& put(char ch) {
        if (!rdbuf() || rdbuf()->sputc(ch) == EOF) setstate(badbit);
        return *this;
    }

    // flush
    ostream& flush() {
        if (!rdbuf() || rdbuf()->sync() != 0) setstate(badbit);
        return *this;
    }

    // operator<< overloads
    ostream& operator<<(const char* s) {
        if (!s) return *this;
        if (!rdbuf()) { setstate(badbit); return *this; }
        if (rdbuf()->sputn(s, std::strlen(s)) != std::strlen(s)) setstate(badbit);
        return *this;
    }
    ostream& operator<<(const std::string& s) {
        if (!rdbuf()) { setstate(badbit); return *this; }
        if (rdbuf()->sputn(s.data(), s.size()) != s.size()) setstate(badbit);
        return *this;
    }
    ostream& operator<<(char ch) { return put(ch); }

    ostream& operator<<(int v) {
        char buf[32];
        std::snprintf(buf, sizeof(buf), "%d", v);
        return *this << buf;
    }
    ostream& operator<<(double v) {
        char buf[64];
        std::snprintf(buf, sizeof(buf), "%.6g", v);
        return *this << buf;
    }

    // manipulators
    ostream& operator<<(manip_t m) { return m(*this); }
};

// very tiny istream (just enough to demo)
class istream : public virtual ios {
public:
    istream() = default;
    explicit istream(streambuf* sb) : ios(sb) {}

    int get() {
        if (!rdbuf()) { setstate(badbit); return EOF; }
        int c = rdbuf()->sbumpc();
        if (c == EOF) setstate(eofbit);
        return c;
    }

    // basic >> for int (skips spaces, parses sign and digits)
    istream& operator>>(int& out) {
        if (!rdbuf()) { setstate(badbit); return *this; }
        // skip whitespace
        int c;
        do { c = rdbuf()->sgetc(); if (c == EOF) { setstate(eofbit); return *this; } } while (std::isspace(c));
        // sign
        int sign = 1;
        if (c == '+' || c == '-') { sign = (c == '-') ? -1 : 1; rdbuf()->sbumpc(); }
        // digits
        long long val = 0;
        bool any = false;
        while ((c = rdbuf()->sgetc()) != EOF && std::isdigit(c)) {
            any = true;
            val = val * 10 + (c - '0');
            rdbuf()->sbumpc();
        }
        if (!any) setstate(failbit);
        out = static_cast<int>(sign * val);
        return *this;
    }

    // basic >> for word (no spaces)
    istream& operator>>(std::string& out) {
        out.clear();
        if (!rdbuf()) { setstate(badbit); return *this; }
        // skip whitespace
        int c;
        do { c = rdbuf()->sgetc(); if (c == EOF) { setstate(eofbit); return *this; } } while (std::isspace(c));
        // read until whitespace/EOF
        while ((c = rdbuf()->sgetc()) != EOF && !std::isspace(c)) {
            out.push_back(static_cast<char>(c));
            rdbuf()->sbumpc();
        }
        return *this;
    }
};

// combined
class iostream : public istream, public ostream {
public:
    iostream() = default;
    explicit iostream(streambuf* sb) : ios(sb), istream(sb), ostream(sb) {}
};

// ======================= Wrappers (own the buffer) =======================
class ofstream : public ostream {
public:
    ofstream() = default;
    explicit ofstream(const char* path, const char* mode = "w") { open(path, mode); }
    bool open(const char* path, const char* mode = "w") {
        if (!fb_.open(path, mode)) { this->setstate(badbit); return false; }
        this->init(&fb_);
        return true;
    }
    void close() { fb_.close(); }
private:
    filebuf fb_;
};

class ifstream : public istream {
public:
    ifstream() = default;
    explicit ifstream(const char* path, const char* mode = "r") { open(path, mode); }
    bool open(const char* path, const char* mode = "r") {
        if (!fb_.open(path, mode)) { this->setstate(badbit); return false; }
        this->init(&fb_);
        return true;
    }
    void close() { fb_.close(); }
private:
    filebuf fb_;
};

class fstream : public iostream {
public:
    fstream() = default;
    fstream(const char* path, const char* mode) { open(path, mode); }
    bool open(const char* path, const char* mode) {
        if (!fb_.open(path, mode)) { this->setstate(badbit); return false; }
        this->init(&fb_);
        return true;
    }
    void close() { fb_.close(); }
private:
    filebuf fb_;
};

class stringstream : public iostream {
public:
    stringstream() { this->init(&sb_); }
    std::string str() const { return sb_.str(); }
    void str(const std::string& s) { sb_.str(s); }
private:
    stringbuf sb_;
};

// ======================= Manipulators =======================
inline ostream& endl(ostream& os) { os.put('\n'); return os.flush(); }
inline ostream& flush(ostream& os) { return os.flush(); }

// ======================= Globals for quick demo =======================
static consolebuf __cout_buf(stdout);
static consolebuf __cerr_buf(stderr);

static ostream cout(&__cout_buf);
static ostream cerr(&__cerr_buf);

} // namespace tiny

// ======================= Demo main (optional) =======================
// Uncomment to test:
// #include <iostream>
// int main() {
//     using namespace tiny;
//     cout << "Hello, tiny I/O! " << 42 << endl;
//     ofstream f("tiny_out.txt");
//     f << "File line 1" << endl << "Line 2 = " << 123 << endl;
//     f.flush();
//
//     stringstream ss;
//     ss << "99 bottles";
//     int n; std::string w;
//     ss >> n >> w;
//     cout << "Parsed: n=" << n << " w=" << w << endl;
//     return 0;
// }

```

---
# NEXT PROJECT STEPS

