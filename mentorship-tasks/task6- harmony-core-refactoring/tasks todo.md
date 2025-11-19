
## **PHASE 1 — Clean Up Existing Code (Foundations)**

### **Task 1 — Move `note_names` to a static/constexpr location**

**Goal:** Remove reconstruction inside `harmony::name()`.

-  Create
    
    `inline constexpr std::array<const char*, 12> note_names{ ... };`
    
    in a header (`harmony/note_names.hpp`).
    
-  Update `harmony::name()` to use this.
    

---

### **Task 2 — Rewrite `harmony::name()` using `ostringstream`**

Replace string concatenation with:

`std::ostringstream os; os << note_names[note_idx] << harmony::octave(p); return os.str();`

-  Remove unnecessary temporaries
    
-  Add Doxygen comment
    
-  Ensure function is `const`
    

---

### **Task 3 — Make `pitch(int)` constructor use `assert`**

-  Replace throw with:
    
    `assert(midi_note >= 0 && midi_note <= 127);`
    
-  Keep conversion to `uint8_t`
    
-  Add Doxygen stating valid range is caller responsibility
    

---

## **PHASE 2 — Redesign `chord` Class (Internal Representation)**

### **Task 4 — Redesign `chord` private storage**

Implement:

`note                 const root_; std::array<bool,12> const notes_;`

-  Remove old `vector<note>` storage
    
-  Rename enum to be inside the class (`chord::quality`)
    
-  Add Doxygen to document invariants
    

---

### **Task 5 — Implement the template constructor**

`template<typename NoteIt> chord(note r, NoteIt b, NoteIt e);`

This constructor must:

-  Set `root_`
    
-  Initialize all `notes_` to `false`
    
-  For each note in `[b, e)`:
    
    - Compute pitch-class index
        
    - Set `notes_[index] = true`
        

---

### **Task 6 — Implement `get_notes()` using iteration on `notes_`**

-  Iterate over `notes_`
    
-  For each `true`, convert index → `note`
    
-  Use `std::vector<note> result(begin,end)` pattern (no mutation)
    

---

### **Task 7 — Implement `get_pitches(int octave)` using iterators**

Jonathan’s hint: _construct the vector at the point of construction_.

-  Call `get_notes()`
    
-  Create a lambda iterator that converts note→pitch
    
-  Construct vector using iterator pair
    
    `std::vector<pitch> pitches(first, last);`
    

---

## **PHASE 3 — Add Factory Functions (Musical Construction)**

### **Task 8 — Implement `make_triad(note, chord::quality)`**

-  Major: 0, +4, +7
    
-  Minor: 0, +3, +7
    
-  Diminished: 0, +3, +6
    
-  Augmented: 0, +4, +8
    

---

### **Task 9 — Implement `make_chord(note root, std::initializer_list<note> ns)`**

Allows:

`auto c = make_chord(C, {C, E, G, B});`

---

### **Task 10 — Implement `make_polychord(chord a, chord b)`**

-  Use operator+ internally
    

---

## **PHASE 4 — Add Set-Based Operators**

### **Task 11 — Implement `operator+(const chord&, const chord&)`**

**Union**: for each index i:  
`result.notes_[i] = a.notes_[i] || b.notes_[i];`

---

### **Task 12 — Implement `operator-(const chord&, const chord&)`**

**Difference**:  
`result.notes_[i] = a.notes_[i] && !b.notes_[i];`

---

## **PHASE 5 — ChordProgression Refinement**

### **Task 13 — Replace container constructor with iterator constructor**

`template<typename ForwardIt> chord_progression(ForwardIt b, ForwardIt e)   : chords_(b, e) {}`

-  Delete old container constructor
    
-  Add overload for `initializer_list` that forwards to iterator ctor
    

---

## **PHASE 6 — Apply Zero-Cost Abstraction Principles**

### **Task 14 — Make functions constexpr where possible**

Examples:

- `pitch::get_frequency()`  
    Move constant definitions (`alpha`) to `constexpr` static
    
- Literal-based operations
    
- Interval computations
    

---

### **Task 15 — Remove unnecessary temporaries across all code**

Examples:

- Avoid `std::string temp = ...`
    
- Prefer `ostringstream`
    
- Prefer `return <expression>;`
    
- Avoid `vector.push_back` when you can construct directly
    

---

## **PHASE 7 — Documentation & Tests**

### **Task 16 — Add full Doxygen comments**

For:

- pitch
    
- note
    
- chord
    
- chord_progression
    
- factory functions
    

---

### **Task 17 — Add test cases**

Examples:

- `C Major == {C, E, G}`
    
- Polychord union
    
- Remove 3rd → power chord via `operator-`
    
- Out-of-range pitch values caught by assert in debug
    

---

# ⭐ **Your Immediate Next Step (Today)**

Start with **Tasks 1–4**:

1. Move `note_names`
    
2. Rewrite `name()`
    
3. Replace throw with assert
    
4. Redesign `chord` internal structure
    

These will make the rest easier and give you visible progress fast.