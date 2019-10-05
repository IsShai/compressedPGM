output:	main.o	func.o	funcHelpers.o	lists.o	trees.o
	gcc -g main.o	func.o	funcHelpers.o	lists.o	trees.o	-lm	-o output
main.o:	main.c	types.h
	gcc -c	main.c
func.o:	func.c	types.h
	gcc	-c	func.c
funcHelpers.o:	funcHelpers.c types.h
	gcc	-c	funcHelpers.c
lists.o:	lists.c	types.h
	gcc	-c	lists.c
trees.o:	trees.c	types.h
	gcc	-c	trees.c
clean:
	rm	*.o
