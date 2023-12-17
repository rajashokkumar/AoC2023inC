#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned long long int uint64;

#define STR_MAX 256
#define NUM_CARDS 6
#define MAX_CARDS 13

int rank = 1;
int cardCount = 0;
typedef struct _list
{
    char cards[NUM_CARDS];
    int bid;
    uint64 handStrength;
    int rank;
    int hand;
    struct _list *next;
}LIST;

LIST *list=NULL;

char *cardName[] =  {"J", "2", "3", "4", "5", "6", "7", "8", "9", "T", "Q", "K", "A"};

int findCardIndex(char card)
{
    int i = 0;
    for(i=0; i < MAX_CARDS;i++)
    {
        if(cardName[i][0] == card)
        {
            return i;
        }
    }
    //Index should never reach here.
    printf("==Bug Fix me== card[%c]\n", card);
    return 0;
}


int findHand(char *cards)
{
    int hand = 0;
    int cardCount[MAX_CARDS];
    int i = 0;
    int index = 0;
    int  numberOfJoker  = 0;
    int fiveMatch = 0;
    int fourMatch = 0;
    int threeMatch  = 0;
    int twoMatch = 0;

    for(i=0; i< MAX_CARDS;i++)
    {
        cardCount[i] = 0;
    }

    for(i=0;i< NUM_CARDS-1;i++)
    {
        index = findCardIndex(cards[i]);
        cardCount[index]++;
    }

    numberOfJoker = cardCount[0];

 //   printf("Number of jokers:%d\n", numberOfJoker);

    for(i=1; i< MAX_CARDS;i++)
    {
        if(cardCount[i] == 5)
        {
            fiveMatch++;
        }
        if(cardCount[i] == 4)
        {
            fourMatch++;
        }
        if(cardCount[i] == 3)
        {
            threeMatch++;
        }
        if(cardCount[i] == 2)
        {
            twoMatch++;
        }
    }

    if (fiveMatch)
    {
        hand =  6;//Five of kind  - All five match
         return hand;
    }

    if(fourMatch)
    {
        if(numberOfJoker == 1)
        {
             hand =  6;//Five of kind  - All five match
            return hand;
        } else {
            hand =  5;////Four of kind - Four match
            return hand;
        }
    }

    if(threeMatch)
    {
        if(numberOfJoker == 2)
        {
             hand =  6;//Five of kind  - All five match
            return hand;
        }
        if(numberOfJoker == 1)
        {
             hand =  5; //Four of kind - Four match
            return hand;
        }
        if(numberOfJoker == 0)
        {
            if(twoMatch)
            {
                 hand =  4;////Three of kind - 1 , Three match and 1, two match
                return hand;             
            } else {
                 hand =  3;////Three of kind - 1 , Three match and no two match
                return hand;                  
            }
        }
    }

    if(twoMatch)
    {
        if(numberOfJoker == 3)
        {
             hand =  6;//Five of kind  - All five match
            return hand;
        }
        if(numberOfJoker == 2)
        {
             hand =  5;////Four of kind - Four match
            return hand;
        }
        if(numberOfJoker == 1)
        {
            if(twoMatch == 2)
            {
                 hand =  4;////Three of kind - 1 , Three match and 1, two match
                return hand;             
            } else {
                 hand =  3;////Three of kind - 1 , Three match and no two match
                return hand;                  
            }
        }
        if(numberOfJoker == 0)
        {
            if(twoMatch == 2 ) 
            {
                hand = 2;// Two pair - two 2 matches
                return hand;             
            } else {
                 hand =  1; //One pair - one  2 match
                return hand;                  
            }
        }
    }

    if(numberOfJoker == 5)
    {
         hand =  6;//Five of kind  - All five match
         return hand;
    }

    if(numberOfJoker == 4)
    {
         hand =  6; //Five of kind  - All five match
         return hand;
    }

    if(numberOfJoker == 3)
    {
         hand =  5;  //Four of kind - Four match 
         return hand;
    }
    if(numberOfJoker == 2)
    {
         hand =  3;////Three of kind - 1 , Three match and no two match 
         return hand;
    }

    if(numberOfJoker == 1)
    {
         hand =  1; //One pair - one  2 match
         return hand;
    }
     return hand; //High card, all different cards
}

