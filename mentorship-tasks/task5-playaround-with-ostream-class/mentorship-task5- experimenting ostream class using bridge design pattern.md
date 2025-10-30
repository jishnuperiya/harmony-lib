**Theme**: 
- **Focus:** Bridge pattern, typesafe I/O, polymorphism basics
- **Date:** october 2025  
**Objectives:**
The main objective was to play around with the ostream class and streambuf class and understand how it works under the hood conceptually and also understand the bridge pattern. to achieve this i created these tiny objectives:
- implement a tiny ostream class which bridges to a streambuf implementation
- an abstract streambuf interface on implementation side
- 2 buffers (consolebuf and filebuf) as concrete implementations
- operator<< overload in the ostream class
- demonstrate bridge pattern
- practice basic api design


**ios original design**

ios
|
ostream -> streambuf
			|
		   filebuf

- `ostream` IS an ios (inheritance), whereas `ostream` HAS a `streambuf`(delegation via a pointer - the 'bridge')

|Concept|Relationship Type|Example|Meaning|
|---|---|---|---|
|`ostream` **IS** an `ios`|**Inheritance (is-a)**|`class ostream : public ios { ... };`|`ostream` inherits functionality from `ios`, so it _is a specialized form_ of it.|
|`ostream` **HAS** a `streambuf`|**Composition / Delegation (has-a)**|`streambuf* m_buf;` inside `ostream`|The `ostream` _contains_ a `streambuf` pointer and delegates the actual I/O operations to it (that’s the Bridge pattern).|

how to distinguish visually?

- inheritance( IS-A) : solid line with triangle arrow in UML
- Delegation/composition (HAS-A) : line with diamond or plain arrow


## conceptual overview

### Design

**pattern** : bridge

| Bridge Role               | Class                          | Description                                           |
| ------------------------- | ------------------------------ | ----------------------------------------------------- |
| **Abstraction**           | `my_ostream`                   | High-level interface used by clients to send output.  |
| **Implementor**           | `my_streambuf` (abstract base) | Defines the low-level output interface.               |
| **Concrete Implementors** | `my_consolebuf`, `my_filebuf`  | Provide destination-specific output (console / file). |
The design allows new output destinations (new sinks like a network stream) without modifying my_ostream.

- polmorphism through pure virutal class (my_streambuf)
- seperation of abstrction(my_ostream) from implementation (my_streambuf derivatives)
- resource management and RAII (my_filebuf owns a file handle)
- low level I/O using `<cstdio>` API
- operator<< overloading (remember again: its just  a fn with a infix synatax)


## Rationale behind 'operator<<' design

c++ replaced C's `printf` with **type safe, extensible and composable stream abstraction**

printf used runtime format strings and variadic arguments -> the compiler couldnt check types and handle user defined classes.

stroustrup introduced streams and operator overloading (<<) so that each overload corresonponds to a real type (that way it can be extended with user defined type as well) -> type safety and extensibility

each `operator<<` :
- write to the stream
- and return the same stream (ostream&) -> enables chaining
(if it had retunred void, the chaining wouldnt have happened)


**ostream** : abstraction
**streambuf and subclasses**: implementations

`decouple abstraction from implementations so that they can vary independently` -> **Bridge PAttern**

This design made the C++ I/O:
- **type safe**: compiler checks overloads
- **extensible** : user types can defin operator<<
- **composable** : chained expressions enabled






