
| #   | Topic / Concept                 | Subtopics Included                                                                                                               |
| --- | ------------------------------- | -------------------------------------------------------------------------------------------------------------------------------- |
| 1   | Special Member Functions (SMFs) | default ctor, copy ctor, copy assignment, destructor, compiler-generated behavior, value vs default init, recursive construction |
| 2   | Initialization vs Assignment    | constructor semantics, assignment semantics, `=` dual meaning                                                                    |
| 3   | Expressions & Evaluation        | expressions as recipes, reduction, value vs computation, evaluation outcomes                                                     |
| 4   | Operators as Functions          | `operator+` = function, infix syntax, operators are overloaded functions                                                         |
| 5   | Stroustrup Insights             | operator as normal function, same symbol for different function types                                                            |
| 6   | Operator Overloading Rules      | name overloading, type inference, disambiguation with cast/FQN                                                                   |
| 7   | Value Type Principles           | behave like built-in, correct semantics, invariants, SMFs                                                                        |
| 8   | Rebinding to User-Defined Types | missing arithmetic ops, missing value-type ops, compiler failure reasons                                                         |
| 9   | Operator Families               | +, +=, -, -=, unary -, grouped semantics                                                                                         |
| 10  | Members vs Non-Members          | minimal spanning set, public interface, free functions, non-member +                                                             |
| 11  | Complex Class Design            | minimal members (SMFs, +=), arithmetic as free functions                                                                         |
| 12  | `operator+=` Design             | must be member, mutating LHS, const RHS, prevents friend coercion issues                                                         |
| 13  | `operator+` Design              | free function wrapper around +=, take lhs by value, symmetry                                                                     |
| 14  | Semantic Consistency            | + implemented via +=, consistent semantics under representation changes                                                          |
| 15  | Implicit Coercions              | non-explicit ctors, conversion on rhs in member ops, conversion on both sides in free ops                                        |
| 16  | Member vs Free Behavior         | coercion symmetry, ADL lookup, minimal interface                                                                                 |
| 17  | Why Avoid Friends               | tight coupling, breakage, unnecessary for arithmetic                                                                             |
| 18  | ADL (Argument Dependent Lookup) | operators found via namespace of arguments, avoids global pollution                                                              |
| 19  | Client Extension                | clients can add free functions, not members; namespace-based overloads                                                           |
| 20  | Representation Independence     | avoid public members, avoid friend ops, future-proof design                                                                      |
| 21  | `lhs` vs `rhs` Rules            | non-const ref can’t bind to temporary, const ref can                                                                             |
| 22  | Proper Operator Signatures      | `+=` takes `T&`, `+` takes value, return new object                                                                              |
