#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char *name;
    int starting_time;
    int remaining_time;
} Process;

typedef struct Node
{
    Process data;
    struct Node* next;
} Node;

Node* newNode (Process data)
{
    Node *n = (Node*)malloc(sizeof(Node));
    n -> data = data;
    n -> next = NULL;
    return n;
}

typedef struct
{
    Node *head;
    Node *tail;
} Queue;

Queue* init()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q -> head = NULL;
    q -> tail = NULL;
    return q;
}

int isEmpty(Queue *q)
{
    if (q -> head == NULL)
        return 1;
    else
        return 0;
}

Process dequeue(Queue *q)
{
    Process value;
    if (q -> head)
    {
        Node *temp = q -> head;
        value = temp -> data;
        q -> head = q -> head -> next;
        free(temp);
        if (q -> head == NULL)
            q -> tail = NULL;
    }
    return value;
}

void enqueue(Queue *q, Process value)
{
    Node *n = newNode(value);
    if (q -> head == NULL)
        q -> head = q -> tail = n;
    else
    {
        q -> tail -> next = n;
        q -> tail = n;
    }
}

void destroy(Queue *q)
{
    int i, j = 0;
    Node *ptr = q -> head;
    while (ptr != NULL)
    {
        ptr = ptr -> next;
        j++;
    }
    for ( i = 0 ; i < j ; i++ )
    {
        if (q -> head != NULL)
        {
            Node *temp = q -> head;
            q -> head = q -> head -> next;
            free(temp);
            if (q -> head == NULL)
                q -> tail = NULL;
        }
    }
}

void RoundRobin(char* filename)
{
    int i = 0;
    int totalTime;

    Queue *pqueue = init();
    Queue *temp = init();

    FILE *fp;
    fp = fopen(filename,"r");

    Process p;

    char w[10],t[5],s[6],eq;
    fscanf(fp,"%s %s %s %c %d\n",w,t,s,&eq,&totalTime);

    while(1)
    {
        p.name = malloc(4);
        fscanf(fp,"%s %d %d\n",p.name,&p.starting_time,&p.remaining_time);
        enqueue(pqueue,p);
        i++;
        if (feof(fp))
            break;
    }

    int o;

    for ( i = 0 ;  i < totalTime ; i++ )
    {
        Process k;
        Process t;
        int z = 0;

        Node *ptr = pqueue -> head;
        while (ptr != NULL)
        {
            ptr = ptr -> next;
            z++;
        }

        for ( o = 0 ; o < z ; o ++ )
        {
            k = dequeue(pqueue);
            if (k.starting_time <= i)
            {
                enqueue(temp,k);
            }
            else
            {
                enqueue(pqueue,k);
            }
        }

        if (!isEmpty(temp))
        {
            t = dequeue(temp);
            t.remaining_time--;
            printf ("%s     (%d --> %d)",t.name,i,i+1);
            if (t.remaining_time == 0)
                printf (" %s aborts",t.name);
            else
                enqueue(temp,t);
            printf ("\n\n");
        }

        else
        {
            printf ("idle   (%d --> %d)\n\n",i,i+1);
        }

    }

    destroy(pqueue);
    destroy(temp);
    printf ("STOP\n\n");

    printf ("*** Thanks ! ***\n\n");

}

int main()
{
    printf ("\n");
    printf ("** Round Robin Scheduling **\n\n");
    char filename[261];
    puts("Enter file name or Ctrl+Z to exit:");
    puts("----------------------------------");
    while(fgets(filename, 260, stdin) != NULL)
    {
        printf ("\n");
        filename[strlen(filename)-1]='\0';
        if(fopen(filename,"r"))
            RoundRobin(filename);
        else
        {
            puts("File Not Found!");
            puts("----------------------------------\n");
        }
        puts("Enter file name or Ctrl+Z to exit:");
        puts("----------------------------------");
    }
}
