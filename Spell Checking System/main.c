#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char data[25];
    struct Node *right;
    struct Node *left;
} Node;

Node* newNode (char str[])
{
    Node *n = malloc(sizeof(Node));
    strcpy(n -> data, str);
    n -> right = NULL;
    n -> left = NULL;
    return n;
}

Node* insert(Node* root, char key[])
{
    Node* new_node = newNode(key);
    Node* curr = root;

    Node* prev = NULL;

    while (curr != NULL)
    {
        prev = curr;
        if (strcasecmp(key, curr->data) < 0)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (prev == NULL)
    {
        prev = new_node;
        return prev;
    }

    if (strcasecmp(key, prev->data) < 0)
    {
        prev->left = new_node;
    }

    else
    {
        prev->right = new_node;
    }
    return root;
}

Node* search(Node *n, char str[])
{
    if (n == NULL)
        return NULL;
    if (strcasecmp(n -> data, str) == 0)
        return n;
    else if(strcasecmp(str, n -> data) == -1)
        return search(n -> left,str);
    else
        return search(n -> right,str);
}

int max(int x, int y)
{
    return x > y ? x : y;
}

int height(Node *n)
{
    if ( n == NULL)
        return -1;
    else
        return 1 + max(height(n -> left), height(n -> right));
}

int count(Node *n)
{
    if ( n == NULL)
        return 0;
    else
        return 1 + count(n -> left) + count(n -> right);
}

Node* FindMin(Node *root)
{
    if(root == NULL)
        return NULL;
    else if(root -> left != NULL)
        return FindMin(root -> left);
    else
        return root;
}

Node* FindMax(Node *root)
{
    if(root == NULL)
        return NULL;
    else if(root -> right != NULL)
        return FindMax(root -> right);
    else
        return root;
}

Node* getSuccessor (Node *n, Node *r, char str[])
{
    Node* successor;

    if (strcasecmp(str, FindMax(r) -> data) != 0)
    {
        if (n -> right != NULL)
        {
            return FindMin(n -> right);
        }
        else
        {
            while (r != NULL)
            {
                if (strcasecmp(str, r -> data) == -1)
                {
                    successor = r;
                    r = r -> left;
                }
                else if (strcasecmp(str, r -> data) == 1)
                {
                    r = r -> right;
                }
                else
                    break;
            }
        }

        return successor;
    }

    return NULL;
}

Node* getPredecessor (Node *n, Node *r, char str[])
{
    Node *predecessor;

    if (strcasecmp(str, FindMin(r) -> data) != 0)
    {
        if (n -> left != NULL)
        {
            return FindMax(n -> left);
        }
        else
        {
            while (r != NULL)
            {
                if (strcasecmp(str, r -> data) == 1)
                {
                    predecessor = r;
                    r = r -> right;
                }
                else if (strcasecmp(str, r -> data) == -1)
                {
                    r = r -> left;
                }
                else
                    break;
            }
        }

        return predecessor;
    }

    return NULL;
}

Node* searchIncorrect (Node *r, char str[])
{
    while (r != NULL)
    {
        if (strcasecmp(str, r -> data) == -1)
        {
            if (r -> left == NULL)
                return r;
            else
                r = r -> left;
        }
        else if (strcasecmp(str, r -> data) == 1)
        {
            if (r -> right == NULL)
                return r;
            else
                r = r -> right;
        }
    }
    return NULL;
}

int main()
{

    system("color f0");

    printf ("\n");
    printf ("*** Spell Checking System ***\n\n\n\n");

    FILE *fp;
    fp = fopen("EN-US-Dictionary.txt","r");

    char word1[25];
    char sent [200];
    char word[25];

    fscanf(fp,"%s\n",word1);
    Node *root = NULL;
    root = insert(root, word1);

    while(!feof(fp))
    {
        fscanf(fp,"%s\n",word);
        insert(root, word);
    }

    printf ("** Dictionary loaded successfully **\n\n");

    int h = height(root);
    printf ("* Height : %d\n\n",h);

    int cnt = count(root);
    printf ("* Size : %d\n\n",cnt);

    Node* minimum = FindMin(root);
    Node* maximum = FindMax(root);

    printf ("* The minimum and maximum words are %s and %s :)\n\n",minimum -> data, maximum -> data);

    printf ("* Enter the sentence you want to check (Max 200 elements) : \n\n  ");
    gets(sent);
    printf ("\n");
    printf ("--------------------------------------------------------------------------------\n\n");
    char *p;
    p = strtok (sent," ");

    Node *searched = NULL;
    Node *inCorrect = NULL;

    while (p != NULL)
    {
        searched = search(root, p);

        if (searched == NULL)
        {
            inCorrect = searchIncorrect(root, p);
            printf ("* %s\n\n", p);
            printf ("  State : Incorrect\n\n");
            printf ("  Suggestions : %s, %s, %s\n\n", inCorrect -> data, getSuccessor(inCorrect, root, inCorrect -> data) -> data, getPredecessor(inCorrect, root, inCorrect -> data) -> data);
        }

        else
        {
            printf ("* %s\n\n", p);
            printf ("  State : Correct\n\n");
        }

        p = strtok (NULL, " ");
    }

    printf ("\n\n*** Thanks ! ***\n\n");

}
