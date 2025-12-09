# Leranings from PR




```cpp
  note note_from_name(std::string_view s)
  {
    for (auto const& [name, n] : std::initializer_list<std::pair<std::string_view, note>>{
      
      {"C", note(0)},  {"B#", note(0)},
      {"C#", note(1)}, {"Db", note(1)},
      {"D", note(2)},
      {"D#", note(3)}, {"Eb", note(3)},
      {"E", note(4)},  {"Fb", note(4)},
      {"F", note(5)},  {"E#", note(5)},
      {"F#", note(6)}, {"Gb", note(6)},
      {"G", note(7)},
      {"G#", note(8)}, {"Ab", note(8)},
      {"A", note(9)},
      {"A#", note(10)}, {"Bb", note(10)},
      {"B", note(11)}, {"Cb", note(11)}
})
    {
        if (s == name)
            return n;
    }
    throw std::invalid_argument("Invalid note name");
  }
}
  note::note(uint8_t value)
    : note_{static_cast<uint8_t>(value % 12)} 
  {}

  note::note(std::string_view s)
	  : note (note_from_name(s))
  { }

  ```

  first i had the idea to use a map as a global variable to map string names to note values, but then i realized that a simple loop over an initializer list would be more straightforward and avoid the overhead of a map. this way, we can easily add or modify note names in one place without worrying about map initialization order or performance issues.

  but jonathon changed it to a initializer list and moved in the for loop to avoid the global variable.
  ```
  the advantages of this approach are: 
  - no increase in binary size
  - no static data
  - no global storage
  - no memory beyond call
  - no global side effect
  ```


  # Questions for jonathan:
isnt it better to use a static const map inside the function to avoid re-creating the initializer list on each call?

---
# set_intersection
intersection
defined in <algorithm>
you give it iterators.
iterators need to be forward iterators or better.
if you use std::set<note> directly, its iterators are not compatible with std::set_intersection.
set provides bidirectional iterators, but std::set_intersection requires at least forward iterators.


how to read the cpprefernce:

```cpp
template< class InputIt1, class InputIt2, class OutputIt >
OutputIt set_intersection( InputIt1 first1, InputIt1 last1,
                           InputIt2 first2, InputIt2 last2,
                           OutputIt d_first );
```

Human meaning:

�Given two sorted ranges [first1, last1) and [first2, last2),
write the intersection into d_first,
and return the iterator pointing to the end of the output.�

first 4 are input iterators. and the last one is output iterator.
output iterator means you can write to it.

example:

```cpp

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
 
int main()
{
    std::vector<int> v1{7, 2, 3, 4, 5, 6, 7, 8};
    std::vector<int> v2{5, 7, 9, 7};
    std::sort(v1.begin(), v1.end());
    std::sort(v2.begin(), v2.end());
 
    std::vector<int> v_intersection;
    std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(),
                          std::back_inserter(v_intersection));
 
    for (int n : v_intersection)
        std::cout << n << ' ';
    std::cout << '\n';
}

```

what is `std::back_inserter`?
`std::back_inserter` is a standard library function that creates an output iterator which appends elements to the end of a container. It is typically used with containers like `std::vector`, `std::list`, or `std::deque`.
When you use `std::back_inserter`, it returns an iterator that, when dereferenced and assigned a value, will call the `push_back` method of the container. This allows algorithms that require output iterators to add elements to the container without needing to know its size in advance.

in the case of set container we cannot use back_inserter because set does not have push_back method.


- in normal iterator, *out = value; means assign value to the location pointed by out.
- in inserter, *out = value; means call container.insert(value);
- in back_inserter, *out = value; means call container.push_back(value);
- in front_inserter, *out = value; means call container.push_front(value);
- in ostream_iterator, *out = value; means call ostream << value;
- in istream_iterator, *in reads value from istream >> value;
- etc.

---

## usage of contains and find

