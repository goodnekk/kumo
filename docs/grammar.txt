//Primary statements
Statement       Call | Expression
Call            Name(arguments)
Expression      AddSub | Paren

//arithmatic
Paren           (AddSub)
AddSub          MulDiv + AddSub | Paren + AddSub | MulDiv
MulDiv          N  * MulDiv | Paren * MulDiv | N
N               Number | Name | Call

//terminal
Number          [0..9]
Name            [a..bA..B]
