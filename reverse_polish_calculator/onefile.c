#include <stdio.h>
#include <stdlib.h> // for atof()
#include <ctype.h>

// K&R page 76-79

#define MAXOP 100  // max size of operand or operator
#define NUMBER '0' // signal that a number was found

int getop(char[]);
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
        switch (type)
        {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
            /* note that for - and / the left and right operand must be distinguished.
            If we did push(pop() - pop()); the order in which the two calls of pop are
            evaluated is not defined. To guarantee the right order, it is necessary to
            pop the first value into a temporary variable as we did in main.
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

#define MAXVAL 100 // maximum depth of val stack

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
    else
    {
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

/* It’s often the case that a program cannot determine that it has read
enough input until it has read too much. One instance is collecting
characters that make up a number: until the first non-digit is seen,
the number is not complete. But then the program has read one character
too far, a character that it is not prepared for.

ungetch solves this problem by making it possible to “un-read” the
unwanted character. Then every time the program reads one character too
many, it could push it back on the input, so the rest of the code could
behave as if it had never been read.

*/

#define BUFSIZE 100

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0;      // next free position in buf

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