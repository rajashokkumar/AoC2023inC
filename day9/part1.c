#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long int llint;

#define STR_MAX 512
#define MAX_ELEMENTS 800
#define MAX_STACK_ELE 200
llint row = 0;
llint maxElements = 0;
#define MAX_STACK 200

llint stack[MAX_STACK][MAX_STACK_ELE];

llint stackMax[MAX_STACK];

void resetStackMax()
{
    llint i = 0;
    llint j =0;

    for(i=0; i < MAX_STACK; i++)
    {
        stackMax[i] = -1;
        for(j=0;j < MAX_STACK_ELE;j++)
        {
            stack[i][j] = 0;
        }
    }
    
}
void pushstack(llint num, llint sno)
{
    //printf("%s:adding %d stackMax :%d sno:%d\n",__FUNCTION__,num, stackMax[sno], sno);
    if(stackMax[sno] >= MAX_STACK_ELE)
    {
        printf("Stack 1 FULL\n");
        return;
    }
    stackMax[sno]++;
    stack[sno][stackMax[sno]] = num;
    return;
}

llint peekstack(llint sno)
{
    if(stackMax[sno] < 0)
    {
        printf("Stack %d Empty\n", sno);
        return -1;
    }
    return stack[sno][stackMax[sno]];
}

llint popstack(llint sno)
{
    llint num = 0;
    if(stackMax[sno] < 0)
    {
        printf("Stack %d Empty\n", sno);
        return -1;
    }
    num = stack[sno][stackMax[sno]];
    stackMax[sno]--;
    return num;
}

void printStack(llint sno)
{
    llint i =0;
    printf("Here is the stack:\n");
    for(i=0; i <= stackMax[sno];i++)
    {
        printf("%d ", stack[sno][i]);
    }
    printf("\n");
}

llint countNode(llint sno)
{
    llint num1;
    llint num2;
    llint diff;
    llint count = stackMax[sno] ;
    llint i =0;

    //printf("%s check on sno:%d maxElements:%d\n",__FUNCTION__,sno, count);

    for(i=0; i < count;i++)
    {
        num1 = stack[sno][i];
        num2 = stack[sno][i+1];
        diff = num2 - num1;
        pushstack(diff, sno+1);
    }

    if(diff == 0)
    {
        return sno;
    } else {
        diff = countNode(sno+1);
    }
    return diff;
}
llint parseInput(char *input)
{
    char *token;
    llint num = 0;
    llint count = 0;
    llint num1 = 0;
    llint num2 = 0;
    llint diff = 0;
    llint i =0;
    llint lastNum = 0;

    row++;

    token = strtok(input, " ");
    while(token)
    {
        num = atoi(token);
        pushstack(num,0);
        count++;
        token = strtok(NULL," ");
    }
    maxElements = count;
    //printStack(0);
    count = countNode(0);
    //printf("Count Node: %d\n", count);
    for(i=count; i >= 0;i-- )
    {
        //printf("Max Ele:%d\n", stackMax[i]);
        if(i < count)
        {
          //  printf("Curr %d prev%d\n", stack[i][stackMax[i]+1], stack[i+1][stackMax[i+1]]);
            stack[i][stackMax[i]+1] = stack[i][stackMax[i]]+ stack[i+1][stackMax[i+1]];
            stackMax[i] = stackMax[i]+1;
        }
        printStack(i);

    }
    lastNum = stack[0][stackMax[0]];
    resetStackMax();
    return lastNum;

}



int main(int argc, char * argv[])
{
   FILE *fp;
   char strInput[STR_MAX];
   llint len = 0;
   llint total = 0;
   llint num = 0;
   llint row = 1;

   resetStackMax();

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
       num = parseInput(strInput);
       total = total + num;
       printf("For row %d last num is :%d\n",row, num);
       row++;
   }

   printf("Total : %d\n",total);

   fclose(fp);
   return 0;
}