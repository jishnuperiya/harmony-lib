
this is the notes/hints that he gave me:

pitch
  128 distinct pitches/keys in a Grand piano
  assume even tempered Tuning
  assume scientific pitch Notation(Wikipedia)
  assume midi convention for note numbers
  assume A4=440Hz(Concert A Tuning)
frequency
  represented as a double
  an audible frequence measured in Hertz (wiki)
notes
note
scale
scale_type
chord
voicing
interval
  diff between 2 pitches. number of half pitches


also these tips:
2 pitches are octave equivalent if the Ratio of their freq is power of 2
2 pitches are octvae equivalent if the difference of their pitch number is div by 12


he said lets make everthing in a single file:harmony.hpp

he said first lets only make 3 classes: pitch, ferquency and note



## **Task**

We will build a **C++ harmony library**.

**Goal:** Start implementing fundamental classes to represent musical concepts, using the first three classes as a foundation.

---

## **Classes to Implement First**

1. **Pitch**
    
2. **Frequency**
    
3. **Note**
    

---

## **Hints / Notes from Mentor**

### **Pitch**

- Represents **how high or low a note sounds**.
    
- Piano has **128 keys** (MIDI 0–127).
    
- Standard tuning: **A4 = 440 Hz** (Concert A).
    
- Use **scientific pitch notation**.
    
- **Octave equivalence:**
    
    - Two pitches are octave equivalent if:
        
        - Frequency ratio is a power of 2, **or**
            
        - MIDI number difference is divisible by 12.
            
- **Interval:** difference between two pitches in **half steps** (semitones).
    

### **Frequency**

- Represented as a **double**.
    
- Measures the vibration of sound in **Hertz (Hz)**.
    
- Example: A4 = 440 Hz.
    

### **Note**

- Represents a musical note with a pitch and possibly other metadata.
    
- Can be associated with a **scale**, **chord**, or **voicing** later.
    

---

## **General Tips**

- Start by keeping **everything in a single file**: `harmony.hpp`.
    
- Implement the **first three classes only** for now.
    
- Think about **value semantics** and safe memory handling for your classes.
