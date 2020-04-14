main: main.c v1_parent.c 
	gcc -o main main.c v1_parent.c v1_child.c -I. -lm