void addEntry(char *cards, int bid)
{
    LIST *new;
    LIST *prev = NULL;
    LIST *temp = list;
    int i = 0;
    int j = 0;

    new = malloc(sizeof(LIST));
    cardCount++;
    strcpy(new->cards, cards);
    new->bid = bid;
    new->next = NULL;
    new->handStrength = 0;
    new->rank = 0;
    new->hand = findHand(cards);

    if(temp == NULL)
    {
       // printf("Inserting %s at head hand[%d]\n",cards, new->hand);
        list = new;
        return;
    }

    //while(temp->next)
    while(temp)
    {
        if(new->hand < temp->hand)
        {
           //printf("Inserting Diff Hand %s[hand:%d] before %s[hand:%d]\n",cards, new->hand, temp->cards, temp->hand);
            //insert small at head
            if(prev)
            {
                prev->next = new;
                new->next = temp;
            } else {
                //insert at head
                new->next = temp;
                list = new;
            }
            return;
            
        } else if (new->hand == temp->hand)
        {
            for(i = 0; i < NUM_CARDS-1;i++)
            {
               // printf("hand[%d][Curr]%c index %d  , [Temp]%c index %d\n", new->hand, cards[i], findCardIndex(cards[i]), temp->cards[i], findCardIndex(temp->cards[i]));
                if(findCardIndex(cards[i]) < findCardIndex(temp->cards[i]))
                {
                   // printf("Inserting Same Hand %s before %s\n",cards, temp->cards);
                    //insert small at head
                    if(prev)
                     {
                         prev->next = new;
                         new->next = temp;
                     } else {
                        //insert at head
                         new->next = temp;
                         list = new;
                     }
                    return;
                } else if (findCardIndex(cards[i]) == findCardIndex(temp->cards[i]))
                {
                    //Find next card
                    continue;
                } else {
                    break;
                }

            }
        } else {
            //move to next element
        }
        prev = temp;
        temp = temp->next;
    }
    prev->next = new;
    //printf("Inserting %s hand:%d at tail end\n", cards, new->hand);
    //temp->next = new;
}

void addRank()
{
    LIST *temp = list;
    int rank = 1;

    while(temp)
    {
        //printf("Adding rank: %d for card:%s\n", rank, temp->cards);
         temp->rank = rank;
         rank++;
        temp = temp->next;
    }

}
void printList()
{
    LIST *temp = list;

    while(temp)
    {
        printf("cards[%s] bid[%d] hand[%d] rank[%d]\n",
                         temp->cards, temp->bid, temp->hand, temp->rank);
        temp = temp->next;
    }
}

uint64 findTotalWin()
{
    uint64 totalWin = 0;
    LIST *temp = list;

    while(temp)
    {
        totalWin = totalWin +  temp->bid * temp->rank;
        temp = temp->next;
    }
    return totalWin;
}
void cleanList()
{
    LIST *temp = list;
    LIST *prev = NULL;

    while(temp)
    {
        prev = temp;
        temp= temp->next;
        free(prev);
    }

    list = NULL;
}
void parseInput(char *input)
{
    char *token;
    int bid;
    char cards[NUM_CARDS];

    token = strtok(input, " ");
    strcpy(cards, token);
    token = strtok(NULL, " ");
    bid = atoi(token);
    //printf("cards:[%s] bid:[%d]\n", cards, bid);

    addEntry(cards,bid);

}
//Find hand strength
//Find Rank
//Find total winning

int main(int argc, char * argv[])
{
   FILE *fp;
   char strInput[STR_MAX];
   int len = 0;
   uint64 totalwin = 0;

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
       parseInput(strInput);
   }

   addRank();
  printList();
   totalwin = findTotalWin();
   printf("Solution: %d\n", totalwin);
   printf("Total card :%d\n", cardCount);

   fclose(fp);
   cleanList();
   return 0;
}