## 1.  Ownership semantics
**Every c++ type must define who owns what.**

ownership semantics describe:
- who is responsible for an object's lifetime,
- who cleans up the resources
- and whether multiple objects share or transfer ownership.
in othe words: "when i copy or move this object" - who owns the underlying resource now?


#### Value semantics - one kind of ownership semantics
     - our complex and string classes that we implmented so far.
    **value semantics means:**
     - Every object **owns its own resources**.
	- Copying creates a **new, independent owner**.
	- Destroying one object doesn’t affect others.
	- Each object has exclusive ownership of its internal state.
eg. string class:
```cpp
std::string a = "hello";
std::string b = a;  // deep copy, owns its own buffer

```
`a` and `b` own their own heap memory.
When `a` dies, `b` is unaffected.

That’s **value semantics → exclusive ownership.**

-  The class hides all resource management — the user treats it as a _value_
	 
- use value semantics unless inheritance (will learn later when studying inheritance)
#### Pointer semantics - the other kind of ownership semantics
    
 Object references shared resources via pointers.
 - you need when you want inheritance, dynamic poloymorphism (will learn later)
        
-> havent learned till now

## 2. Extension Points

Extension points is a crucial design concept(not a language feature). that enables a system to be **customized and extended** without altering its core, proven source code.

there are 2 types:
1. Architectural extension points (design patterns)
(will go through it later)
2. Class extension points

##### Class extension points
mentor referred to the **special member functions** as extension points because they allow you to customize the **object's lifecycle and resource management behavior** beyond the compiler's simple defaults.
By implementing them, you are **extending** the language's built-in memory management rules for your specific resource-owning class.

![[Pasted image 20251010140947.png]]
##### The Conceptual Distinction

While writing a custom copy/move function is technically a **modification** to the class's source code, it's considered an **extension of the object's _behavior_** because:

1. **Standardized Slot:** These functions are standardized "slots" that C++ guarantees exist for every class.
    
2. **Resource Management:** By defining them, you are extending the default behavior (simple memory copy) into a robust, resource-aware system (RAII). You are customizing _how_ the class instance is managed, not changing its core functional logic.

##### The Modern Resolution: The Rule of Zero

The ultimate goal in modern C++ design is to avoid writing these five functions entirely. By following the **Rule of Zero**—delegating all resource management to standard library wrappers like `std::unique_ptr`, `std::vector`, and `std::string`—you rely on the **already-correctly-extended** behavior of the standard library, making your class truly closed for modification.

 _Insight:_

> “Copy/move are extension points for value types; you can redefine how duplication or transfer works.”

### 3. Constructor Practices

- Do as much work as possible in the **member initializer list** — avoids redundant construction.
    
- Example:
```cpp
String::String(const char* s)
    : length_(std::strlen(s)), data_(new char[length_ + 1]) { ... }

```

This ensures direct member initialization instead of default + assignment.

### 4. Delete Operators

- `delete` → for single objects (`new`)
    
- `delete[]` → for arrays (`new[]`)  
    Mixing them causes undefined behavior.

#### What happens when you call `delete` in C++

When you write:

`delete p;`

you’re not just “freeing memory.”  
It’s actually a **two-step process** performed by the compiler-generated _delete expression_.

---

#### Step 1 – Call the object’s destructor

`p->~T();`

This is a call to the destructor of the object **that `p` points to**.  
That destructor is responsible for cleaning up whatever the object owns — for example, freeing its internal heap memory.

---

#### Step 2 – Deallocate the raw memory

After the destructor finishes, the runtime calls the _deallocation function_:

`operator delete(p);`

This function (the global `::operator delete` (provided by the standard library implementation), or a class-specific overload if provided) actually releases the raw memory block back to the heap.

So, roughly speaking,

`delete p;`

expands conceptually to:

```cpp
`if (p) { 
p->~T();               // Step 1: destroy the object     
operator delete(p);    // Step 2: free raw memory
}
```

#### What about `delete[]` ?

When you allocate with:

`T* arr = new T[5];`

C++ must destroy **five separate objects**, not just one.  
So when you later call:

`delete[] arr;`

the runtime must:

 Loop over the elements and call **each destructor**:
    
```cpp
`for (int i = 5; i-- > 0;)    
     arr[i].~T();
```

Finally call:
    
    `operator delete[](arr);`
    


## 5. Threading Concepts (Intro)

Each thread has its own **instruction pointer** (its execution position).

- **What this means:** A **process** (your running program) is an isolated container for resources (memory, file handles). A **thread** is the smallest unit of execution _within_ that process.
    
- **The Analogy:** Think of a large house (the Process) with a single kitchen and pantry (shared memory). If two cooks (Threads) are working in the house, each cook has their own individual **recipe step they are on** (their instruction pointer). They progress independently, but share all the kitchen resources.
    
- **Significance:** Because each thread has its own instruction pointer, they can execute different functions or different parts of the same function _simultaneously_ or _interleaved_.


You can pass **function signatures** (callables) to `std::thread`.

-  **What this means:** When you create a new thread using `std::thread`, you must tell it _what code_ to run. This code is passed as a **callable object**.
    
