#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256
//#define STR_MAX 50
int mapIndex = -1;
#define MAP_LEN  7

typedef unsigned long long int uint32;

//typedef double uint32;


typedef struct _list_seed
{
    uint32 seed;
    uint32 location;
    struct _list_seed *next;
}LIST_SEED;

LIST_SEED *seed = NULL;

typedef struct _list_map
{
    uint32 next;
    uint32 cur;
    uint32 range;
    struct _list_map *nextPtr;
}LIST_MAP;

char *map[] = {"seed-to-soil map:",
                "soil-to-fertilizer map:",
                "fertilizer-to-water map:",
                "water-to-light map:",
                "light-to-temperature map:",
                "temperature-to-humidity map:",
                "humidity-to-location map:" };

LIST_MAP *mapList[MAP_LEN];

void addSeed(uint32 num)
{
    LIST_SEED *new = NULL;
    LIST_SEED *temp = NULL;

    new = malloc(sizeof(LIST_SEED));
    new->seed = num;
    new->location = 0;
    new->next = NULL;

    if(seed == NULL)
    {
        seed = new;
    } else {
        temp = seed;
        while(temp->next)
        {
            temp= temp->next;
        }
        temp->next = new;
    }
}

void cleanSeed()
{
    LIST_SEED *temp = NULL;
    LIST_SEED *prev;

    temp = seed;
    while(temp)
    {
        prev = temp;
        temp= temp->next;
        free(prev);
    }
    seed = NULL;
}

void printSeed()
{
    LIST_SEED *temp = NULL;
    LIST_SEED *prev;

    temp = seed;
    while(temp)
    {
        prev = temp;
        printf("seed:%lld location:%ld\n", temp->seed, temp->location);
        temp= temp->next;
    }
}
void addMapList(uint32 next, uint32 cur, uint32 range)
{
    LIST_MAP *new = NULL;
    LIST_MAP *temp = NULL;

     if(mapIndex == -1)
     {
        printf("invalid mapIndex -1\n");
        return;
     }
    new = malloc(sizeof(LIST_MAP));
    new->next= next;
    new->cur = cur;
    new->range = range;
    new->nextPtr = NULL;

    if(mapList[mapIndex] == NULL)
    {
        mapList[mapIndex] = new;
    } else {
        temp = mapList[mapIndex];
        while(temp->nextPtr)
        {
            temp= temp->nextPtr;
        }
        temp->nextPtr = new;
    }
 
}

