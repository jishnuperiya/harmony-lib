
- **ERROR: Discarding Qualifiers**

erorr i got when i tried to implement a getter method for complex type:

```
error: passing ‘const Complex’ as ‘this’ argument discards qualifiers [-fpermissive]

```

in the below given function:

```cpp
bool operator==(const Complex& lhs, const Complex& rhs)
{
  return (lhs.getReal() == rhs.getReal() &&
          lhs.getImag() == rhs.getImag());
}

```

**reason** : It happens when you call a **member function** (`getReal()` or `getImag()`) on a `const` object, but that member function is **not marked const**.


- When you see **“discards qualifiers”** in an error, 99% of the time it means: You’re calling a non-const method on a const object.
- qualifier means things like 'const'..


my function was this:
```cpp
double getReal();
```

since all member function has a hidden this pointer available(the current object),

the compiler sees this function as:
```cpp
double getReal(Complex* this); // takes a non const complex* as argument
```
which means this method may modify the real_ or imag_
if you are calling it on a const complex, it may break the contract

so you mark the method as const. allowing it to call on a const complex object