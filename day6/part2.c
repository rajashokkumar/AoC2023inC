#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256
#define ARRAY_MAX 2

typedef double  uint32;


uint32 time[ARRAY_MAX];
uint32 distance[ARRAY_MAX];
uint32 win[ARRAY_MAX];
int maxLen = 0;

void parseData(char *input)
{
    char *token;
    int len = 0;
    char *data;
    uint32 num = 0;
    uint32 value = 0;

    if(strncmp(input, "Time:", 5) == 0)
    {
        //Fill time array
        data = strchr(input,':');
        data++;//Moving :
        while(*data != '\0')
        {
            if((*data>= '0') && (*data <= '9'))
            {
                value = *data - '0';
                if(num == 0)
                {
                    num = value;
                } else {
                    num = num*10 + value;
                }
            }
            data++;
        }
        time[len] = num;
        len++;
    }
    if(strncmp(input,"Distance:",9) == 0)
    {
        //Fill distance array
        data = strchr(input,':');
        data++;//Moving :
        while(*data != '\0')
        {
            if((*data>= '0') && (*data <= '9'))
            {
                value = *data - '0';
                if(num == 0)
                {
                    num = value;
                } else {
                    num = num*10 + value;
                }
            }
            data++;
        }
        distance[len] = num;
        len++;
    }

    maxLen = len;
    return;
}

void printMap()
{
    int i = 0;
    printf(" Time  |  Distance  |  Win\n");
    for(i=0; i < maxLen; i++)
    {
        printf("%5lf %10llf %7llf\n",time[i], distance[i], win[i]);

    }
}

void findPossibleWins()
{
    int race = 0;
    uint32 tme = 0;
    uint32 dist = 0;
    uint32 millimeters = 0;
    uint32 count = 0;
    uint32 hold = 0;

    for(race = 0; race < maxLen; race++)
    {
        tme = time[race];
        dist = distance[race];
        count = 0;
        hold = 1;
        for(;hold<tme;hold++)
        {
            millimeters = (tme - hold) * hold;
            if(millimeters > dist)
            {
                count++;
            }
        }
        win[race] = count;
    }
}
    
uint32 findWaysToWin()
{
    int race = 0;
    uint32 product = 1;

    for(race =0; race < maxLen; race++)
    {
        if(win[race])
           product = product * win[race];
    }

    return product;
}

int main(int argc, char * argv[])
{
   FILE *fp;
   char strInput[STR_MAX];
   int len = 0;
   uint32 totalwin = 0;

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
       parseData(strInput);
   }
   
   findPossibleWins();
   //printMap();
   totalwin = findWaysToWin();
   printf("Total Ways to win: %.0llf", totalwin);
    return 0;
}