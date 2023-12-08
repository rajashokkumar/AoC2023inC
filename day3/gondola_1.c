#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256
//#define STR_MAX 15

typedef struct _nums
{
    int num;
    int row;
    int start_col;
    int end_col;
    int valid;
    struct _nums *next;
} NUMS;

NUMS *nums = NULL;


int symbol[STR_MAX][STR_MAX];

int valid[STR_MAX][STR_MAX];

//use memset or gloabl  not need.
void resetSymbol()
{
   for(int i =0 ; i <STR_MAX;i++ )
   {
      for(int j=0; j < STR_MAX; j++)
      {
         symbol[i][j] = 0;
      }
   }
}

void resetValid()
{
   for(int i =0 ; i <STR_MAX;i++ )
   {
      for(int j=0; j < STR_MAX; j++)
      {
         valid[i][j] = 0;
      }
   }
}

void addNum(int num, int row, int start, int end)
{
   NUMS *new;
   NUMS *temp;
   new = malloc(sizeof(NUMS));
   new->num = num;
   new->row = row;
   new->start_col = start;
   new->end_col = end;
   new->valid = 0; //Set valid to 0 at start
   new->next = NULL;

   if(nums == NULL)
   {
      nums = new;
   } else {

       temp = nums;
      while(temp->next != NULL)
      {
         temp = temp->next;
      }
      temp->next = new;
   }
}

void printNums()
{
   NUMS *temp;
   temp = nums;

   while(temp)
   {
      printf("num:%d row:%d start_col:%d end_col:%d valid:%d\n", 
                      temp->num, temp->row, temp->start_col, temp->end_col, temp->valid);
      temp = temp->next;
   }
}



void printSymbol()
{
   for(int i =0 ; i <STR_MAX;i++ )
   {
      for(int j=0; j < STR_MAX; j++)
      {
         printf("%d",symbol[i][j]);
      }
      printf("\n");
   }
   printf("\n");
}


void printValid()
{
   for(int i =0 ; i <STR_MAX;i++ )
   {
      for(int j=0; j < STR_MAX; j++)
      {
         printf("%d",valid[i][j]);
      }
      printf("\n");
   }
   printf("\n");
}
void fillValid()
{
   int i;
   int j;

   for(i=0; i< STR_MAX; i++)
   {
      for(j=0; j< STR_MAX; j++)
      {
         if(symbol[i][j])
         {
            //Fill Previous Row
            if(i-1 >= 0)
            {
               if(j-1 >= 0)
               {
                  valid[i-1][j-1] = 1;
               }
               valid[i-1][j] = 1;
               if(j+1 <= STR_MAX)
               {
                  valid[i-1][j+1] = 1;
               }
            }
       
            //Fill current Row
            {
               if(j-1 >= 0)
               {
                  valid[i][j-1] = 1;
               }
               valid[i][j] = 1;
               if(j+1 <= STR_MAX)
               {
                  valid[i][j+1] = 1;
               }
            }
         
            //Fill Next Row
            if(i+1 <= STR_MAX)
            {
               if(j-1 >= 0)
               {
                  valid[i+1][j-1] = 1;
               }
               valid[i+1][j] = 1;
               if(j+1 <= STR_MAX)
               {
                  valid[i+1][j+1] = 1;
               }
            }
         }
      }
   }
   return ;
}

void setValid()
{
   NUMS *temp;
   temp = nums;
   int row=0;
   int col=0;
   int index=0;

   while(temp)
   {
#if 0
      printf("num:%d row:%d start_col:%d end_col:%d start:%d\n", 
                      temp->num, temp->row, temp->start_col, temp->end_col, temp->valid);
#endif
      row = temp->row;
      for(index=temp->start_col; index <= temp->end_col; index++)
      {
         if(valid[row][index])
         {
            temp->valid = 1;
         }
      }
#if 0
      printf("num:%d row:%d start_col:%d end_col:%d start:%d\n", 
                      temp->num, temp->row, temp->start_col, temp->end_col, temp->valid);
#endif
      temp = temp->next;
   }
}


int findValidNumSum()
{
   NUMS *temp;
   temp = nums;
   int total = 0;

   while(temp)
   {
      if(temp->valid)
      {
         total = total + temp->num;
      }
      temp = temp->next;
   }
   return total;
}

int main()
{
   FILE *fp;
   char   strInput[STR_MAX];
   int len = 0;
   int row = 0;
   int col = 0;
   int startNum = 0;
   int num = 0;
   int total = 0;
   int start_col= 0;

   fp = fopen("input_1.txt", "r");
   //fp = fopen("sample_1.txt", "r");
  
   if(fp == NULL)
   {
      printf("Unable to open file.\n");
      return -1;
   }
   memset((void *)strInput,'\0',STR_MAX);

   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
       len = strlen(strInput);
       if(len >= STR_MAX)
       {
         printf("Increase the array size\n");
         return 1;//ERROR
       }
       if(strInput[len-1] == '\n')
       {
            len--;
            strInput[len] = '\0';
       }
       //printf("%s\n", strInput);
       col = 0;
       while(strInput[col] != '\0')
       {
           if(strInput[col] != '.')
           {
             if ((strInput[col] >= '0') && (strInput[col] <= '9'))
             {
               //printf("Num [%c] row:%d col:%d\n", strInput[col], row, col);
               if(startNum)
               {
                  num = num*10 + strInput[col] - '0';
               } else {
                  start_col = col;
                  num = strInput[col] - '0';
                  startNum = 1;
               }
             }
             else
             {
               // printf("Char [%c] row:%d col:%d\n", strInput[col], row, col);
               if(startNum)
               {
                  startNum = 0;
                  addNum(num, row, start_col,col-1);
                  //printf("num:%d row:%d col:%d\n", num, row, col);
               }
               symbol[row][col] = 1;
             } 
           } else {
            if(startNum)
            {
               startNum = 0;
               addNum(num, row, start_col,col-1);
               //printf("num:%d row:%d start_col:%d col:%d\n", num, row, start_col, col);
            }
           }
          col++;
        }
        if(startNum)
        {
            startNum = 0;
            addNum(num, row, start_col,col-1);
            //printf("num:%d row:%d start_col:%d col:%d\n", num, row, start_col, col);
        }


    row++;
   }
   //printNums();
   //printSymbol();
   //printf("Total : %d\n", total);
   fillValid();
  // printValid();
   setValid();
   //printNums();
   total = findValidNumSum();
   printf("Total : %d\n", total);


   return 0;
}