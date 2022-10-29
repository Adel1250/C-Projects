#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    char firstname[20];
    char lastname[20];
    char address[50];
    char email[50];
    char phone[30];
    date bd;

} contact;

int i,lines;

contact c[100];

int read_contact(FILE *fp)
{
    int lines = 0, i;
    if(fp == NULL)
    {
        printf("Error !\n");
        exit(0);
    }
    while(1)
    {
        i=lines;
        fscanf(fp,"%[^,],%[^,],%[^,],%[^,],%[^,],%d-%d-%d\n",c[i].firstname,c[i].lastname,c[i].address,c[i].email,c[i].phone,&c[i].bd.day,&c[i].bd.month,&c[i].bd.year);
        lines++;
        if(feof(fp))
            break;
    }
    return lines;

}

void load()
{
    for(i=0; i<lines; i++)
    {
        printf("* Contact #%d : \n* First name : %s\n* Last name : %s\n* Address : %s\n* Email : %s\n* Phone number : %s\n* Birth date : %d-%d-%d\n\n",i+1,c[i].firstname,c[i].lastname,c[i].address,c[i].email,c[i].phone,c[i].bd.day,c[i].bd.month,c[i].bd.year);
    }
}

void add()
{
    i=lines;
    printf("* Enter the first name : ");
    scanf("%s",c[i].firstname);
    printf ("\n");
    printf("* Enter the last name : ");
    scanf("%s",c[i].lastname);
    printf ("\n");
    printf("* Enter the address : ");
    getchar();
    gets(c[i].address);
    printf ("\n");
    printf("* Enter the email : ");
    scanf("%s",c[i].email);
    printf ("\n");
    printf("* Enter the phone number : ");
    scanf("%s",c[i].phone);
    printf ("\n");
    printf("* Enter the birth date : \n\n");
    printf ("* The day : ");
    scanf("%d",&c[i].bd.day);
    printf ("\n");
    printf ("* The month : ");
    scanf("%d",&c[i].bd.month);
    printf ("\n");
    printf ("* The year : ");
    scanf("%d",&c[i].bd.year);
    printf ("\n");
    lines++;
}

void save(FILE *fp)
{
    fp = fopen("contacts.txt","w");
    int j;
    for(j=0 ; j<lines ; j++)
        fprintf(fp,"%s,%s,%s,%s,%s,%d-%d-%d\n",c[j].firstname,c[j].lastname,c[j].address,c[j].email,c[j].phone,c[j].bd.day,c[j].bd.month,c[j].bd.year);
    fclose(fp);
}

int sort_cont(int mode)
{
    int length=lines;
    int pass;
    contact temp;
    if(mode==1)
    {
        for(pass=1; pass<length; pass++)
        {
            for(i=0; i<length-pass; i++)
            {
                if(c[i].bd.year>c[i+1].bd.year)
                {
                    temp=c[i];
                    c[i]=c[i+1];
                    c[i+1]=temp;
                }
                else if(c[i].bd.year==c[i+1].bd.year&&c[i].bd.month>c[i+1].bd.month)
                {
                    temp=c[i];
                    c[i]=c[i+1];
                    c[i+1]=temp;
                }
                else if(c[i].bd.year==c[i+1].bd.year&&c[i].bd.month==c[i+1].bd.month&&c[i].bd.day>c[i+1].bd.day)
                {
                    temp=c[i];
                    c[i]=c[i+1];
                    c[i+1]=temp;
                }
            }

        }
    }
    else if(mode==2)
    {
        for(pass=1; pass<length; pass++)
        {
            for(i=0; i<length-pass; i++)
            {
                if(strcasecmp(c[i].lastname,c[i+1].lastname)==1)
                {
                    temp=c[i];
                    c[i]=c[i+1];
                    c[i+1]=temp;
                }
                else if(!(strcasecmp(c[i].lastname,c[i+1].lastname))&&strcasecmp(c[i].firstname,c[i+1].firstname)==1)
                {
                    temp=c[i];
                    c[i]=c[i+1];
                    c[i+1]=temp;
                }
            }
        }
    }
    return length;
}

void search_contacts(char *target)
{
    int i;
    contact temp[lines];
    int counter=0;
    for(i=0; i<lines; i++)
    {
        if(!strcasecmp(target,c[i].lastname))
        {
            temp[counter++]=c[i];
        }
    }
    if(counter >= 1 )
    {
        printf("\n*** There is %d contacts with this last name ***\n\n",counter);
    }
    else
        printf("\n* This contact doesn't exist\n\n");
    for(i=0; i<counter; i++)
        printf("* First name : %s\n* Last name : %s\n* Address : %s\n* E-mail :  %s\n* Phone : %s\n* Birth date : %d- %d- %d\n\n",temp[i].firstname,temp[i].lastname,temp[i].address,temp[i].email,temp[i].phone,temp[i].bd.day,temp[i].bd.month,temp[i].bd.year);
}

void delete_contact(char *target)
{
    int i,pos;
    int check = 0;
    for(i=0; i<lines; i++)
    {
        if(!strcasecmp(target,c[i].lastname))
        {
            check++;
            lines--;
            for(pos=i; pos<lines; pos++)
                c[pos]=c[pos+1];

            if(!strcasecmp(target,c[i].lastname))
                i--;
        }

    }
    if (check)
        printf ("\n*** Successfully deleted this contact ***\n\n");
    else if(!check)
        printf("\n*** This contact doesn't exist ***\n\n");
}

