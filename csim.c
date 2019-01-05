#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
int s,E,b,count; 
char *file_name; 
int hits=0, misses=0, evictions=0;
int tag, set, offset;

/* Define cache structure  */
typedef struct cache_data{
    int valid_bit;
    int tag;
    int time_be_used;
} cache_data;
cache_data **cache_table;
bool ifprint = false;
void parse(int s, int b, int var);
void check_cache();
int main(int argc, char * argv[])
{
    /* Parse user inputs */
    char c ;
    while((c=getopt(argc, argv, "hvs:E:b:t:")) != -1){
        switch(c){
            case 'h':
                break;
            case 'v':
                ifprint = true;
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

    /* Creat cache table and initialization */
    int S = 1<<s;
    cache_table =  malloc(S*sizeof(cache_data *));
    for (int i = 0; i < S; i++) {
        cache_table[i] = malloc(E*sizeof(cache_data));
    }
    for (int i = 0; i < S; i++) {
        for (int j = 0; j < E; j++) {
            cache_table[i][j].valid_bit = 0;
            cache_table[i][j].tag = 0;
            cache_table[i][j].time_be_used = 0;
        }
    }


    char word[50];
    FILE *fp = fopen(file_name, "r");
    while (fgets(word, 50, fp)){
        count++;
        if(ifprint)
            printf("%s ", strtok(word, "\n"));
        char *instruction = strtok(word, " "); 
        char *addr = strtok(NULL, ",");
        unsigned int addr_hex = (unsigned int)strtol(addr, NULL, 16); 
        parse(s,b,addr_hex);
        if(ifprint)
            printf(" %d %d %d ", tag, set, offset);

        switch(*instruction){
            case 'I':
                break;
            case 'L':
                check_cache();
                break;
            case 'M':
                check_cache();
                check_cache();
                break;
            case 'S':
                check_cache();
                break;
        }
        
        if(ifprint)
            printf("\n");
    }



    /* Print results */
    printSummary(hits, misses, evictions);
    return 0;
}

void parse(int s, int b, int var){
    unsigned int mask_offset = (1 << b) - 1;
    unsigned int mask_set = (1 << (s+b)) - ( 1 << b);
    unsigned int mask_tag = ~0 - (mask_offset + mask_set);
    /* printf("%x %x %x\n", mask_tag, mask_set, mask_offset);   */
    tag = (var & mask_tag) >> (s+b);
    set = (var & mask_set) >> (b);
    offset = var & mask_offset;
}

/* Check if data hit the cache */
void check_cache(){

    for (int i = 0; i < E; i++) {
        if(cache_table[set][i].valid_bit == 1 && cache_table[set][i].tag == tag){
                cache_table[set][i].time_be_used = count;
                hits += 1;
                if(ifprint)
                    printf("hit ");
                return;
        }
    }

    misses += 1;
    if(ifprint)
        printf("miss ");
    int n_lru = 0;
    for (int i = 0; i < E; i++) {
        if(cache_table[set][i].valid_bit == 0){
            cache_table[set][i].valid_bit = 1;
            cache_table[set][i].tag = tag;
            cache_table[set][i].time_be_used = count;
            return;
        }
        else{
            if(cache_table[set][n_lru].time_be_used > cache_table[set][i].time_be_used)
                n_lru = i;
        }
    }
    
    evictions += 1;
    if(ifprint)
        printf("eviction ");
    cache_table[set][n_lru].valid_bit = 1;
    cache_table[set][n_lru].tag = tag;
    cache_table[set][n_lru].time_be_used = count;
}

