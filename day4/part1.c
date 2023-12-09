#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256


typedef struct _list
{
    int num;
    struct _list *next;
}LIST;

LIST *winning = NULL;
LIST *numbers = NULL;

void addWNum(int num)
{
    LIST *new = NULL;
    LIST *temp = NULL;

    new = malloc(sizeof(LIST));
    new->num = num;
    new->next = NULL;

    if(winning == NULL)
    {
        winning = new;
    } else {
        temp = winning;
        while(temp->next)
        {
            temp= temp->next;
        }
        temp->next = new;
    }
}

void addNNum(int num)
{
    LIST *new = NULL;
    LIST *temp = NULL;

    new = malloc(sizeof(LIST));
    new->num = num;
    new->next = NULL;
    if(numbers == NULL)
    {
        numbers = new;
    } else {
        temp = numbers;
        while(temp->next)
        {
            temp= temp->next;
        }
        temp->next = new;
    }
}

void cleanWNum()
{
    LIST *temp = NULL;
    LIST *prev;

    temp = winning;
    while(temp)
    {
        prev = temp;
        temp= temp->next;
        free(prev);
    }
    winning = NULL;
}

void cleanNNum()
{
    LIST *temp = NULL;
    LIST *prev;

    temp = numbers;
    while(temp)
    {
        prev = temp;
        temp= temp->next;
        free(prev);
    }
    numbers = NULL;
}

void addNumbers(char *input, int list)
{
    char *token = NULL;
    int index = 0;
    int num = -1;

    while(input[index] != '\0')
    {

        if(input[index] == ' ')
        {
            if(num != -1)
            {
                if(list == 0)
                {
                    addWNum(num);
                } else {
                    addNNum(num);
                }
                num = -1;
            }
        } else {
            if(num == -1)
            {
                num = input[index] - '0';
            } else {
                num = num * 10 +(input[index] - '0');
            }
        }
        index++;
    }
    if(num != -1)
    {
        if(list == 0)
        {
            addWNum(num);
        } else {
            addNNum(num);
        }
    }
}

int findPoints(char *input)
{
    char *token = NULL;
    int count = 0;
    char temp[STR_MAX];
    LIST *wtemp = NULL;
    LIST *ntemp = NULL;
    int index = 0;
    int points = 0;

     input = strchr(input,':');
     input++; //Skip :
    token = strtok(input,"|");
    while(token)
    {
       // printf("%s len:%d count:%d\n", token, strlen(token), count);
        addNumbers(token, count);
        count++;
        token=strtok(NULL,"|");
    }
    count = 0;
    ntemp = numbers;
    while(ntemp)
    {
        wtemp = winning;
        while(wtemp)
        {
            if(ntemp->num == wtemp->num)
            {
                count++;
            }
            wtemp = wtemp -> next;
        }
        ntemp = ntemp -> next;
    }
    cleanWNum();
    cleanNNum();
    if(count > 0)
         points = 1;
    for(index = 1; index < count; index++ )
    {
        points = points * 2;

    }
    //printf("points: %d count:%d\n", points, count);

    return points;
}
int main(int argc, char * argv[])
{
   FILE *fp;
   char   strInput[STR_MAX];
   int len = 0;
   int points= 0;
   int total=0;

   if(argc < 2)
   {
       printf("Invalid input\n");
       printf("Sample(./a.exe <input filename>)\n");
       return 1;
   }
   
   fp = fopen(argv[1], "r");
   if(fp == NULL)
   {
      printf("Unable to open file[%s].\n", argv[1]);
      return -1;
   } else {
      printf(" Opened : %s\n", argv[1]);
   }
   memset((void *)strInput,'\0',STR_MAX);

   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
       len = strlen(strInput);
       if(len >= STR_MAX)
       {
         printf("Increase the array size\n");
         return 0;//ERROR
       }
       if(strInput[len-1] == '\n')
       {
            len--;
            strInput[len] = '\0';
       }
       points = findPoints(strInput);
       total = total + points;
   }
   printf("Total Points: %d\n", total);
   return 0;
}