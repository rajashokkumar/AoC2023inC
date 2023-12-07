#include<string.h>
#include <stdlib.h>
#include <stdio.h>

#define STR_MAX 256

int findNum(char *input)
{
   int firstNum = -1;
   int lastNum = -1;
   int final = 0;
   int num = -1;
   int i = 0;
   int len = strlen(input);

   while(input[i] != '\0')
   {
      if( input[i] >= '0' && input[i] <= '9')
      {
         num = input[i] - '0';
      }
      switch(input[i])
      {
         case 'o':
            if((i+2) < len)
            {
               if(input[i+1] == 'n' && input[i+2] == 'e')
               {
                  num = 1;
               }
            }
         break;

         case 't':
            if((i+2) < len)
            {
               if(input[i+1] == 'w' && input[i+2] == 'o')
               {
                  num = 2;
               }
            }
            if((i+4) < len)
            {
               if(input[i+1] == 'h' && input[i+2] == 'r' && input[i+3] == 'e' && input[i+4] == 'e')
               {
                  num = 3;
               }
            }
         break;

         case 'f':
            if((i+3) < len)
            {
               if(input[i+1] == 'o' && input[i+2] == 'u'&& input[i+3] == 'r')
               {
                  num = 4;
               }
            }
            if((i+3) < len)
            {
               if(input[i+1] == 'i' && input[i+2] == 'v'&& input[i+3] == 'e')
               {
                  num = 5;
               }
            }
         break;

         case 'e':
            if((i+4) < len)
            {
               if(input[i+1] == 'i' && input[i+2] == 'g'&&  input[i+3] == 'h' && input[i+4] == 't')
               {
                  num = 8;
               }
            }
         break;

        case 's':
            if((i+2) < len)
            {
               if((input[i+1] == 'i' && input[i+2] == 'x'))
               {
                  num = 6;
               }
            }
            if((i+4) < len)
            {
               if(input[i+1] == 'e' && input[i+2] == 'v' && input[i+3] == 'e' && input[i+4] == 'n')
               {
                  num = 7;
               }
            }
         break;

        case 'n':
            if((i+3) < len)
            {
               if(input[i+1] == 'i' && input[i+2] == 'n' && input[i+3] == 'e')
               {
                  num = 9;
               }
            }
         break;

         default:
         break;
      }
      if(num != -1)
      {
         if(firstNum == -1)
         {
            firstNum = num;
         }
         lastNum = num;
         num = -1;
      }
      i++;

   }
   final = firstNum * 10 + lastNum;
   if(final == -1)
   {
      final = 0;
   }

   printf("firstNum = %d lastNum=%d final=%d %s",firstNum, lastNum, final, input);

   return final;
}

int main()
{
   FILE *fp;
   char   strInput[STR_MAX];
   int total  = 0;
   int num = 0;

   //fp = fopen("sample_2.txt", "r");
   fp = fopen("input_2.txt", "r");
  
   if(fp == NULL)
   {
      printf("Unable to open file.\n");
      return -1;
   }
   memset((void *)strInput,'\0',STR_MAX);

   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
        num = findNum(strInput);
        //printf("num = %d str=%s", num, strInput);
        total = total + num;
        memset((void *)strInput,'\0',STR_MAX);
   }
   fclose(fp);
   printf("\nTotal = %d\n", total);
   return 0;
}
