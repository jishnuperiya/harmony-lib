### Handles in C++
the `filebuf` class has a data member : `FILE* file_`

file_ is a **handle**.
its a **opaque reference** to a resource managed elsewhere

you cant do things like `file_->something=18` . you only pass it to functions that know what to do with it

also think this way: `file_` is a handle and `filebuf` is the c++ wrapper that owns and manages that handle.

**ownership** : decide who owns the handle. if your object owns it, clost it in destructor (RAII)

#### Is handle a PImpl?
**PImpl**: pointer to implementation,and its used in your own implementation.

```cpp
class filebuf
{
  struct Impl; //forward declaration (opaque to header)
  Impl* impl_; // pointer to hidden implmentation
};
```

then in *filebuf.cpp* you can define the implementation of the *filebuf.cpp*. 

here *impl_* is a pimpl pointer. it hides class's data (client doesnt know even the class is using a FILE* handle) and implementation detail from clients.


- **file_ is a handle to external opaque implementation**
- **PImpl is internal handle to your own opaque implementation**

another way to say it:

- **FILE* is the handle given to you by another library***
- **pimpl_ handle you define to hide your own library details **

both are pointers to an incomplete type. but the design intent differs.



