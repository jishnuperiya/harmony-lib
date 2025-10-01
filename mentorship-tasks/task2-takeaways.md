
# Special Member Functions — Summary

**The 6 SMFs (Rule of 6):**
- Default constructor
- Copy constructor
- Copy assignment operator
- Move constructor
- Move assignment operator
- Destructor

**Rules:**
- Rule of 0: don’t declare any → compiler handles everything (ideal if possible).
- Rule of 3: traditionally (pre-C++11) — if you define copy ctor/assignment or destructor, define all three.
- Rule of 5: modern version (copy + move + destructor).
- Rule of 6: same as Rule of 5, but also counting the default constructor.

**Default constructor:**
- Generated if you declare no other constructors and all members are default-constructible.
- *Value initialization* (`{}`) zeroes fundamental types + calls default ctors for members.
- Writing an empty ctor yourself disables that benefit — use `= default` instead.
- Prefer initializer lists over assignment in ctor body.

**Destructor:**
- Generated if you don’t declare one.
- Compiler-generated dtor destroys class-type members, but doesn’t delete raw pointers.
- Only write your own if you manage a resource; otherwise prefer `= default`.

**Copy operations:**
- Generated if not declared and if no move operations exist, and if all members are copyable.
- Declaring a move ctor or move assignment suppresses copy operations.
- Some members (like `unique_ptr`) make copying unavailable.

**Moves:**
- Generated if no copy operations are declared, and all members are movable.

**Key guideline:**
Prefer the Rule of 0 if possible.  
If you need custom behavior, follow Rule of 5.  
Avoid empty ctors/dtors — let compiler generate them or use `= default`.
