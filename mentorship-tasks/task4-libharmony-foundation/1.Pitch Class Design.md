Hints on modelling the class from Jonathon:
  - 128 distinct pitches/keys in a Grand piano
  - assume even tempered Tuning
  - assume scientific pitch Notation(Wikipedia)
  - assume midi convention for note numbers
  - assume A4=440Hz(Concert A Tuning)

## Thoughts while designing the pitch class:

### step 1: clarifying the semantics

A `pitch` represents a musical note identified by its **MIDI note number**, under the **equal tempered scale** and **A4 = 440 Hz** tuning.

It’s a **discrete value type**.  i.e., it represents one of 128 equally spaced semitones, not a continuous variable

**mental model:**

Domain: Integers 0 -> 127
Each integer corresponds to unique musical pitch
we will provide 2 views:
- midi() - the numeric code
- frequency() - frequency

## step 2: thinking about storage

simplest internal representation

```cpp
private:
  uint8_t midi_note_; // 0-127
```

frequency is not stored seperately since it can be derived each time from the midi_note_
which would make the class simple (fully defined by one integer)

## step 3:  identifying the invariants
- 
 0<= midi_note_ <=127, this invariant has to be used in the constructor

## step 4. thinking about special member functions

the compiler can automatically generate:
1. Default constructor
2. copy ctor
3. copy assignment operator
4. dtor
5. move ctor
6. move assignment operator

now whether you need to define them yoursefl depends on what is inside the class.

the internal structure of pitch is this:
```cpp
class pitch 
{
private: 
  uint8_t midi_note_;
}
```

the internal member of the class is just a simple byte. no heap allocation needed.
-> which means trivially copyable and destroyable
**bitwise copy** of midi_note is fine


we can keep this (user defined constructor):

```cpp
pitch(int midi_note = 60);
```
and in this constructor we can define invariants (that it should be between 0 and 127)

and let the compiler generate:
- `pitch(const pitch&) = default;`
    
- `pitch& operator=(const pitch&) = default;`
    
- `~pitch() = default;`


```
Rule of zero:
---------------
If your class doesn’t own resources, then you don’t need to explicitly define copy/move/destructor.  
Let the compiler generate those automatically.
```

## step 5: defining responsibilities: what operations make sense for pitch?

##### 1. accessors

```cpp
int midi() const;
double frequency() const;
```

for frequency():
  F = 440 × 2^((n-69)/12

usage:
```
harmony::pitch p(60);
p.midi(); // gives you the midi note
p.frequency() //gives you the frequency
```

since neither function modifies the object, we can make it const

these are the basic getters

##### 2. mutations - member functions

compound assignment operators would be nice:
usage:
```cpp
p+=2;
p-=1;
```
where 2, 1 are semitones

##### 3. arithmeic
```cpp
pitch operator+(pitch lhs, int semitones);

  pitch operator-(pitch lhs, int semitones);

  pitch operator-(pitch lhs, pitch rhs);
```

**rule of thumb: For small, trivially copyable types (size ≤ 2 doubles ≈ 16 bytes), pass by value.**

otherwise you could pass it by const reference. here the pitch class has only one uint8_t, just pass it by value

##### 4.utilities
- one function to give the scientific pitch notation name (eg. C4, D7 etc)
- one function to give the octave number
- one function to check if to pitches are octave equivalent
```cpp
  bool is_octave_equivalent(pitch lhs, pitch rhs);

  std::string name(pitch p);

  uint8_t octave(pitch p);
```


