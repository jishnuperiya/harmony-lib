
implementing the operator+= for the pitch class:
```cpp
harmony::pitch& harmony::pitch::operator+=(int semitones)
{
  //implementatin here
  return *this;       
}
```
the midi_note_ is uint8. and the semitones is int.

how to perofrm the arithmetic properly?

option 1: first convert semitones to uint8. then add with midi_note_
**wrong** why? - semitones **can be negative and you end up getting wrap around value. since uint8 is unsigned integer.**

so the only option: upgrade midi_note_ to int and then do arithmetic and later cast the result to uint8_t

