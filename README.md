# lesson-6

#### Compiling

Suppose that three functions are stored in three files called main.c, getline.c, and strindex.c. Then the command cc main.c getline.c strindex.c compiles the three files, placing the resulting object code in files main.o, getline.o and strindex.o, then loads them into an executable file called a.out. If there is an error, say in main.c, the file can be recompiled by itself and the result loaded with the previous object files, with the command cc main.c getline.o strindex.o (the cc command uses the .c versus .o naming convention to distinguish source files from object files).

