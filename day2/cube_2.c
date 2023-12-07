#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int total_red = 12;
int total_green = 13;
int total_blue = 14;

#define STR_MAX 512

int findGamePower(char *input)
{
    int red = 0;
    int green = 0;
    int blue = 0;
    char subset[STR_MAX];
    int len = strlen(input);
    int sub = 0;
    int i = 0;
    int count = 0;
    int power = 0;

    char color_count[STR_MAX];
    int color_index = 0;

    char color[20];
    int num = 0;

    while((input[i] != '\0') && (input[i] != ':'))
    {
        i++;
    }
    i++; //:
    i++; //Space after :
    //printf("len: %d index:%d rem string: [%s", len, i, &input[i]);
    while(i < len)
    {
        sub = 0;
        //printf("len: %d index:%d rem string: [%s", len, i, &input[i]);
        while((input[i] != ';') && (i <len))
        {
            subset[sub] = input[i];
            i++;
            sub++;
        }
        if(i >= len)
           sub--;
        i++;//;
        i++;// space after ;

        subset[sub] = '\0';
        //printf("subset:[%s] sub[%d]\n", subset, sub);
        color_index = 0;
        while(color_index < sub)
        {
            int j = 0;
            num = 0;
            while((subset[color_index] != ',') && (color_index < sub))
            {
                color_count[j] = subset[color_index];
                j++;
                color_index++;
            }
            color_count[j] = '\0';
            color_index++; //,
            color_index++;// Space after ,
            sscanf(color_count,"%d%s",&num,color);
            //printf("color_count[%s] num[%d]\n", color_count, num);
            if(strcmp("red",color) == 0)
            {
                if(num > red)
                {
                    red = num;
                }             
            }
            if(strcmp("blue",color) == 0)
            {
                if(num > blue)
                {
                    blue = num;
                }             
            }
            if(strcmp("green",color) == 0)
            {
                if(num > green)
                {
                    green = num;
                }             
            }
#if 0
             if(count > 4)
           break;
        else
           count++;
#endif
        }
#if 0
        if(count > 4)
           break;
        else
           count++;
#endif
        
    }
    power = red * green * blue;
    return power;
}

int main()
{
   FILE *fp;
   char   strInput[STR_MAX];
   int total = 0;
   int power = 0;
  
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
    //printf("%s", strInput);
    power = findGamePower(strInput);
    total += power;
   }
   printf("Total : %d\n", total);

    return 0;
}