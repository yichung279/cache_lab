#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
int s,E,b;
char *file_name;
int hits=0, misses=0, evicts=0;
unsigned int atoui(char *s);
struct cache{


};

int main(int argc, char * argv[])
{
    /* Parse user inputs */
    char c ;
    while((c=getopt(argc, argv, "hvs:E:b:t:")) != -1)
    {
        switch(c)
        {
            case 'h':
                break;
            case 'v':
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                file_name = optarg;
                break;
        }
    }
    char word[50];
    FILE *fp = fopen(file_name, "r");
    while (fgets(word, 50, fp)){
        char *instruction = strtok(word, " ");
        char *addr = strtok(NULL, ",");
        char *m_size = strtok(NULL, ",");
        unsigned int addr_hex = (unsigned int)strtol(addr, NULL, 16); 
        printf("%s %s %s",instruction, addr, m_size);
        printf("%x\n", val);
    } 

    /* Creat cache table */
    int S = 1<<s;
    unsigned int **set =  malloc(S*sizeof(unsigned int *));
    for (int i = 0; i < S; i++) {
        set[i] = malloc(E*sizeof(unsigned int));
    }


    /* Print results */
    printSummary(0, 0, 0);
    return 0;
}

