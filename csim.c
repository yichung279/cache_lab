#include "cachelab.h"
#include "csim.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int g_hit = 0;
int g_miss = 0;
int g_evicts = 0;
int g_v = 0;

Cache *cache_create(int s, int E, int b)
{
    Cache *cache = (Cache *)malloc(sizeof(Cache));

    cache->s = s;
    cache->E = E;
    cache->b = b;
    cache->t = 64 - s - b;   // tag_size, not tracefile

    cache->S = 2 << s;
    cache->B = 2 << b;

    cache->table = (Cacheline **)calloc(cache->S, sizeof(Cacheline *));

    for(long i = 0; i < cache->S; i++){
        cache->table[i] = (Cacheline *)calloc(E, sizeof(Cacheline));
        for(long j = 0; j < E; j++){
            cache->table[i][j].valid = 0;
            cache->table[i][j].access_time = -1;
        }
    }

    return cache;
}

void cache_visit(Cache *cache, unsigned long addr)
{
    cache->time++;
    unsigned long tag;
    long index;

    index = (addr >> cache->b) & ~(~0 << cache->s);
    tag = (addr >> cache->s) >> cache->b;

    // hit
    for (int i = 0; i < cache->E; i++){
        Cacheline *line = &(cache->table[index][i]);

        if(line->tag == tag && line->valid){
            g_hit++;
            line->access_time = cache->time;
            return;
        }
    }

    //miss
    g_miss++;

    // replace the oldest cacheline
    Cacheline *oldline;
    int oldtime = 2147483647;
    for (int i = 0; i < cache->E; i++){
        Cacheline *line = &(cache->table[index][i]);

        if(line->access_time < oldtime){
            oldtime = line->access_time;
            oldline = line;
        }
    }

    if(oldline->access_time != -1)
    {
        g_evicts++;
    }

    oldline->tag = tag;
    oldline->valid = 1;
    oldline->access_time = cache->time;
    return;
}

int main(int argc, char* argv[])
{
    // argv 
    int s, E, b;
    char* t;

    int opt;
    while ((opt = getopt(argc, argv, "s:E:b:t:v")) != -1)
    {
        switch(opt)
        {
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
                t = optarg;
                break;
            case 'v':

                break;

            default:
                printf("Please Enter Arguments.\n");
                return -1;
        }
    }

    if (s == 0 || E == 0 || b == 0 || t == NULL)
    {
        printf("Arguments Error\n");
        return -1;
    }

    FILE* trace = fopen(t, "r");
    if(trace == NULL)
    {
        printf("Trace file is empty\n");
        return -1;
    }

    Cache* cache = cache_create(s,E,b);

    char instr;
    char addr;
    int size; 

    while(fscanf(trace, " %c %s,%d", &instr, &addr, &size) == 2)
    {
        unsigned long addr_hex = (unsigned long)strtol(&addr, NULL, 16); 
        switch(instr)
        {
            case 'I':
                break;

            case 'M':
                cache_visit(cache, addr_hex);  // Load
                g_hit++;                       // Store
                break;

            case 'S':
                cache_visit(cache, addr_hex);
                break;

            case 'L':
                cache_visit(cache, addr_hex);
                break;

            default:
                printf("Trace file format is error.\n");
                return -1;
        }
    }

    printSummary(g_hit, g_miss, g_evicts);
    return 0;
}
