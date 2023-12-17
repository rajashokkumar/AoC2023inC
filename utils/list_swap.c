#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int rank = 1;
typedef struct _list
{
    int rank;
    int num;
    struct _list *next;
}LIST;

LIST *list=NULL;

void addEntry(int num)
{
    LIST *new;
    LIST *temp = list;

    new = malloc(sizeof(LIST));
    new->num = num;
    new->next = NULL;
    new->rank = rank;
    rank++;
    if(temp == NULL)
    {
        list = new;
        return;
    }
    while(temp->next)
    {
        temp = temp->next;
    }
    temp->next = new;
}

void printList()
{
    LIST *temp = list;

    while(temp)
    {
        printf("num[%d] rank[%d]\n",temp->num, temp->rank);
        temp = temp->next;
    }
}

#if 0
void sortList()
{
    LIST *curr = list;
    LIST *next = NULL;
    LIST *prev = NULL;
    LIST *temp = NULL;

    while(curr->next)
    {
        next = curr->next;
        if(curr->num > next->num)
        {
            temp = next->next;
            if(prev)
            {
                prev->next = next;

            } else {
                list = next;
            }
            next->next = curr;
            curr->next = temp;
        }
        prev = curr;
        curr = curr->next;
    }
}
#else
void sortList()
{
    LIST *curr;
    LIST *next = NULL;
    int temp = 0;
    int rank = 0;
    LIST *outer = list;

   // while(outer)
    {
        curr = outer;
        while(curr->next)
        {
            next = curr->next;
            if(curr->num >  next->num)
            {
                temp = curr->num;
                rank = curr->rank;
                curr->num = next->num;
                curr->rank = next->rank;
                next->num = temp; 
                next->rank = rank;
            }
            curr = curr->next;
        }
 //       outer = outer->next;
    }
}
#endif
void cleanList()
{
    LIST *temp = list;
    LIST *prev = NULL;

    while(temp)
    {
        prev = temp;
        temp= temp->next;
        free(prev);
    }
    list = NULL;
}

int main()
{
    addEntry(3);
    addEntry(13);
    addEntry(11);
    addEntry(5);
    addEntry(1);
    printList();
    sortList();
    printf("=Sorted=\n");
    printList();

    cleanList();

}
