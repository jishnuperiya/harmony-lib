https://youtu.be/9BM5LAvNtus?si=a75N4XzF5_a7sqrP
Speaker: Klaus Iglberger

special member functions: functions that a compiler may generate for you.

**task**: name all the compiler generated functions:
- default constructor
- copy constructor
- copy assignment operator
- move constructor
- move assignment operator
- destructor

```cpp
class Widget{
Widget(); //default ctor
Widget(Widget const&); // copy ctor
Widget& operator=(Widget const&); // copy assignment operator
Widget(Widget&&) noexcept; // move ctor
Widget& operator=(Widget&&) noexcept; //move assignment operator
~Widget();
};
```

These functions, the compiler may generate for you, depending on the situation.
These are also the fundamental functionality of a class, copy functionality, move functionality, cleanup and ofcourse the default initialization.

**Rule of 6** : when people talk about this, what they mean is that all of these functions are somewhere defined.

**Rule of 5**: people talking about these functions except the default constructor. That one is not that special afterall. These remaining five are probably most important.

```cpp
class Widget{
//Widget(); //default ctor
Widget(Widget const&); // copy ctor
Widget& operator=(Widget const&); // copy assignment operator
Widget(Widget&&) noexcept; // move ctor
Widget& operator=(Widget&&) noexcept; //move assignment operator
~Widget();
};
```

**Rule of 3**: not quiet updated. when people talk about this traditionally it means, somewhere you have defined the copy operations and the destructor.

```cpp
class Widget{
//Widget(); //default ctor
Widget(Widget const&); // copy ctor
Widget& operator=(Widget const&); // copy assignment operator
//Widget(Widget&&) noexcept; // move ctor
//Widget& operator=(Widget&&) noexcept; //move assignment operator
~Widget();
};
```
its not quiet upto date anymore but still might be relevant.

**Rule of 0**: so often you hear people talk about rule of zero! means the class doesnt have the explicit defenitions of any of these 6 SMFs.  This is good! This is kind of the best that you can have and this is the goal. 

```cpp
class Widget{
//Widget(); //default ctor
//Widget(Widget const&); // copy ctor
//Widget& operator=(Widget const&); // copy assignment operator
//Widget(Widget&&) noexcept; // move ctor
//Widget& operator=(Widget&&) noexcept; //move assignment operator
//~Widget();
};
```

Lets talk about these 6 special member functions in order..


# 1. Default Constructor

### When the compiler generate a default constructor

#### compiler generate it if you have no other constructor in your class.

```cpp
//compiler generated default constructor available
class Widget{
public:
   // ....
};

Widget w1; // compiler generated, ok
Widget w2{}; // compiler generated, ok
```


you can create the widgets in these 2 possibilities:
```cpp
Widget w1; // compiler generated, ok
Widget w2{}; // compiler generated, ok
```

with paranthese not possible due to the so called vexing parse.
```cpp
Widget w3(); // not possible! - vexing parse
```

### When the compiler doesnt generate the default consturctor

#### case 1: If you have any other constructor in your class then the default constructor is disabled.
```cpp
// no compiler generated default constructor available
class Widget{
public:
   Widget(Widget const&); 
   // explicit declaration of the copy ctor, no default ctor available
};

Widget w1; // no default consturctor, compilation failed!!
Widget w2{}; // no default consturctor, compilation failed!!
```
#### case 2: I have a data member which doesnt have a default constructor

```cpp
// No compiler generated default constructor available
class Widget{
public:
   // ...
private:
	NoDefaultCtor member_; // Data member without default ctor
};

Widget w1; // no default consturctor, compilation failed!!
Widget w2{}; // no default consturctor, compilation failed!!
```
if you have a data member without a default ctor, the compiler will drop the hand and say i have no idea how to default constructor for this member.


#### Basics:
**vexing parse**:
the most vexing parse is a specific syntactic ambiguity resolution in the c++ programming language. The term was used by the scott meyers in effective STL . it means that whatever that can be interpreted as a function declaration will be interpreted as a function declaration. 

in this example below the user wanted to create a string object foo and call a default constructor:
```cpp
std::string foo();
```
but what happens is that the above line will be interpreted as a function declaration by the compiler. We here just declared the function called foo, taking no parameters and returning a string. Whereas we only wanted to call the default constructor!
So to declare a object by calling default constructor, dont use parantheses and avoid the vexing parse issue.
### Default Constructor Task : Data member initialization

**Task**: What is the initial value of the three data members i, s and pi ?

