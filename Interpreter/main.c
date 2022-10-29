#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define T Variable
#define MAXSIZE 100


typedef union
{
    float floatdata;
    char chardata;
} Item;


// Struct to create an array of strings
typedef struct
{
    char str[150];
} Line;


// Variable Struct such that each node in BST is a variable
typedef struct
{
    char key[20];
    float value;
} Variable;


// BST Implementation
typedef struct Node
{
    Variable data;
    struct Node *right;
    struct Node *left;
} Node;

// Node Implementation
Node* newNode (Variable v)
{
    Node *n = malloc(sizeof(Node));
    n -> data = v;
    n -> right = NULL;
    n -> left = NULL;
    return n;
}

// To insert an element in the BST
Node* insert (Node *n, Variable v)
{
    if (n == NULL)
        return newNode(v);

    if (strcmp(v.key, (n -> data).key) == -1)
        n -> left = insert(n -> left, v);

    else if (strcmp(v.key, (n -> data).key) == 1)
        n -> right = insert(n -> right, v);

    return n;
}

// To search for an element in the BST
Node* search(Node *n, char str[])
{
    if (n == NULL)
        return NULL;
    if (strcmp((n -> data).key, str) == 0)
        return n;
    else if(strcmp(str, (n -> data).key) == -1)
        return search(n -> left,str);
    else
        return search(n -> right,str);
}

// To print the elements of the BST without sorting
void InOrderPrint (Node *temp)
{
    if (temp != NULL)
    {
        InOrderPrint (temp -> left);
        printf("--> %s = %.3f\n",(temp -> data).key, (temp -> data).value);
        InOrderPrint (temp -> right);
    }
}


// To count the number of nodes in the BST
int count(Node *n)
{
    if ( n == NULL)
        return 0;
    else
        return 1 + count(n -> left) + count(n -> right);
}
// End BST


// Heap Implementation
void swapTwo (T **item1, T **item2)
{
    T* temp = *item1;
    *item1 = *item2;
    *item2 = temp;
}


