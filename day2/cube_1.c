#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int total_red = 12;
int total_green = 13;
int total_blue = 14;

#define STR_MAX 512

int isGameValid(char *input)
{
    int red = 0;
    int green = 0;
    int blue = 0;


    if (( red > total_red) || (green > total_green) || (blue > total_blue))
    {
        return 0;
    }
    return 1;
}

int main()
{
   FILE *fp;
   char   strInput[STR_MAX];
   int total = 0;
   int game_num = 1;
  
   //fp = fopen("input_1.txt", "r");
   fp = fopen("sample_1.txt", "r");
  
   if(fp == NULL)
   {
      printf("Unable to open file.\n");
      return -1;
   }
   memset((void *)strInput,'\0',STR_MAX);

   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
    if(isGameValid(strInput))
    {
        total += game_num;
    }
    game_num++;
    printf("%s", strInput);
   }
   printf("Total : %d\n", total);

    return 0;
}