```cpp
 notes_t C_major_notes = { note("C"), note("E"), note("G") };
  C_major_notes.insert(note("B"));
  assert(C_major_notes.contains(note("B")));
  assert(C_major_notes.find(note("B")) != C_major_notes.end());
    C_major_notes.erase(note("B"));
```


For std::set, std::map, std::unordered_set, and std::unordered_map, the member function:
`s.contains(x)`

is just a clean wrapper around:

`s.find(x) != s.end()`

so the implementation is basically: 

```cpp
bool contains(const key& x) const
{
  return find(key)!=end();
}

```

for std::set and std::map (tree based) find and contains are O(log n)

for std::unordered_set and std::unordered_map (hash based) find and contains are O(1) on average.
---

# SET container

```cpp
template<
    class Key,
    class Compare = std::less<Key>,
    class Allocator = std::allocator<Key>
> class set;
```
from this you undrestand:
- first param is essential. u pass the type here
- second param is default. uses std::less<your type>, which inturn call your opertor<
- third parameter is default, uses std memory allcoator for your type, new/delete. no needc to care now


---
since std::set handles all the work and the wrapper owns no memory, you dont need the 
- copy constructor

- move constructor

- copy assignment operator

- move assignment operator

- dtor

RULE OF FIVE:

if the compiler manuaally generate any of these 5:

- copy ctor
- copy assignment
- move ctor
- move assignment
- dtor

you have to define all 5 (bcoz the class likely manage some resources manually)

*rule of 5 does NOT include the default ctor or any normal ctor*




---

# my first implmentation of note set

```cpp
//******** Copyright � 2025 Jishnu Periya, Jonathon Bell. All rights reserved.
//*
//*
//*  Version : $Header:$
//*
//*
//*  Purpose : wrapper class over std::set for musical notes
//*
//*
//****************************************************************************
#pragma once

#include<set>									// For std::set
#include<utility>							    // For std::pair
#include "harmony.hpp"							// For harmony::note

//****************************************************************************

namespace harmony
{
	class note_set
	{
	public:
	  using iterator = std::set<note>::iterator;
	  using const_iterator = std::set<note>::const_iterator;

	  note_set() = default;
		
	  template <typename InputIt>
	  note_set(InputIt b, InputIt e)
		: notes_(b,e){}

	  std::pair<iterator, bool> insert(const note& n)
	  {
	    return notes_.insert(n);
	  }

	  std::size_t erase(const note& n)
	  {
	    return notes_.erase(n);
	  }

	  iterator find(const note& n)
	  {
        return notes_.find(n);
	  }

	  bool  contains(const note& n)
	  {
		return notes_.contains(n);
   	  }
	  
	  iterator begin()
	  {
		return notes_.begin();
	  }

	  const_iterator begin() const
	  {
		return notes_.begin();
   	  }

	  const_iterator cbegin() noexcept
	  {
		return notes_.cbegin();
	  }

	  iterator end()
	  {
		  return notes_.end();
	  }

	  const_iterator end() const
	  {
		return notes_.end();
	  }

	  const_iterator cend() noexcept
	  {
		return notes_.cend();
	  }
	
	private:
	  std::set<note> notes_;
	};
}
```

now we will change the internal representation to use uint16_t bits_ instead of std::set<note>


## bit operations basics

we have 12 pitch classess:

```cpp
0  = C
1  = C#
2  = D
3  = D#
4  = E
...
11 = B

```


if a bit is present the pitch class is present in the set.

if a bit is 0, it is absent

example: c major triad: C E G
```cpp

C -> bit 0 = 1
E -> bit 4 = 1
G -> bit 7 = 1
bits = 10010001 = 0x91
```

### the 3 basic bit operations we need are:
- set a bit
- clear a bit
- check if a bit is set
- set a bit:
```cpp
bits_ |= (1 << n);
```
- clear a bit:
```cpp
bits_ &= ~(1 << n);
```
- check if a bit is set:
```cpp
return (bits_ & (1 << n)) != 0;
```
---
funciton objects: objects that acts like functions. such objects come from classes the overload operator(), the fucntino call operator
---
