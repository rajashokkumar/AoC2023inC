#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_MAX 256
#define MAX_LINES 1024

#if 1
int fileRead(char *input, char ***lines)
{
   FILE *fp;
   char strInput[STR_MAX];
   int len = 0;
   int count = 0;
   char **line = NULL;
   int row = 0;
 
   fp = fopen(input, "r");
   if(fp == NULL)
   {
      printf("Unable to open file[%s].\n", input);
      return -1;
   } 
   
   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
    row++;
   }
   if(row > MAX_LINES)
   {
     printf("More than  %d lines, increase line size\n",MAX_LINES);
     return -3;
   } else {
    printf("No of lines in file: %d\n", row);
   }
   rewind(fp);

   line = (char **)malloc(row*sizeof(char *));
   printf("line:%p\n", line);
   *lines = line;

   memset((void *)strInput,'\0',STR_MAX);
   count = 0;
   while (fgets(strInput, STR_MAX, fp) != NULL)
   {
       len = strlen(strInput);
       if(len >= STR_MAX)
       {
         printf("Increase the array size\n");
         return -2;//ERROR
       }
       if(strInput[len-1] == '\n')
       {
            len--;
            strInput[len] = '\0';
       }
       printf("Now reading line %d :[%s] ",count+1, strInput);
       line[count] = (char *)malloc(sizeof(char) * len);
       printf("Storing in %p\n", &line[count]);
       strcpy(line[count], strInput);
       count++;

   }
   fclose(fp);
   return row;
}
#else

char** fileRead(const char* filename, int* lineCount) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Count the number of lines in the file
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            count++;
        }
    }
    rewind(file);

    // Allocate memory for the array of char pointers
    char** lines = (char**)malloc(count * sizeof(char*));
    if (lines == NULL) {
        perror("Memory allocation error");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for each line
    for (int i = 0; i < count; i++) {
        lines[i] = (char*)malloc(STR_MAX * sizeof(char));
        if (lines[i] == NULL) {
            perror("Memory allocation error");
            exit(EXIT_FAILURE);
        }
    }

    // Read lines from the file and store them in the array
    int i = 0;
    while (fgets(lines[i], STR_MAX, file) != NULL) {
        // Remove newline character if present
        char* newline = strchr(lines[i], '\n');
        if (newline != NULL) {
            *newline = '\0';
        }
        i++;
    }

    *lineCount = count;
    fclose(file);
    return lines;
}
#endif

int main(int argc, char *argv[])
{
  #if 1
    char **lines;
    int noOfLines = 0;
    int row;
    int i ;

    row = fileRead(argv[1], &lines);
    printf("Number of lines in file: %d\n", row);

    for(i=0; i < row; i++)
    {
      printf("line:%p %d[%s]\n",&lines[i],i, lines[i]);
      free(lines[i]);
    }
    free(lines);

#else
    int lineCount;

    char** lines = fileRead(argv[1], &lineCount);

    // Print the lines
    for (int i = 0; i < lineCount; i++) {
        printf("Line %d: %s\n", i + 1, lines[i]);
        free(lines[i]); // Free memory for each line
    }

    // Free memory for the array of char pointers
    free(lines);
#endif
    return 0;
}