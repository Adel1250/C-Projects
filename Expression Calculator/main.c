#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAXSIZE 100

typedef union
{
    float floatdata;
    char chardata;
} Item;

typedef struct
{
    Item items[MAXSIZE];
    int top;
} Stack;

Stack* initialize ()
{
    Stack *s = malloc(sizeof(Stack));
    s->top = 0;
    return s;
}

void push (Stack *s, Item value)
{
    s->items[s->top] = value;
    s->top++;
}

Item pop (Stack *s)
{
    Item value;
    s->top--;
    value = s->items[s->top];
    return value;
}

int isEmpty (Stack *s)
{
    if (s->top == 0)
    {
        return 1;
    }
    else
        return 0;
}

Item top (Stack *s)
{
    return s->items[s->top-1];
}

int priority (char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 0;
    case '*':
    case '/':
        return 1;
    case '^':
        return 2;
    case '(':
        return 3;
    }
    return -1;
}

char* infixtoPostfix (char *infexp)
{

    Stack *s = initialize();

    char *token = strtok (infexp," ");
    char *postexp = malloc (100);
    Item a, b;

    memset(postexp,0,strlen(postexp));

    while (token != NULL)
    {
        if (!((strlen(token) == 1) && ( token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '^' || token[0] == '(' || token[0] == ')')))
        {
            strncat (postexp,token,strlen(token));
            char v = ' ';
            strncat (postexp,&v,1);
        }

        else if (token[0] == ')')
        {
            while (!isEmpty(s) && top(s).chardata != '(')
            {
                char f = pop(s).chardata;
                strncat(postexp,&f,1);
                f = ' ';
                strncat(postexp,&f,1);
            }

            pop(s);
        }

        else if (isEmpty(s))
        {
            a.chardata = token[0];
            push (s,a);
        }

        else
        {
            while(!isEmpty(s) && priority(top(s).chardata) >= priority(token[0]) && top(s).chardata != '(')
            {
                char u = pop(s).chardata;
                strncat(postexp,&u,1);
                u = ' ';
                strncat(postexp,&u,1);
            }
            b.chardata = token[0];
            push (s,b);

        }

        token = strtok (NULL, " ");

    }

    while(!isEmpty(s))
    {
        char w = pop(s).chardata;
        strncat(postexp,&w,1);
        w = ' ';
        strncat(postexp,&w,1);
    }

    return postexp;

}

float evaluate (char x, float op1, float op2)
{

    if (x == '+')
        return (op1 + op2);
    if (x == '-')
        return (op1 - op2);
    if (x == '*')
        return (op1 * op2);
    if (x == '/')
        return (op1 / op2);
    if (x == '^')
        return (pow(op1,op2));
    return 0;

}

float evaluatePostfix (char *exp)
{
    Stack *s = initialize();
    float op1, op2, val;
    Item x, m;
    char *p = strtok(exp," ");
    while ( p != NULL )
    {
        if ((strlen(p) == 1) && ( p[0] == '+' || p[0] == '-' || p[0] == '*' || p[0] == '/' || p[0] == '^'))
        {
            op2 = pop(s).floatdata;
            op1 = pop(s).floatdata;
            val = evaluate (*p,op1,op2);
            x.floatdata = val;
            push(s,x);
        }
        else
        {
            float n = atof(p);
            m.floatdata = n;
            push (s,m);
        }
        p = strtok (NULL," ");
    }
    float k = pop(s).floatdata;
    return k;
}

int main()
{
    system("color f0");
    char infexp[MAXSIZE];
    printf ("\n");
    printf ("** Expression Calculator **\n\n");
    printf ("* Enter the Infix expression : ");
    gets (infexp);
    printf ("\n");
    printf ("* The value of this expression is ");
    printf ("%.3f",evaluatePostfix(infixtoPostfix(infexp)));
    printf ("\n\n");
    printf ("*** Thanks ! ***\n\n");
    return 0;
}