void heapify(T *arr[], int n, int i)
{

    int largest = i;
    int leftChild = 2*i+1;
    int rightChild = 2*i+2;

    if(leftChild < n && arr[leftChild]->value > arr[largest]->value)
    {
        largest = leftChild;
    }

    if(rightChild < n && arr[rightChild]->value > arr[largest]->value )
    {
        largest = rightChild;
    }

    if(largest != i)
    {

        swapTwo(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}


void printArray(T *arr[], int n)
{

    for(int i = 0; i < n; i++)
    {
        printf("--> %s = %.3f\n", arr[i]->key, arr[i]->value);
    }

    printf("\n");
}


void deleteMax(T *arr[], int n)
{
    swapTwo(arr, &arr[n]);
    heapify(arr, n, 0);
}


void heapSort(T *arr[], int n)
{

    for(int i = n/2-1; i >=0; i--)
    {
        heapify(arr, n, i);
    }

    for(int i = n-1; i > 0; i--)
    {
        deleteMax(arr, i);
    }
}
// End Heap


// Stack Implementation
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
    s -> items[s -> top] = value;
    s -> top++;
}


Item pop (Stack *s)
{
    Item value;
    s -> top--;
    value = s -> items[s -> top];
    return value;
}


int isEmpty (Stack *s)
{
    if (s -> top == 0)
    {
        return 1;
    }
    else
        return 0;
}


Item top (Stack *s)
{
    return s -> items[s -> top-1];
}
// End Stack


// Expression Evaluation
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


// To insert spaces between the terms of the expression to be ready for infix->postfix function
char* infixWithSpaces(char *exp)
{
    char *inf = malloc (100);
    memset(inf,0,strlen(inf));
    char space = ' ';
    char times = '*';
    int i = 0;
    for ( i = 0 ; i < strlen(exp) ; i++ )
    {
        if (exp[i] == '+' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^')
        {
            strncat(inf,&space,1);
            strncat(inf,&exp[i],1);
            strncat(inf,&space,1);
        }

        else if (exp[i] == '-')
        {
            if (exp[i-1] == '+' || exp[i-1] == '-' || exp[i-1] == '*' || exp[i-1] == '/' || exp[i-1] == '^' || exp[i-1] == '(' || exp[i-1] == ')' || i == 0)
            {
                strncat(inf,&exp[i],1);
            }
            else
            {
                strncat(inf,&space,1);
                strncat(inf,&exp[i],1);
                strncat(inf,&space,1);
            }
        }

        else if (exp[i] == '(')
        {
            strncat(inf,&exp[i],1);
            strncat(inf,&space,1);
        }

        else if (exp[i] == ')')
        {
            strncat(inf,&space,1);
            strncat(inf,&exp[i],1);
        }

        // To handle for ex: 2X situation
        else if ((exp[i] == '0' || exp[i] == '1' || exp[i] == '2' || exp[i] == '3' || exp[i] == '4' || exp[i] == '5' || exp[i] == '6' || exp[i] == '7' || exp[i] == '8' || exp[i] == '9') && ((exp[i+1] >= 'a' && exp[i+1] <= 'z') || (exp[i+1] >= 'A' && exp[i+1] <= 'Z')))
        {
            strncat(inf,&exp[i],1);
            strncat(inf,&space,1);
            strncat(inf,&times,1);
            strncat(inf,&space,1);
        }

        else
        {
            strncat(inf,&exp[i],1);
        }
    }
    return (inf);
}


// Infix to Postfix conversion
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


// Calculation
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


// Postfix expression evaluation
float evaluatePostfix (char *exp, Node *root)
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

        // To check if the term is variable and search for it in the BST
        else if ((p[0] >= 'a' && p[0] <= 'z') || (p[0] >= 'A' && p[0] <= 'Z'))
        {
            Node *searched = NULL;
            searched = search(root, p);
            if (searched != NULL)
            {
                m.floatdata = (searched -> data).value;
                push (s, m);
            }
            else
            {
                printf ("** ERROR **\n\n");
                printf ("** Check Invalid Symbol **\n\n");
                exit(0);
            }
        }
        // To handle -ve variables
        else if ((p[0] == '-') && ((p[1] >= 'a' && p[1] <= 'z') || (p[1] >= 'A' && p[1] <= 'Z')))
        {
            char* contents_chopped = p + 1;
            Node *searched = NULL;
            searched = search(root, contents_chopped);
            if (searched != NULL)
            {
                m.floatdata = (searched -> data).value * (-1);
                push (s, m);
            }
            else
            {
                printf ("** ERROR **\n\n");
                printf ("** Check Invalid Symbol **\n\n");
                exit(0);
            }

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
// End expression calculation


// Errors Handling
// To remove all spaces in the file so we can tokenize each line and get a key before "=" and a value after "="
void removeSpaces(char *str)
{
    int count = 0;

    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i];
    str[count] = '\0';
}


// To stop the program if the equal sign is missing in the equation
int checkEqualSign (char str[])
{
    int i;

    for ( i = 0 ; i < strlen(str) ; i++ )
    {
        if (str[i] == '=')
            return 1;
    }
    return 0;
}


// To stop the program if there are multiple variables in the equation
int checkSign (char str[])
{
    int i;

    for (i=0; i<strlen(str); i++)
    {
        if (str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '-' || str[i] == '=' || str[i] == '(' || str[i] == ')')
        {
            printf ("** ERROR **\n\n");
            printf ("** An operation found in the LHS **\n\n");
            return 1;
        }

    }
    return 0;
}


//To check that number of closed brackets is equal to the number of open brackets
int checkBrackets(char str[])
{
    int i;
    int countOpen=0;
    int countClosed=0;
    for (i=0; i<strlen(str); i++)
    {
        if (str[i] == '(')
            countOpen++;
        else if (str[i] == ')')
            countClosed++;
    }

    if (countOpen!=countClosed)
    {
        printf("** ERROR **\n\n");
        printf("** Please check the brackets  **\n\n");
        return 1;
    }
    return 0;
}


//To check if there was a consecutive  in any operator
int checkConsecutiveSign(char str[])
{
    int i;
    for (i=0; i<strlen(str); i++)
    {
        if (str[i] == '+' || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == '=' )
        {
            if (str[i+1] == '+' || str[i+1] == '*' || str[i+1] == '/' || str[i+1] == '^' || str[i+1] == '=')
            {
                printf("** ERROR **\n\n");
                printf("** Please check if there was any Consecutive Operators **\n\n");
                return 1;
            }
        }
        else if (str[i] == '(')
        {
            if (str[i+1] == '+' || str[i+1] == '*' || str[i+1] == '/' || str[i+1] == '^' || str[i+1] == '=')
            {
                printf("** ERROR **\n\n");
                printf("** Please check if there was a Consecutive Operator after a bracket **\n\n");
                return 1;
            }
        }
        else if (str[i] == ')')
        {
            if (str[i-1] == '+' || str[i-1] == '*' || str[i-1] == '/' || str[i-1] == '^' || str[i-1] == '=' ||str[i-1] == '-')
            {
                printf("** ERROR **\n\n");
                printf("** Please check if there was a Consecutive Operator before a bracket **\n\n");
                return 1;
            }
        }
    }
    return 0;
}


// To check the entered variable validity
int validityCheck (char str[], Node *root)
{
    char *p;
    removeSpaces(str);
    p = strtok(infixWithSpaces(str), " ");
    while (p != NULL)
    {
        if ((p[0] >= 'a' && p[0] <= 'z') || (p[0] >= 'A' && p[0] <= 'Z'))
        {
            Node *searched = NULL;
            searched = search(root, p);
            if (searched == NULL)
            {
                printf ("** ERROR **\n\n");
                printf ("** Invalid Symbol **\n\n");
                return 1;
            }
        }
        else if ((p[0] == '-') && ((p[1] >= 'a' && p[1] <= 'z') || (p[1] >= 'A' && p[1] <= 'Z')))
        {
            char* contents_chopped = p + 1;
            Node *searched = NULL;
            searched = search(root, contents_chopped);
            if (searched == NULL)
            {
                printf ("** ERROR **\n\n");
                printf ("** Invalid Symbol **\n\n");
                return 1;
            }
        }
        p = strtok(NULL, " ");
    }
    return 0;
}

// To check variables starting with a number
int numberAtFirstCheck (char str[])
{
    if (str[0] == '0' || str[0] == '1' || str[0] == '2' || str[0] == '3' || str[0] == '4' || str[0] == '5' || str[0] == '6' || str[0] == '7' || str[0] == '8' || str[0] == '9')
    {
        printf ("** ERROR **\n\n");
        printf ("** Invalid Variable Name **\n\n");
        return 1;
    }
    return 0;
}
// End Error Handling

// Loading Src.txt
void loadFile ()
{
    FILE *fp;
    fp = fopen("Src.txt","r");

    int lines = 0;
    int i;
    Line l[100];

    if(fp == NULL)
    {
        printf("** ERROR **\n\n");
        printf("** There is no File attached to your Program **\n\n");
        exit(0);
    }

    // Inserting each equation existing in the file into an array of strings "l[100]"
    while (!feof(fp))
    {
        fscanf (fp, "%[^\n]\n", l[lines].str);
        lines++;
    }

    // Fixing the lines in the files by removing spaces and checking for the "="
    for ( i = 0 ; i < lines ; i++ )
    {
        removeSpaces(l[i].str);
        if (checkEqualSign(l[i].str) == 0)
        {
            printf ("** ERROR **\n\n");
            printf("** Please check if there was any Operator before the Equal Sign **\n\n");
            exit(0);
        }
        printf ("--> %s\n",l[i].str);
    }
    printf ("\n");
}

// Reading the file and inserting its components into the BST and the heap
Node *readFile (FILE *fp, T **arr)
{
    int lines = 0;
    int i;
    Line l[100];


    if(fp == NULL)
    {
        printf("** ERROR **\n\n");
        printf("** There is no File attached to your Program **\n\n");
        exit(0);
    }

    // Inserting each equation existing in the file into an array of strings "l[100]"
    while (!feof(fp))
    {
        fscanf (fp, "%[^\n]\n", l[lines].str);
        lines++;
    }


    // The variable in the first equation
    Variable v1;
    // The other variables
    Variable v;

    // Our Tokens
    char *p1;
    char *p2;

    // Fixing the lines in the files by removing spaces and checking for the "="
    for ( i = 0 ; i < lines ; i++ )
    {
        removeSpaces(l[i].str);
        if (checkEqualSign(l[i].str) == 0)
        {
            printf ("** ERROR **\n\n");
            printf("** Please check the Equal Sign **\n\n");
            exit(0);
        }
    }

    p1 = strtok (l[0].str,"=");

    if (checkSign(p1))
    {
        printf("** ERROR **\n\n");
        printf("** Please check the Equal Sign **\n\n");
        exit(0);
    }
    if (numberAtFirstCheck(p1))
    {
        exit(0);
    }

    p2 = strtok (NULL, "=");

    if (p1 == NULL || p2 == NULL)
    {
        printf ("** ERROR **\n\n");
        printf ("** Blank Space **\n\n");
        exit(0);
    }

    if (checkSign(p2)==1)
    {
        printf("** ERROR **\n\n");
        printf("** Please check if there was any Operator beside your first value **\n\n");
        exit(0);
    }

    if (checkBrackets(p2) == 1)
    {
        exit(0);
    }

    if (checkConsecutiveSign(p2))
    {
        exit(0);
    }

    Variable *vptr = malloc(sizeof(Variable));

    // Initializing the BST, inserting the first variable and calculating its value
    Node *root = NULL;
    strcpy(v1.key, p1);
    strcpy(vptr -> key, p1);
    v1.value = evaluatePostfix(infixtoPostfix(infixWithSpaces(p2)), root);
    vptr -> value = v1.value;

    arr[0] = vptr;
    root = insert (root, v1);

    // Inserting the remaining variables to the BST & heap and calculating the value of each variable
    for ( i = 1 ; i < lines ; i++ )
    {

        vptr = malloc(sizeof(Variable));
        p1 = strtok (l[i].str,"=");
        p2 = strtok (NULL, "=");

        if (p1 == NULL || p2 == NULL)
        {
            printf ("** ERROR **\n\n");
            printf ("** Blank Space **\n\n");
            exit(0);
        }

        if (checkSign(p1))
        {
            printf("** ERROR **\n\n");
            printf("** Please check the Equal Sign **\n\n");
            exit(0);
        }

        if (numberAtFirstCheck(p1))
        {
            exit(0);
        }

        if (checkBrackets(p2) == 1)
        {
            exit(0);
        }

        if (checkConsecutiveSign(p2))
        {
            exit(0);
        }

        strcpy(v.key, p1);
        strcpy(vptr -> key, p1);
        v.value = evaluatePostfix(infixtoPostfix(infixWithSpaces(p2)), root);
        vptr -> value = v.value;

        arr[i] = vptr;
        insert (root, v);
    }
    return root;
}


// To put an extra variable
void put (char vname[], char expr[], Node* root, T** arr)
{

    Variable v;

    removeSpaces(vname);
    removeSpaces(expr);
    int i, element;

    if (checkSign(vname))
    {
        printf("** ERROR **\n\n");
        printf("** Please check the Equal Sign **\n\n");
        exit(0);
    }

    Variable *vptr = malloc(sizeof(Variable));

    checkBrackets(expr);
    checkConsecutiveSign(expr);

    Node *searched = NULL;
    searched = search(root, vname);

    // If the node is found then values will be updated
    if (searched != NULL)
    {

        strcpy(v.key, vname);
        strcpy(vptr -> key, vname);
        v.value = evaluatePostfix(infixtoPostfix(infixWithSpaces(expr)), root);
        vptr -> value = v.value;
        searched -> data = v;

        for ( i = 0 ; i < count(root) ; i++ )
        {
            if (strcmp(arr[i] -> key, vname) == 0)
            {
                element = i;
                break;
            }
        }
        arr[element] = vptr;
    }
    // If the node is not found then it will be added to the system
    else
    {
        strcpy(v.key, vname);
        strcpy(vptr -> key, vname);
        v.value = evaluatePostfix(infixtoPostfix(infixWithSpaces(expr)), root);
        vptr -> value = v.value;
        insert (root, v);
        arr[count(root)-1] = vptr;
    }
}

// Main Function
int main()
{
    printf ("\n");
    printf ("*** Simple Interpreter ***\n\n");
    system("color 5f");

    int cnt = 0, cho;
    char ch[100];
    char n[100];

    FILE *fp;
    fp = fopen("Src.txt","r");

    T **arr = malloc(sizeof(T *) * 50);

    Node *root = readFile(fp, arr);

    printf ("* The Uploaded File : \n\n");
    loadFile();

    while (1)
    {
        char eq[150];
        char *p1;
        char *p2;
        int i, no;


        printf("* Select one of the following commands :\n\n  1- BST Sort  (By Variable Name)\n  2- Heap Sort (By Value)\n  3- Insert Equations\n  4- EXIT\n\n");
        printf ("* Enter your choice (1 to 4) : ");
        scanf(" %[^\n]s",ch);
        printf ("\n");
        removeSpaces(ch);
        cho = atoi(ch);

        switch (cho)
        {
        // Printing BST InOrder
        case 1:
            printf ("* Sort by Variable Name :\n\n");
            InOrderPrint(root);
            printf ("\n");
            break;
        // Printing array using heapSort
        case 2:
            cnt = count(root);
            printf ("* Sort by Value : \n\n");
            heapSort(arr, cnt);
            printArray(arr, cnt);
            break;
        // Put an equation
        case 3:
            printf ("* Enter the number of equations you want to calculate : ");
            scanf (" %[^\n]s",n);
            removeSpaces(n);
            no = atoi(n);
            printf ("\n");
            for ( i = 0 ; i < no ; i++ )
            {
                printf ("--> Enter the Equation #%d : ",i+1);
                scanf(" %[^\n]s",eq);
                printf ("\n");
                if (checkEqualSign(eq) == 0)
                {
                    printf("** ERROR **\n\n");
                    printf("** Please check the Equal Sign **\n\n");
                    i--;
                }
                else
                {
                    p1 = strtok (eq,"=");
                    p2 = strtok (NULL, "=");

                    if (p1 == NULL || p2 == NULL)
                    {
                        printf ("** ERROR **\n\n");
                        printf ("** Blank Space **\n\n");
                    }

                    if (p1 != NULL && p2 != NULL && numberAtFirstCheck(p1) == 0 && checkSign(p1) == 0 && checkConsecutiveSign(p2) == 0 && checkBrackets(p2) == 0 && validityCheck(p2, root) == 0)
                    {
                        put(p1, p2, root, arr);
                        printf ("** Equation Recorded Successfully **\n\n");
                    }
                    else
                        i--;
                }
            }
            break;
        // Ending the program
        case 4:
            printf ("*** Thanks ! ***\n\n");
            exit(0);
            break;
        default:
            printf("X Invalid Input X\n\n");
            break;
        }
    }
    return 0;
}
// End of Main function
// End of Program
