all:
	gcc main.c -o main -I"C:\Users\thitc\Documents\freeglut\include" -L"C:\Users\thitc\Documents\freeglut\lib" -lfreeglut -lopengl32 -lglu32 -lm
	./main