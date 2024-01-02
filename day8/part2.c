#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint32;

#define STR_MAX 512
#define MAX_ELEMENTS 800

char instruction[512];

char inde[MAX_ELEMENTS][STR_MAX];

typedef struct _list
{
    char index[STR_MAX];
    char left[STR_MAX];
    char right[STR_MAX];
}LIST;

LIST input[MAX_ELEMENTS];

int findIndex(char *input)
{
    int i = -1;

    //Return if entry already found.
    for(i=0; i < MAX_ELEMENTS; i++)
    {
        //Find empty index and update the value
        if(strcmp(&inde[i][0],input) == 0)
        {
            //printf("Entry [%s]  found at index :%d\n",input, i);
            return i;
        }
    }
    i = -1;
    return i;
}

void addIndex(char *input)
{
    int i = 0;

    //printf("Add index : %s\n", input);
    //Return if entry already found.
    i = findIndex(input);
    if(i != -1)
    {
        //printf("Entry [%s] already found at index: %d\n", input, i);
        return;
    }

    // Add entry
    for(i=0; i < MAX_ELEMENTS; i++)
    {
        //Find empty index and update the value
        if(strcmp(&inde[i][0],"") == 0)
        {
            strcpy(&inde[i][0], input);
            //printf("Add entry [%s] at index :%d\n",input, i);
            return;
        }
    }
}

void addDirection(char *ind, char *left, char *right)
{
    int i = -1;
    //printf("Add dir for index[%s] left[%s] right[%s]\n", ind, left, right);

    i = findIndex(ind);
    if(i == -1)
    {
        printf("Index not found for [%s]\n", ind);
        return;
    }

    strcpy(input[i].index, ind);
    strcpy(input[i].left, left);
    strcpy(input[i].right, right);
    return;
}


void parseInput(char *input)
{
    char index[STR_MAX];
    char left[STR_MAX];
    char right[STR_MAX];

    char *token;
    

    token = strtok(input," =(,)");
    if(token)
    {
        strcpy(index, token);
    }

    token=strtok(NULL," =(,)");
    if(token)
    {
        strcpy(left, token);
    }

    token=strtok(NULL," =(,)");

    if(token)
    {
        strcpy(right, token);
    }
    addIndex(index);
    addDirection(index, left, right);
}


void printInput()
{
    int i =0;

    for(i = 0; i < MAX_ELEMENTS; i++)
    {
        if(strcmp(&inde[i][0], "") != 0)
        {
            printf("Index: %s Left:%s Right:%s\n", input[i].index, input[i].left, input[i].right);
        }
    }

}

int countNode()
{
    int count = 1;
    int i = 0;
    int len = 0;
    int startIndex = 0;
    char str[STR_MAX];
    int idx = 0;
    

    len = strlen(instruction);

    startIndex = findIndex("AAA");
    idx = startIndex;

loopagain:

    //printf("Starting index is : %d [Instrcution len: %d]\n", idx, len);

    for(i=0; i < len; i++)
    {
        if(instruction[i] == 'L')
        {
            strcpy(str,input[idx].left);
        } else {
            strcpy(str,input[idx].right);
        }
        if(strcmp(str,"ZZZ") == 0)
        {
            return count;
        } else {
            count++;
            idx = findIndex(str);
        }
    }
    if(strcmp(str,"ZZZ") != 0)
    {
        goto loopagain;
    }
    return count;

}
int main(int argc, char * argv[])
{
   FILE *fp;
   char strInput[STR_MAX];
   int len = 0;

   if(argc < 2)
   {
       printf("Input file missing\n");
       printf("Sample: ./a.exe ./sample.txt)\n");
       return 1;
   }
   fp = fopen(argv[1], "r");
   if(fp == NULL)
   {
      printf("Unable to open file[%s].\n", argv[1]);
      return -1;
   } 
   
   memset((void *)strInput,'\0',STR_MAX);

    if(fgets(strInput, STR_MAX, fp) != NULL)
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
       strcpy(instruction,strInput);

    }

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
       parseInput(strInput);
   }

   //printInput();

   printf("Total steps: %d\n",countNode());

   fclose(fp);
   return 0;
}