void printMapList()
{
    LIST_MAP *temp = NULL;
    LIST_MAP *prev;
    int i = 0;

    for(i=0; i < MAP_LEN; i++)
    {
        temp = mapList[i];
        printf(" == %s ==\n", map[i]);
        while(temp)
        {
            printf("next[%lld] curr[%lld] range[%lld]\n",temp->next,temp->cur, temp->range);
            temp = temp->nextPtr;
        }
        printf("===End==\n");
    }
}
void cleanMapList()
{
    LIST_MAP *temp = NULL;
    LIST_MAP *prev;
    int  i = 0;

    for(i=0; i < MAP_LEN; i++)
    {
        temp = mapList[i];
        while(temp)
        {
            prev = temp;
            temp = temp->nextPtr;
            free(prev);
        }
        mapList[i] = NULL;
    }
}
int isMap(char *line)
{
    int i = 0;
    for(i; i < MAP_LEN;i++)
    {
        if(strcmp(line, map[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int findIndexofMap(char *line)
{
    int i = 0;
    for(i; i < MAP_LEN;i++)
    {
        if(strcmp(line, map[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

void createEntry(char *input)
{
    int index = 0;
    uint32 next;
    uint32 cur;
    uint32 range;
    char *token;
    uint32 seed = 0;

    if(isMap(input))
    {
        mapIndex = findIndexofMap(input);
        return;
    }
    if(mapIndex != -1)
    {
        if(strlen(input) < 1)
        {
            //Skip empty lines
            return;
        }
        sscanf(input,"%ld %ld %ld", &next, & cur, &range);
        addMapList(next, cur, range);
    } else {
        if(strncmp(input, "seeds:", strlen("seeds:")) == 0)
        {
            token = strtok(strchr(input,' '), " ");
            while(token)
            {
                seed = atoll(token);
                addSeed(seed);
                token=strtok(NULL, " ");
            }
        }
    }
    return;
}

uint32 findIndexFromMapping(int index, uint32 mappingIndex)
{
    LIST_MAP *temp;
    uint32 nextMapIndex = 0;
    uint32 difference = 0;

    temp = mapList[index];
    //printf("index[%d] start_mappingIndex[%lld]\n", index, mappingIndex);
    while(temp)
    {
        //printf("index:%d mappingIndex:%lld temp->cur:%lld temp->range:%lld difference:%lld nextMapIndex:%lld\n",
        //    index, mappingIndex,temp->cur, temp->range,difference , nextMapIndex);
        if((mappingIndex >= temp->cur) && (mappingIndex < (temp->cur+temp->range)))
        {
            difference = mappingIndex - temp->cur;
            nextMapIndex = difference + temp->next;
            // printf("index:%d mappingIndex:%lld temp->cur:%lld temp->range:%lld difference:%lld nextMapIndex:%lld\n",
            //index, mappingIndex,temp->cur, temp->range,difference , nextMapIndex);
            return nextMapIndex;
        }
        temp = temp->nextPtr;
    }

    //printf("Range not found, so just keeping same index\n");
    nextMapIndex = mappingIndex;

    return nextMapIndex;
}
uint32 findLocationOfSeed(uint32 seedl)
{
    uint32 location = 0;
    int index = 0;
    uint32 mappingIndex;

    mappingIndex = seedl;
    for(index=0; index < MAP_LEN; index++)
    {
        //printf("index[%d] cur_mappingIndex[%lld]\n", index, mappingIndex);
        mappingIndex = findIndexFromMapping(index, mappingIndex);
        //printf("index[%d] next_mappingIndex[%lld]\n", index, mappingIndex);
    }

    location = mappingIndex;
    return location;
}
void fillSeedLocation()
{
    LIST_SEED *seed_temp;
    int index = 0;
    uint32 mappingIndex;
    uint32 location;

    seed_temp = seed;

    while(seed_temp)
    {
        location = findLocationOfSeed(seed_temp->seed);
        seed_temp->location = location;
        seed_temp = seed_temp->next;
    }
    return;
}

uint32 findCloseSeedLocation()
{
    uint32 least = -1;
    LIST_SEED *seed_temp;

    seed_temp = seed;

    while(seed_temp)
    {
        if (least == -1)
        {
            least = seed_temp->location;
       } else if (least > seed_temp->location) {
            least = seed_temp->location;
        }
        seed_temp = seed_temp->next;
    }
    return least;
}

uint32 findCloseSeedRangeLocation()
{
    uint32 least = -1;
    LIST_SEED *seed_temp;
    uint32 start = 0;
    uint32 end = 0;
    uint32 location = 0;

    seed_temp = seed;

    while(seed_temp)
    {
        start = seed_temp -> seed;
        seed_temp = seed_temp ->next;
        end = start + seed_temp->seed;
        for(start; start < end; start++)
        {
            location = findLocationOfSeed(start);
            if(least == -1)
            {
                least = location;
            }
            if(least > location)
            {
                least = location;
            }
        }
        seed_temp = seed_temp ->next;
    }

    return least;
}

int main(int argc, char * argv[])
{
   FILE *fp;
   char   strInput[STR_MAX];
   int len = 0;
   int row = 0;
   uint32 closest = 0;

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
       createEntry(strInput);

       row++;
   }
   
    //printMapList();
    //printSeed();
    //fillSeedLocation();
    //printSeed();

    closest = findCloseSeedRangeLocation();
    printf("Closest Location : %lld\n", closest);

    cleanSeed();
    cleanMapList();
   return 0;
}