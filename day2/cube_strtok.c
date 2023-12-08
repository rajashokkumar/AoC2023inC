#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 512

int findGamePower(char *input)
{
    int red = 0;
    int green = 0;
    int blue = 0;
    int power = 0;
    char *token = NULL;
    char *set = NULL;
    char color[20];
    int num = 0;
    set = strrchr(input,':');
    set++;
    token = strtok(set,",;");
    while(token != NULL)
    {
        //printf("%s\n", token);
        num = 0;
        sscanf(token,"%d%s",&num,color);
        if(strcmp("red",color) == 0)
        {
            if(num > red)
            {
                red = num;
            }
        }
        if(strcmp("green",color) == 0)
        {
            if(num > green)
            {
                green = num;
            }
        }
        if(strcmp("blue",color) == 0)
        {
            if(num > blue)
            {
                blue = num;
            }
        }
        token = strtok(NULL,",;");
    }
    
    power = red * blue * green;
    //printf("power:%d red:%d green:%d blue:%d\n", power,red,green,blue);
    return power;
}
        

int main()
{
   FILE *fp;
   char   strInput[STR_MAX];
   int total = 0;
   int power = 0;
   int len = 0;
  
   fp = fopen("input_2.txt", "r");
   //fp = fopen("sample_2.txt", "r");
  
   if(fp == NULL)
   {
      printf("Unable to open file.\n");
      return -1;
   }
   memset((void *)strInput,'\0',STR_MAX);

   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
    len = strlen(strInput);
    if(strInput[len-1] == '\n')
    {
        strInput[len-1] = '\0';
    }

    //printf("%s\n", strInput);
    power = findGamePower(strInput);
    total += power;
   }
   printf("Total : %d\n", total);

    return 0;
}