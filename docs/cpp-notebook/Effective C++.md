

# 1) View C++ as a federation of languages

in the beginning, people said: c++ is c with some object oriented features -  thats when the called "c with classes" - reflected this heritage

but language matured. now its a **multiparadigm programming language**
combination of **procedural** **object oriented, function, generic and meta progrmaming features**

see c++ as not as a single language but federation of related languages. within a sub language rules seems straightforward and when youchange from one sublanguage to other: rules may change

4 primary sublanguages:
- **C** : simple. no exceptions, no templates, no overloading etc
- **Object Oriented C++** : classes, encapsulation, inheritance, polymorphism, virtual functions (dynamic binding) etc. - classic part of c++ where the classic rules for OOPS design most directly apply
- **Template C++** : too powerful. generic programming part. gave rise to new programming paradigm - template meta programming (tmp)
- **STL** : stl is a template library. containers, iterators, algorithms and function objects mesh beatifully.

it can be that the effecitve programming strategy changes when changing from one sublanguage to another. For example:

pass by value is cheaper than pass by reference when workig wth built in types (C like)
pass by reference is usually better when working with object oriented C++.
pass by reference is also better with tempaltes becuase you dont even know what type you will be passing to
when you cross to STL, the iteraotr and functon objects are modeled as pointers (C) - again pass by value is better.

**Remeber**
 **C++ isnt a single language with single set of rules. its a federation of 4 sub languages, each with its own conventations. if you have those 4 sublanguages in mind, you will find that c++ is musch easier to understand**


# 2) Prefer Consts, enums  and inlines to \#defines


`# define ASPECT_RATIO 1.653`
the symbolic name ASPECT_RATIO may never be seen by the compiler: it may be removed by the preprocesser before the srouce code ever gets to a compiler. (preprocesser do text replacement)

so hard to debug

**solution**
- replace the macro with a constant
`const double AspectRatio = 1.653`

AspectRatio is a language constant - therefore defenitely seen by compilers and is certainly entered into their symbol tables.

substituition of ASPECT_RATIO with 1.653 may yield in multiple copies in object code, but with athe constant AspectRAtio wouldnt result in more than one copy.


to ensure the special case of class specific constants, you make it a membre and to enusre that there is at most only one copy of the constant (and no constrcution cost multiple times) you make it a static member
(on the other note: there is no way to create a class specific constant using `#define`)