- **Callables include:** Standard functions, member functions, lambda expressions, and function objects (functors).
    
- **Example (Conceptual):**
```cpp
void task() { /* runs in the new thread */ }
std::thread t(task); // Creates a new thread running 'task'
```
Threads can be **interrupted** or **rescheduled** by the OS.
- - **What this means:** The operating system's **scheduler** manages all the threads running on the system. It periodically **interrupts** one thread's execution to pause it, and then **reschedules** another thread to run on the CPU core.
    
- **The Timing is Non-Deterministic:** You have **no control** over exactly _when_ the OS will interrupt and switch threads. It could be every few milliseconds, or it could be right in the middle of a C++ statement.
    
- **Significance:** This non-deterministic timing is the root cause of **thread hazards** (data races). Since you can't predict when threads will switch, you must assume they can switch at the worst possible moment.
    

###  Thread Hazards
 If **two threads change the same object** → data race → undefined behavior.
    - **Data Race Definition:** A data race occurs when two or more threads access the same memory location concurrently, and at least one of those accesses is a **write** (a change), and there is **no synchronization** mechanism in place.

 Shared **global variables** are especially dangerous.

- **The Risk:** Global variables exist throughout the lifetime of the program and are accessible from any thread function. It's easy to forget that a utility function, called by two different threads, might be silently modifying the same global counter or status flag.
    
- **Principle:** When writing concurrent code, you must assume _all_ access to _any_ global variable is a potential data race unless proven otherwise.

### Shared Resources

##### Any shared resource (heap, file, I/O) must be **protected by a locking strategy**.

Basics: 
what is mutex(the tool)?
- **Role:** The mutex holds the state (either "locked" or "unlocked"). It is the **shared resource** that all threads compete for.
what is lock? (the action)
- The purpose of a lock  is to protect a **specific, shared data structure** or a **block of code** that accesses it. This protected region is called the **critical section**.

- **How it Works:** Before a thread accesses shared data, it **locks** the mutex. If the mutex is already locked by another thread, the new thread **waits**. Once the thread is finished with the data, it **unlocks** the mutex, allowing a waiting thread to take its turn.
    
### `malloc` and `free` internally use **mutexes** to ensure thread-safety.

- **What this means:** The heap (raw memory manager) is the ultimate shared resource. If two threads called `malloc` at the same time, the memory manager could crash.
    
- **Implementation Detail:** To avoid this, the C/C++ standard library wraps its internal memory allocation/deallocation logic in a mutex. When you call `new` (which calls `operator new`, which calls something like `malloc`), your thread silently waits for the internal memory mutex to become free before getting its memory block.
    
- **Significance:** This guarantees that the memory _manager itself_ doesn't crash, but it **does not** protect the data _inside_ the memory block that you allocated. That protection is still your responsibility.
    

### Locking and waiting add significant **performance cost**.

1. **Instruction Overhead:** Locking and unlocking requires the CPU to execute instructions.
        
2. **Waiting Overhead:** If one thread has to pause and wait for another to release a lock, that wait time is wasted time where the core could have been executing other code.

- **Principle:** You should strive to minimize the amount of time a lock is held (the **critical section**) and, even better, restructure your code to avoid sharing data entirely.

---

## 6.Why `new` / `malloc` Are Expensive

1. They lock internally to ensure thread-safe access to the heap.
    
2. The allocator must:
    
    - Find a free memory block (walk the _free list_).
        
    - Possibly split or merge blocks.
        
    - Coordinate with other threads.
        
3. These operations are inherently serialized → **bottleneck**.
    
 _Optimization idea:_

> Avoid the heap when possible — or _steal ownership_ (move semantics) instead of reallocating.

---

## Move Semantics

- Use move when it’s safe to **steal** a resource from another object.
```cpp
String makeString() {
    String s("world");
    return s;  // compiler moves automatically
    //move because the local variable s has no use after this line
}

int main() {
    String b = makeString();
}

```
    


now lets look at this example:
```cpp
// Function returning a temporary
String bar() {
    String temp("Hello from bar()");
    return temp; // compiler knows temp is a temporary
}

// Function taking String by value
void foo(String s) {
    std::cout << "In foo: " << s.data << "\n";
}

int main() {
    std::cout << "Calling foo(bar())\n";
    foo(bar());
}
```

1. **`bar()` is called.**
    
    - It returns a **temporary** `String` object — a nameless value that exists only until the end of the full expression. r value
        
2. The result of `bar()` — that unnamed `String` — is passed into `foo(...)`.
    
3. Inside the function call `foo(String s)`:
    
    - The parameter `s` is constructed from the argument (the temporary result of `bar()`).
        
4. The compiler sees:
    
    - The argument is a **temporary (rvalue)**, not a named variable.
        
    - So it can safely call the **move constructor** of `String` to initialize `s` (since the source will be destroyed right after).
    

That’s how the compiler knows:

> “`bar()` returns a temporary (rvalue) → I can move it into `s` safely.”

🧠 _Insight:_

> “Move semantics is the compiler-sanctioned optimization to avoid heap allocations and expensive copies.”

---