void modify(char *target)
{
    int i,ch,p[lines];
    contact temp[lines];
    int counter=0;
    for(i=0; i<lines; i++)
    {
        if(!strcasecmp(target,c[i].lastname))
        {
            temp[counter]=c[i];
            p[counter]=i;
            counter++;
        }
    }
    if(counter  > 1)
    {
        printf("\n*** There is %d contacts with this last name choose one to modify *** \n\n",counter);
        for(i=0; i<counter; i++)
            printf("\n* Contact #%d : \n* First name : %s\n* Last name : %s\n* Address : %s\n* E-mail : %s\n* Phone number : %s\n* Birth date : %d %d %d\n\n",p[i]+1,temp[i].firstname,temp[i].lastname,temp[i].address,temp[i].email,temp[i].phone,temp[i].bd.day,temp[i].bd.month,temp[i].bd.year);
        printf ("* Enter your choice : ");
        scanf("%d",&ch);
        printf ("\n");
        for(i=0; i<counter; i++)
        {
            if(ch==p[i]+1)
            {
                i=p[i];
                printf("\n*** Before Modifying ***\n\n* First name : %s\n* Last name : %s\n* Address : %s\n* E-mail : %s\n* Phone number : %s\n* Date : %d- %d- %d\n\n",c[i].firstname,c[i].lastname,c[i].address,c[i].email,c[i].phone,c[i].bd.day,c[i].bd.month,c[i].bd.year);
                printf("* Enter the first name : ");
                scanf("%s",c[i].firstname);
                printf ("\n");
                printf("* Enter the last name : ");
                scanf("%s",c[i].lastname);
                printf ("\n");
                printf("* Enter the address : ");
                getchar();
                gets(c[i].address);
                printf ("\n");
                printf("* Enter the E-mail : ");
                scanf("%s",c[i].email);
                printf ("\n");
                printf("* Enter the phone number : ");
                scanf("%s",c[i].phone);
                printf ("\n");
                printf("* Enter birth date : \n\n");
                printf ("* The day : ");
                scanf("%d",&c[i].bd.day);
                printf ("\n");
                printf ("* The month : ");
                scanf("%d",&c[i].bd.month);
                printf ("\n");
                printf ("* The year : ");
                scanf("%d",&c[i].bd.year);
                printf ("\n");
                printf("\n*** After Modifying ***\n\n* First name : %s\n* Last name : %s\n* Address : %s\n* E-mail : %s\n* Phone number : %s\n* Date : %d- %d- %d\n\n",c[i].firstname,c[i].lastname,c[i].address,c[i].email,c[i].phone,c[i].bd.day,c[i].bd.month,c[i].bd.year);
                break;
            }
        }
    }

    else if(!counter)
        printf("\n***There is no contact with this last name***\n");
    else if(counter==1)
    {
        i=p[0];
        printf("\n*** Before Modifying ***\n\n* First name : %s\n* Last name : %s\n* Address : %s\n* E-mail : %s\n* Phone number : %s\n* Date : %d- %d- %d\n\n",c[i].firstname,c[i].lastname,c[i].address,c[i].email,c[i].phone,c[i].bd.day,c[i].bd.month,c[i].bd.year);
        printf("* Enter the first name : ");
        scanf("%s",c[i].firstname);
        printf ("\n");
        printf("* Enter the last name : ");
        scanf("%s",c[i].lastname);
        printf ("\n");
        printf("* Enter the address : ");
        getchar();
        gets(c[i].address);
        printf ("\n");
        printf("* Enter the E-mail : ");
        scanf("%s",c[i].email);
        printf ("\n");
        printf("* Enter the phone number : ");
        scanf("%s",c[i].phone);
        printf ("\n");
        printf("* Enter birth date : \n\n");
        printf ("* The day : ");
        scanf("%d",&c[i].bd.day);
        printf ("\n");
        printf ("* The month : ");
        scanf("%d",&c[i].bd.month);
        printf ("\n");
        printf ("* The year : ");
        scanf("%d",&c[i].bd.year);
        printf ("\n");
        printf("\n*** After Modifying ***\n\n* First name : %s\n* Last name : %s\n* Address : %s\n* E-mail : %s\n* Phone number : %s\n* Date : %d- %d- %d\n\n",c[i].firstname,c[i].lastname,c[i].address,c[i].email,c[i].phone,c[i].bd.day,c[i].bd.month,c[i].bd.year);

    }
}
int main()
{
    system("color f0");
    int ch,ch2;
    char target[20];
    printf("\n** Welcome to the PHONEBOOK **\n\n");
    FILE *fp;
    fp=fopen("contacts.txt","r");
    lines=read_contact(fp);
    while(1)
    {
        printf("** Menu **\n");
        printf("\n 1.LOAD\n 2.SEARCH\n 3.ADD\n 4.DELETE\n 5.MODIFY\n 6.SORT\n 7.SAVE\n 8.EXIT\n\n");
        printf ("* Enter your choice : ");
        scanf("%d",&ch);
        printf ("\n");
        system("cls");
        switch(ch)
        {
        case 1:
            load();
            break;
        case 2:
            printf("* Enter last name of the contact you want to search for : ");
            scanf("%s",target);
            search_contacts(target);
            break;
        case 3:
            add();
            break;
        case 4:
            printf("* Enter last name of the contact you want to delete : ");
            scanf("%s",target);
            delete_contact(target);
            break;
        case 5:
            printf("* Enter last name of the contact you want to modify : ");
            scanf("%s",target);
            modify(target);
            break;
        case 6:
            printf("* Choose one of the following : \n\n 1.Sort according to Birth date\n 2.Sort according to name\n\n");
            printf ("* Enter your choice : ");
            scanf("%d",&ch2);
            printf ("\n");
            load(sort_cont(ch2));
            break;
        case 7:
            save(fp);
            break;
        case 8:
            printf ("\n\n*** Thanks ! ***\n\n");
            exit(0);
            break;
        default :
            printf("X Invalid Input X\n\n");
        }
    }
    return 0;
}
