
##### 1. Clarifying the semantics
- frequency is the physical view of sound where as pitch is symbolic, discrete view
##### 2. identifying the invariants
- hz>0 (0 hz and negative values are meaningless)
- default A4=440hz
- scaling operations (x, /) must preserve positivity
##### 3. deciding internal representation
```cpp
private:
  double hz_; //cycles per sec	
```

double - trivial copy, 8 bytes

