









![[Pasted image 20251113171414.png]]



way to think about it- this function has 4 params.
b e v are values that we supplied at call site

4th param is type

1-3 value - need in runtime
4- value have to supplied at compile time

find<int> (&v[0],&v[10],17)


find<double>; ->instantiating afunc
-< gives us the normal funciton


its same as 

*(find <int>) (give te 3 params)

find <int> gives the funtion pointer


i am allowed to omit the *()

compiler takes the tempalte code and copy it here and replace T with int


if you just do find(3 args) -they do type inference


find() is fully polymophiosc(parametriclly) if the parametsr support the comparison operator


since operator= is a constraint - it not genuinely 100% paraetrically polymprhpic


bounded polymprhopc


there is a recent addition to spell out this constraints -concepts



real constraints: subtle:
![[Pasted image 20251113172929.png]]
![[Pasted image 20251113172932.png]]

![[Pasted image 20251113172938.png]]

in dsktop



code bloat. where each templates

iterotrs
-----

![[Pasted image 20251113173541.png]]
defnetion is not self documenting

x can be anyhting



any stl get iterators

its better if we construct from pair of iterators

iterators are conepts- set of requirement for a type so it behave like pointers

pointer models the concept of iterator




![[Pasted image 20251113174218.png]]



![[Pasted image 20251113174457.png]]


