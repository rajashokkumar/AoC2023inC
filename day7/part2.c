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
    int threePair = 0;
    int twoPair = 0;
    int  numberOfJoker  = 0;
    int jokerUsed = 0;


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
        if((cardCount[0] == 5) || (cardCount[i] == 5) || ((cardCount[i] == 4) && (cardCount[0] == 1)) || ((cardCount[i] == 3) && (cardCount[0] == 2)) || ((cardCount[i] == 2) && (cardCount[0] == 3)) | ((cardCount[i] == 1) && (cardCount[0] == 4)))
        {
            hand =  6;//Five of kind  - All five match
            return hand;
        }
        if( (cardCount[i] == 4) || ((cardCount[i] == 3) && (cardCount[0] == 1)) || ((cardCount[i] == 2) && (cardCount[0] == 2)) || ((cardCount[i] == 1) && (cardCount[0] == 3)) )
        {
            hand =  5; //Four of kind - Four match
            return hand;
        }
        //if((cardCount[i] == 3) || ((cardCount[i] == 2) && (cardCount[0] == 1)) || ((cardCount[i] == 1) && (cardCount[0] == 2)))
        if(cardCount[i] == 3)
        {
            threePair++;
        }
        //if((cardCount[i] == 2) || ((cardCount[i] == 1) && (cardCount[0] == 1)))
        if(cardCount[i] == 2)
        {
            twoPair++;
        }
    }
    if ((threePair))
    {
        if(twoPair)
        {
            hand = 4;
        } else {
            hand = 3; // Three of kind - one 3 match
        }
    } else if(twoPair)
    {
        if(twoPair == 2)
        {
            hand = 2;// Two pair - two 2 matches
        } else {
            hand = 1; //One pair - one  2 match
        }
    }

    printf("cards[%s] hands[%d] jokerUsed:%d threepair:%d twopair:%d noofjoker:%d\n",cards, hand, jokerUsed, threePair,twoPair, numberOfJoker);

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