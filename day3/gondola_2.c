#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256
//#define STR_MAX 12

#define PRINT 0

typedef struct _nums
{
    int num;
    int row;
    int start_col;
    int end_col;
    int valid;
    int used;
    struct _nums *myptr;
    struct _nums *next;
} NUMS;

NUMS *nums = NULL;

int symbol[STR_MAX][STR_MAX];
NUMS *number[STR_MAX][STR_MAX];


//use memset or gloabl  not need.
void resetSymbol()
{
   for(int i =0 ; i < STR_MAX;i++ )
   {
      for(int j=0; j < STR_MAX; j++)
      {
         symbol[i][j] = 0;
      }
   }
}



void resetNumber()
{
   for(int i =0 ; i <STR_MAX;i++ )
   {
      for(int j=0; j < STR_MAX; j++)
      {
         number[i][j] = NULL;
      }
   }
}

void addNum(int num, int row, int start, int end)
{
   NUMS *new;
   NUMS *temp;
   int col = 0;

   new = malloc(sizeof(NUMS));
   new->num = num;
   new->row = row;
   new->start_col = start;
   new->end_col = end;
   new->valid = 0; //Set valid to 0 at start
   new->next = NULL;
   new->myptr = new;
   new->used = 0;

    for(col = start; col <= end; col++)
    {
      number[row][col] = new;
    }
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
      printf("num:%d row:%d start_col:%d end_col:%d used:%d\n", 
                      temp->num, temp->row, temp->start_col, temp->end_col, temp->used);
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

void printNumber()
{
   for(int i =0 ; i <STR_MAX;i++ )
   {
      for(int j=0; j < STR_MAX; j++)
      {
         if(number[i][j])
             printf("i=%d, j=%d, 0x%08\n",i,j,number[i][j]);
      }
      printf("\n");
   }
   printf("\n");
}


long int findGearRatio()
{
   int i;
   int j;
   long int total;
   long int product;
   int numr0c0;
   int numr0c1;
   int numr0c2;
   int numr1c0;
   int numr1c2;
   int numr2c0;
   int numr2c1;
   int numr2c2;
   int count = 0;
   NUMS *temp;
   
   for(i=0; i< STR_MAX; i++)
   {
      for(j=0; j< STR_MAX; j++)
      {
         numr0c0 = 1;
         numr0c1 = 1;
         numr0c2 = 1;
         numr1c0 = 1;
         numr1c2 = 1;
         numr2c0 = 1;
         numr2c1 = 1;
         numr2c2 = 1;
         product = 0;
         count = 0;
         if(symbol[i][j])
         {
            //Fill Previous Row
            if(i-1 >= 0)
            {
               if(j-1 >= 0)
               {
                  temp = number[i-1][j-1];
                  if(temp) 
                  {
                     if(!temp->used)
                     {
                        numr0c0 = temp->num;
                        temp->used = 1;
                        count++;
                     }
                 

                  }
               }
               temp = number[i-1][j];
               if(temp) 
               {
                  if(!temp->used)
                  {
                     numr0c1 = temp->num;
                     temp->used = 1;
                     count++;
                  }
               }

               if(j+1 <= STR_MAX)
               {
                  temp = number[i-1][j+1];
                  if(temp) 
                  {
                     if(!temp->used)
                     {
                        numr0c2 = temp->num;
                        temp->used = 1;
                        count++;
                     }

                  }
               }
            }
       
            //Fill current Row
            {
               if(j-1 >= 0)
               {
                  temp = number[i][j-1];
                  if(temp) 
                  {
                     if(!temp->used)
                     {
                        numr1c0 = temp->num;
                        temp->used = 1;
                        count++;
                     }
                  }
               }
               if(j+1 <= STR_MAX)
               {
                  temp = number[i][j+1];
                  if(temp) 
                  {
                     if(!temp->used)
                     {
                        numr1c2 = temp->num;
                        temp->used = 1;
                        count++;
                     }

                  }
               }
            }
         
            //Fill Next Row
            if(i+1 <= STR_MAX)
            {
               if(j-1 >= 0)
               {
                  temp = number[i+1][j-1];
                  if(temp) 
                  {
                     if(!temp->used)
                     {
                        numr2c0 = temp->num;
                        temp->used = 1;
                        count++;
                     }
                  }
               }
               temp = number[i+1][j];
                if(temp) 
                  {
                     if(!temp->used)
                     {
                        numr2c1 = temp->num;
                        temp->used = 1;
                        count++;
                     }
                  }

               if(j+1 <= STR_MAX)
               {
                  temp = number[i+1][j+1];
                  if(temp) 
                  {
                     if(!temp->used)
                     {
                        numr2c2 = temp->num;
                        temp->used = 1;
                        count++;
                     }
                  }

               }
            }
            //printf("valid row:%d col:%d count:%d\n", i,j, count);
            if(count > 1)
            {
                product = numr0c0 * numr0c1 * numr0c2 * numr1c0 * numr1c2 * numr2c0 * numr2c1 * numr2c2;
                //printf(" product:%d numr0c0 %d numr0c1 %d numr0c2 %d numr1c0 %d numr1c2 %d numr2c0 %d numr2c1 %d numr2c2\n",
                  //product, numr0c0, numr0c1, numr0c2, numr1c0, numr1c2, numr2c0, numr2c1, numr2c2);
             }
             total = total + product;
         }
      }
   }
   return total;

}
            

int main(int argc, char * argv[])
{
   FILE *fp;
   char   strInput[STR_MAX];
   int len = 0;
   int row = 0;
   int col = 0;
   int startNum = 0;
   int num = 0;
   long int total = 0;
   int start_col= 0;

   
   //fp = fopen("input_2.txt", "r");
   fp = fopen(argv[1], "r");
  
   if(fp == NULL)
   {
      printf("Unable to open file[%s].\n", argv[1]);
      return -1;
   } else{
      printf(" Opened : %s\n", argv[1]);
   }
   memset((void *)strInput,'\0',STR_MAX);

   resetNumber();
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
#if PRINT
       printf("%s\n", strInput);
#endif
       col = 0;
       while(strInput[col] != '\0')
       {
           if(strInput[col] != '.')
           {
             if ((strInput[col] >= '0') && (strInput[col] <= '9'))
             {
#if PRINT
               printf("Num [%c] row:%d col:%d\n", strInput[col], row, col);
#endif
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
#if PRINT
               printf("Char [%c] row:%d col:%d\n", strInput[col], row, col);
#endif
               if(startNum)
               {
                  startNum = 0;
                  addNum(num, row, start_col,col-1);
#if PRINT
                  printf("num:%d row:%d col:%d\n", num, row, col);
#endif
               }
               if(strInput[col] == '*')
               {
                  symbol[row][col] = 1;
               }
             } 
           } else {
            if(startNum)
            {
               startNum = 0;
               addNum(num, row, start_col,col-1);
#if PRINT 
               printf("num:%d row:%d start_col:%d col:%d\n", num, row, start_col, col);
#endif
            }
           }
          col++;
        }
        if(startNum)
        {
            startNum = 0;
            addNum(num, row, start_col,col-1);
#if PRINT
            printf("num:%d row:%d start_col:%d col:%d\n", num, row, start_col, col);
#endif
        }
    row++;
   }

   //printNums();
   //printSymbol();
   //printNumber();
   //printValidNums();
   total = findGearRatio();
   printf("Total : %d\n", total);

   return 0;
}