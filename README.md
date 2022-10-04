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
