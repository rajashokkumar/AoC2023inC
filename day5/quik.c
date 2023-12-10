#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *str = argv[1];

    printf("%d\n", atoi(str));
    printf("%ld\n", atol(str));
    printf("%lld\n", atoll(str));
    printf("%lld\n", atoi(str));
    
    
}