# OpenGL Kitchen

## Prerequisites

- C Compiler
- OpenGL, GLUT and GLEW
- freeglut.dll in the same folder as main.c
  

### How to compile and run by hand (Windows)

To compile, use the following command (remember to change the path to the freeglut library)

```bash
gcc main.c -o main -I"Your path to \freeglut\include" -L"Your path to \freeglut\lib" -lfreeglut -lopengl32 -lglu32 -lm
```

Once compiled, use the main file to run

```bash
./main
```

### How to use Makefile

If you want, and you have make installed, you can change the freeglut path in the Makefile to use the make command. This command will compile and run the program in sequence.

```
make
```

## Controls

### Movement

**__Mouse__** -> Look around

**__W, A, S, D__** -> Move respectively to: Front, Back, Left, Right

**__SPACE, C__** -> Move respectively to: Up, Down
### Objects

**__P__** opens the door

**__J__** opens the window