```cpp
struct Widget{
	int i;  // a fundamental type
	std::string s; // a class type aka user defined type
	int* pi; // a fundamental type
};

int main(){
	Widget w;  // Default initialization
}
```
**Answer**:
```
i  - uninitialized
s  - initialized to empty string (default ctor of string is called)
pi - uninitialized
```

If your struct Widget doesnt have explicity defined constructor from you and relying on the default constructor given by the compiler, then :
- the default ctor initializes all the data members of class (user defined) type, based on their own initialization routine
- but not the data members of fundamental type

**question to mentor**:
- when i write a default ctor myself, is that called default ctor or something eles. is default ctor is called that only when the compiler generat it????

instead of default initialization , i am now going to use the **value initialization** - empty set of braces

```cpp
struct Widget{
	int i;  // a fundamental type
	std::string s; // a class type aka user defined type
	int* pi; // a fundamental type
};

int main(){
	Widget w{};  // value  initialization
}
```

this fundamentally changes behaviour.

```
i  - initialized to zero!
s  - initialized to empty string (default ctor of string is called)
pi - initialized to nullptr
```

so with the **value initialization** you have the added bonus that if first zero initialize all the data members and then call the default ctor for all the user defined types in the member list.

**note**: if no default constructor is declared, a value initialization ..
- zero initialize the object
- and then default initialize all non trivial data members

```
GuideLine
---------
Prefer to create default objects using empty set of braces (value initialization)

```


If you write an empty **explicit default construtor** then the class members of user defined types are default initialized and the members of fundamental types are uninitialized. even the brace initialization { } cannot save you anymore.

```cpp
struct Widget{
	Widget() {}; // explicit default constructor
	int i;  // a fundamental type
	std::string s; // a class type aka user defined type
	int* pi; // a fundamental type
};

int main(){
	Widget w{};  // value  initialization: here only user defined data members are initialized and fundamental types are uninitialized since you wrote an empty explicit default constructor
}
```
so dont write an empty explicit default constructor.

**better: ask for the default** (=default)

```cpp
struct Widget{
	Widget() = default; // ask for the default ctor
	int i; 
	std::string s; 
	int* pi; 
};

int main(){
	Widget w{};  // value  initialization: works well again!
}
```

some points i didnt understand :
- =default works as defenition
- =default may give you couple of bonus effects (eg noexcept)

```
Guideline
---------
Avoid writing empty default constructor. prefer to let the compiler provide a defenition or define it by =default
```

 It can be that you want to initialize the object to a specific state. In that case you can create an explicit default ctor and initialize the data members to the desired state:

```cpp
struct Widget{
	Widget(){
	  i = 42;        // Initialize the int to 42
	  s = "CppCon";  // Initialize the strng to "CppCon"
	  pi = nullptr;  // Initialize the ptr to nullptr
	}
	int i; 
	std::string s; 
	int* pi; 
};
```

**Actually the comments are lying. this is not initialization. This is Assignment!!!**

**corrected version**
```cpp
struct Widget{
	Widget(){
	  i = 42;        // Assignment, not initialization
	  s = "CppCon";  // Assignment, not initialization
	  pi = nullptr;  // Assignment, not initialization
	}
	int i; 
	std::string s; 
	int* pi; 
};
```

**Assignment** = changes an object (uses assignment operator)
**Initialization** = calling a constructor

So where are the data members initialized when you call the constructor? -> before you enter the body of the constructor . In the **member initializer list**


```cpp
struct Widget
{
   Widget()
   : s{"CppCon"} // string should be assigned in the body but initialized in the member initializer list
   {
     i =42;
     pi = nullptr;    // for int and ptr, it really doesnt matter that much to put them in the initializer list or assign them in the body
   }
   
   int i;
   std::string s;
   int* pi;
}

```

intializing string in the initializer list make more sense than int or pointer. why??

**rule of thumb**:
- always prefer intializer list for members that need construction (user defined types like vector or strings)
- for fundamental types it doesnt make much practical difference whether you use the initializer list or assign inside the ctor body
**why the difference?**
if you write:
```cpp
Widget() {
    s = "CppCon";   // here: s was *default-constructed first*, then assigned
}
```
That’s _two steps_: default-construct empty string, then assign `"CppCon"`.

For `int`/pointers, there’s no user-defined “construction”.
**Special cases:**
- **Const or reference members** _must_ be initialized in the initializer list (they can’t be assigned later).
- **Order of initialization** is **always** the order of member declaration in the class, not the order in the initializer list.

In c++, its considered a very good style if you put as much class members as possible in the initialzer list:

