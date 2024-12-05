## General info
* anything enclosed in `()` is a comment
* anything enclosed in `~~` is a string
* anything prefaced by `.` is an operation 
* anything prefaced by `#` is a label name
* anything else is an integer
* words are separated by spaces or newlines; tabs are SUPPORTED

## Supported operations

We provide 
[stack effect diagrams](https://en.wikipedia.org/wiki/Stack-oriented_programming#Stack_effect_diagrams)
to describe the state of the stack before and after each operation. For example
`a b -- c` means that before the operation the top item on the stack is `b`,
the second item from the top is `a` and after the operation the stack contains
only `c`. In other words, the diagrams describe `before -- after` and if there
is more than one item on the stack, the top of the stack is the rightmost item.
See also the `scripts` directory for example use of most functions.

### Operators on integers
For integer operator where order matters, eg. subtraction, multiplication, etc., we
always use the top of the stack as the "second" number. IE. if the stack
contains `a b` where `b` is the top of the stack, `.-` will push `a - b`. For
example `3 2 .-` will push the result `1` to the stack; not `-1`.

* `.+` `a b -- (a+b)` pops two numbers from the stack and pushes their sum
* `.-` `a b -- (a-b)` pops two numbers from the stack and pushes their difference
* `.*` `a b -- (a*b)` pops two numbers from the stack and pushes their multiple
* `./` `a b -- (a/b)` pops two numbers from the stack and pushes the quotient
  of the second popped number divided by the first popped number
* `.mod` `a b -- (a mod b)` pops two numbers from the stack and pushes the
  remainder of the second popped number divided by the first popped number
* `.=?` `a b -- (a==b)` pops two numbers from the stack and pushes `1` if they
  are equal, `0` otherwise
* `.>?` `a b -- (a>b)` pops two numbers from the stack and pushes `1` if the
  second popped number is larger than the first one, `0` otherwise

### Stack operations
* `.dup` `a -- a a` push a copy of the top item on the stack
* `.swap` `a b -- b a` swaps the two top items on the stack 

### Control flow operations
* `.cjump` `a b --` pops two numbers off the stack. if the second number is not `0` the
  program jumps by as many tokens as the first number indicates. eg. in 
  `1 -3 .cjump` the number `1` indicates that a jump should happen and the
  number `-3` indicates that the program should jump three tokens back. If the
  program for instance is `... 5 6 .* 1 -3 .cjump` we will jump back to the
  token `.*`.
* `.cgoto` `a b --` works like `.cjump` but instead of counting how many words/tokens to go back you can just specify a label. E.g. `loop .cgoto` will go to the label `loop`

### I/O operations
* `.print` `a --` pop an item from the stack and print it to terminal
* `.newline` `--` output a newline character to terminal; does not alter the stack.

