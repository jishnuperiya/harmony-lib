
read cpprefernce on preprocesser

a.cpp after flattening preprocesser - TU
actual TUis enormous- it include half of STL

ODR - 
only linker can see if ODR violates

defnition vs declration
declaration is weaker. 
youwant to both to work arund mutual recursion

inline  on a def says pick this up and discard ODR

dont want to use inline a cpp file. has to be defined in header to avoid ODR
****


note cpp

note idex from name

enharmonic nmaes

  for (auto const& [name, index] : std::initializer_list<std::pair<std::string_view, int>>{
      
     {"C", 0},  {"B#", 0},
     {"C#", 1}, {"Db", 1},
     {"D", 2},
     {"D#", 3}, {"Eb", 3},
     {"E", 4},  {"Fb", 4},
     {"F", 5},  {"E#", 5},
     {"F#", 6}, {"Gb", 6},
     {"G", 7},
     {"G#", 8}, {"Ab", 8},
     {"A", 9},
     {"A#", 10},{"Bb", 10},
     {"B", 11}, {"Cb", 11} })
  {
    if (s == name)
      return index;
  }
  throw std::invalid_argument("Invalid note name");
}


anonymus namespace

compiler generate some identifieer.

everything unders this scope all get a unique identifier- prevent name clashing
also get internal inkage

---
now we have too many implicit coercion

defazkt for ctor to be implicit should be marked not default

115: explicit

put in single arg ctor dont want the compiler 

if the list is longer- we want to dobinary serach-

---
note_names array

need proper parser. what if cliet give small letters or whitespace

--
int 
ring and grpup

---
auto x = chord{}

transposing c major trida
transosing c 
transpose pitch

tranpose voice

transpose a polymprhpic

template

---
set operations

c dorian && d dorian

