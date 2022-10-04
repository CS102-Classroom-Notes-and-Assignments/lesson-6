# lesson-6

### Compiling

Suppose that three functions are stored in three files called main.c, getline.c, and strindex.c. Then the command cc main.c getline.c strindex.c compiles the three files, placing the resulting object code in files main.o, getline.o and strindex.o, then loads them into an executable file called a.out. If there is an error, say in main.c, the file can be recompiled by itself and the result loaded with the previous object files, with the command cc main.c getline.o strindex.o (the cc command uses the .c versus .o naming convention to distinguish source files from object files).

#### Compiling scenarios mentioned in the book
```c
#include <stdio.h>
#define MAXLINE 100
/*rudimentary calculator */
main() {
	double sum, atof(char []);
	char line[MAXLINE];
	int getLine(char line[], int max);

	sum = 0;
	while (getline(line, MAXLINE) > 0)
		printf(“\t%g\n”, sum += atof(line));
	return 0;
}
```
The declaration 
```double sum, atof(char []); ```
Says that sum is a double variable, and that atof is a function that takes one char[] argument and returns a double.

The function atof() must be declared and defined consistently. If atof itself and the call to it in main have inconsistent types in the same source file, the error will be detected by the compiler. But if (as is more likely) atof were compiled separately, the mismatch would not be detected, atof would return a double that main would treat as an int, and meaningless answers would result. —> the reason a mismatch can happen is that if there is no function prototype, a function is implicitly declared by its first appearance in an expression, such as: 
```sum += atof(line)```

If a function declaration does not include arguments, as in 
```double atof();```
That is taken to mean that nothing is to be assumed about the arguments of atof; all parameter checking is off. This is bad syntax, if the function takes arguments, declare them; if it takes no arguments, use void.
double atof(void);
```c
/* atoi: convert string s to integer using atof */
int atoi(char s[])
{
	double atof(char s[]);
	return (int) atof(s);
}
```
This operation does potentially discard information, however, so some compilers warn of it. The cast states explicitly that the operation is intended, and suppresses any warning.

###  Make Files - ATOF
#### ATOF - In One File
```c
#include <stdio.h>
#include <ctype.h>

// K&R Pg. 71
// atof: convert string s to double

double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i=0; isspace(s[i]); i++) // skip white space
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val=0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power=1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}

int main()
{
    char input[] = "-1.23";
    printf("%f\n", atof(input));

    return 0;
}
```

### ATOF - In 2 Files - ATOF.C AND ATOF.H

#### atof.h
```c
#include <stdio.h>

double atof(char s[]);
```

#### atof.c
```c
#include <ctype.h>

// K&R Pg. 71
// atof: convert string s to double

double atof(char s[])
{
    double val, power;
    int i, sign;

    for (i=0; isspace(s[i]); i++) // skip white space
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val=0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power=1.0; isdigit(s[i]); i++)
    {
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }
    return sign * val / power;
}
```
#### main.c
```c
#include <stdio.h>
#include <atof.h>

int main()
{
    char input[] = "-1.23";
    printf("%f\n", atof(input));

    return 0;
}
```

### ATOF - In 2 files, compiling
```gcc -o main atof.c main.c -I.```


### SIMPLE MAKEFILE
#### makefile
```make
# this will compile all files every time make is run
make: main.c atof.c atof.h
    gcc -o main main.c atof.c -I.

# this will clean or remove compiled files so you can start fresh
clean:
    rm -f *.o *.exe
make
make clean
```


### UPDATED MAKE FILE
```make
This allows you to only recompile
# Definitions for constants
CC=gcc
CFLAGS=-I.

# This will create your final output using .o compiled files
make: main.o atof.o
    $(CC) $(CFLAGS) -o main main.o atof.o

# This will compile atof.c
atof.o: atof.c atof.h
    $(CC) $(CFLAGS) -c atof.c

# This will compile main.c with its dependency
main.o: main.c atof.h
    $(CC) $(CFLAGS) -c main.c

# This will clean or remove compiled files so you can start fresh
clean:
    rm -f *.o *.exe
```

## Reverse Polish Calculator - each operator follows its operands. 
(1 + 2) * (4 + 5) is entered as 1 2 - 4 5  + * in polish notation.


### Implementation:
- Each operand is pushed onto a stack
- When an operator arrives, the proper number of operands (two for binary operators) is popped
- The operator is applied to them
- And the result is pushed back onto the stack.
- When the end of the input line is encountered, the value on the top of the stack is popped and printed.


### Pseudocode: 

### Questions to consider before writing code: 
What functions should we have?
- void push(double f) { …}
- double pop(void) { … }
- int getop(char s[]) { …}
- main()


What variables should be external?
- stack
- Stack position


What functions should have access to what variables?
- Only push and pop have access to stack 


## MAKE FILES - REVERSE POLISH CALCULATOR
#### CALCULATOR - ALL IN 1 FILE
```c
#include <stdio.h>
#include <stdlib.h> // for atof()

// K&R page 76-79

#define MAXOP   100 // max size of operand or operator
#define NUMBER  '0' // signal that a number was found

int getop(char []);
void push(double);
double pop(void);

// reverse Polish calculator
int main()
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) 
    {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
/* note that for - and / the left and right operand must be distinguished. If we did push(pop() - pop()); the order in which the two calls of pop are evaluated is not defined. To guarantee the right order, it is necessary to pop the first value into a temporary variable as we did in main.
*/
        case '-':
            op2 = pop(); 
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                printf("error:zero divisor\n");
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
    return 0;
}

#define MAXVAL 100  // maximum depth of val stack

int sp = 0;         // next free stack position
double val[MAXVAL]; // value stack

// push: push f onto value stack
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error:stack full, can't push %g\n", f);
}

// pop:pop and return top value from stack
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error:stack empty\n");
        return 0.0;
    }
}

int getch(void);
void ungetch(int);

// getop: get next operator or numeric operand
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;

    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c; // not a number
    i = 0;
    if (isdigit(c)) // collect integer part
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.') // collect fraction part
        while (isdigit(s[++i] = c = getch()))
            ;

    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

/* It’s often the case that a program cannot determine that it has read enough input until it has read too much. One instance is collecting characters that make up a number: until the first non-digit is seen, the number is not complete. But then the program has read one character too far, a character that it is not prepared for. 

ungetch solves this problem by making it possible to “un-read” the unwanted character. Then every time the program reads one character too many, it could push it back on the input, so the rest of the code could behave as if it had never been read.

*/

#define BUFSIZE 100

char buf[BUFSIZE];  // buffer for ungetch
int bufp = 0;       // next free position in buf

int getch(void) // get a (possibly pushed back) charater
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push character back on input
{
    if (bufp >= BUFSIZE)
        printf("ungetch:too many characters\n");
    else
        buf[bufp++] = c;
}
```





