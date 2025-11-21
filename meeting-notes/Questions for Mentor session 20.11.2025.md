
things to ask:

1. pitch class's internal representation is of type unit_8. it can be implicityl converted to a char. check first during debugging and ask jonathon later. for example, while streaming does it converterd to an unsigned char? shoud i use uint16_t -> see note 2

- in pitch class new construtor added -> pitch(frequency) // is there a better way to do it
- pitch class implementation - wrapped everything in a hamrony namespace
- added static constexpr to note_names[12] -> note 1. should i outsource the notenames to filescope. if yes. in header file?

- what is the order of including header files?
chatgpt said:  safe rule is to include the header that the .cpp implements first, then blank line, then other project/3rd‑party headers, then standard headers

- assert in operaotr+= or no?
  
  ```cpp
frequency& frequency::operator+=(double delta_hz)
{
    hz_ += delta_hz;
    assert(hz_ > 0.0);
    return *this;
}
  ```

or nothing? assert doesnt affect zero cost build in release right?


- added this :
  
  ```cpp
    inline constexpr std::array<const char*, 12> NOTE_NAMES = {
    "C", "C#", "D", "D#", "E", "F",
    "F#", "G", "G#", "A", "A#", "B"
  };
  ```
  at harmony.hpp filescope.
because its used by both pitch.cpp and note.cpp
and std array over array obvious reasons, zeor cost
no need to define it static. it has static storage anyway. inline to be included in multiple TUs


- chatgpt says i could use string view here to avoid creating string each time (heap allocation):
```cpp
std::string harmony::note::name() const
{
  return NOTE_NAMES[note_];
}
```
does it matter, isnt the note names tiny and SSO is triggered?

- ```cpp
  harmony::note& harmony::note::transpose(int semitones)
{
  note_ = static_cast<uint8_t>((((int)note_ + semitones) % 12 + 12) % 12);
  return *this;
}

  ```
is it too much ? should have used temporray?

- added ENHARMONIC NAMES as pair. since pair is just a struct, zero runtime overhead?
use string view when we dont need ownership of the string?

- when i have a struct which has 2 members
  
  uint8_t
   int
then the compiler add paddding after uint8 (3 bytes). should we add explicitly add padding the way we want to have control of the class representation in memory?

- i have implemented the get_pitches in the chord.cpp file. is there any way to make it better


# notes

## 1 static constexpr
```cpp
 std::string name(pitch p)
 {
   static constexpr const char* note_names[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
   int note_idx = p.get_midi() % 12;
   std::string note_name = note_names[note_idx];
   std::string scientific_notation = note_name + std::to_string(octave(p));
   return scientific_notation;
 }
```


here static constexpr gives 2 advantage.

static - only one time construction
constexpr - no runtime overhead

## 2 why cast uint8_t to int

```cpp
  std::string name(pitch p)
  {
    static constexpr const char* note_names[12] = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };
	
    std::ostringstream oss;
	oss << note_names[p.get_midi() % 12] << static_cast<int>(octave(p));
	
    return oss.str();
  }
```

here octave(p) returns a uint8_t which is an alias to unsigned char in most platforms. which can be streamed as a character.


# 3 Assert happens in debug build

when assert happens then the program aborts()

no exception is thrown no chance to recover
Once assert fails → program stops → debugger breaks exactly on that line.

In Visual Studio, it pauses execution and takes you straight to the failure.

in release build, assert does nothing:
```cpp
#ifdef NDEBUG
#define assert(expr) ((void)0)
#endif
```
assert becomes ((void)0)
no check
no cost
no instruction executed

- ctor must stay fast. so no runtime overhead


# 4 string view over string

- string view doesnt allocatge or owns memory
if i had used std::pair<std::string, int>,

for every note, like "C", it would hvae constructed a string object
sometime allcoate memory (depending on SSO)

even with SSO you are still constructing  around 20+ string ojbects 

with string view, 
- no memory alloc
- no copyong
- i just stores a ointer + length referring to the string literal (string literal already exist in  the static memory)
