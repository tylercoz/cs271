# Author

Tyler Cozzocrea, December 6th

No License

# Description

Takes in a .asm file containing Hack Assembly and turns it into Hack machine code that the Hack computer can read. The machine code is stored in a .asm.hack file in with the same name and same directory as the .asm file that was passed in.

# Dependencies

- C compiler
- Make

# Use

The default compiler is `gcc`. If you don't have `gcc`, you can change the compiler in the `Makefile` in the `CC` option:

```Makefile
CC = GCC
```

To run this script:

```bash
$ make
$ ./main [file]
```