**clean style:**
```cpp
struct Widget
{
   Widget()
   : i(42)
   , s{"CppCon"}
   , pi{} 
   {}
   
   int i;
   std::string s;
   int* pi;
}

```


```
define and initialize member variables in the order of member declaration
```

```
Prefer initialization to assignment in constructors
```

# 2. Destructor

now lets talk about the second SMF -> destructor

every class has a destructor - either you write it or ocmpiler generate for you (like a default ctor)


```cpp
//compiler generated destructor available
class Widget{
public:
   // ....
};

Widget w1; // compiler generated, ok
Widget w2{}; // compiler generated, ok
```

if you write your declare or define your own destructor, the compiler will not generate one.

```cpp
//no compiler generated destructor available
class Widget{
public:
   ~Widget(); // <- explicit declaration of destructor->
			    //compiler doesnt generate the destructor
   // ....
};

Widget w1; // manual destructor, ok
Widget w2{}; // manual destructor, ok
```

compiler want to cleans up the data members when the lifetime of object ends

the compiler generated destructor
- calls the destructor of all data members of class type
- doesnt do anything special on fundamental type (they dont a dtor)

```cpp
struct Widget
{
   public:
     // ....
   ~Widget()   // the compiler generated destructor destroys the string member but doesnt perform any special action on integer and pointer -> possible resource leak!
   {
   
   }
   
   int i;
   std::string s;
   Resource* pr{};   //<- pr as representive of a possible resource 
}

```

so do this:

```cpp
struct Widget
{
   public:
     // ....
   ~Widget()  
   {
     delete ptr;    // -> now everything ok
   }
   
   int i;
   std::string s;
   Resource* pr{};   //<- pr as representive of a possible resource 
}

```

```
provide a dtor if there is an outstanding responsibilty like above
```
```
never provide an empty dtor. 
prefer to let the compiler provide a defention or define by =default
```

**however, the destructors are often a sign that you have to deal with other functions, that we are goint to talk about now..* -> copy ctor and copy assignment operator


# 3. Copy operations: copy constructor and copy assignment operator

 **Signature of copy consturctor**
```cpp
Widget( Widget const&); //The default
Widget (Widget&) // possible but suspicious
//Widget (Widget) // -> not possible
```
**Signauture of copy assignment operator**
```cpp
Widget& Operator=(Widget const&); //the default
Widget& Operator=(Widget&); // possible but suspicious
Widget& Operator=(Widget); // reasonable! -> it builds on the copy constructor
```

**The compiler generates the copy operations:**
- 1. If they are not explicitly decalred and..
- 2. If no move operations is declared (c++11)
- 3. If all bases/data members can be copy constructed/assigned.


**1. if they are not explicitly declared:**
```cpp
// compiler generated copy ctor and copy assignment operators avaialble
class Widget
{
public:
	//...

};

Widget w1{};
Widget w2(w1); //compiler generated, ok
w1=w2;         //compiler generated, ok
```

```cpp
// compiler generated copy ctor and copy assignment operators NOT avaialble
class Widget
{
public:
	Widget(Widget const&);
	Widget& operator=(Widget const&);

};

Widget w1{};
Widget w2(w1); //explicitly defined, ok
w1=w2;         //explicitly defined, ok
```
**2. if no move operations declared:** (c++11)

If a class **declares a move constructor** (`T(T&&)`) or a **move assignment operator** (`T& operator=(T&&)`):  The compiler **implicitly deletes** the copy constructor **and** the copy assignment operator.

```cpp
// compiler generated copy ctor and copy assignment operators NOT avaialble
class Widget
{
public:
	//Widget(Widget const&) = delete;
	//Widget& operator=(Widget const&) = delete;
	
	//..
	Widget(Widget&& w) noexcept;

};

Widget w1{};
Widget w2(w1); //compiler error: copy ctor not available
w1=w2;         //compiler error: copy assignment oeprator not available

```

in the above case, the copy ctor and copy assignment operator are not gone. they are implicitly defined (or lets think as disabled) . remember- there is always copy operations- might not be available
**3. if all bases/data members can be copy constructed or assigned**

```cpp
// compiler generated copy ctor and copy assignment operators NOT avaialble
class Widget
{
public:
	//Widget(Widget const&) = delete;
	//Widget& operator=(Widget const&) = delete;
	
	//..
	
private:
 NonCopyable memeber_; // data memeber without copy operation(eg reference, unique ptr etc)

};

Widget w1{};
Widget w2(w1); //compiler error: copy ctor not available
w1=w2;         //compiler error: copy assignment oeprator not available

```


```
every class has a copy ctor and copy assignment operator. Either they are available or (implicitly) deleted.
```

