#include "cachelab.h"
#include "csim.h"

#include <stdlib.h>

Cache *cache_create(int s, int E, int b){
    Cache *cache = (Cache *)malloc(sizeof(Cache));
    
    long S = 2 << s;
    long B = 2 << b;

    cache->table = (Cacheline **)calloc(S, sizeof(Cacheline *));
    
    for(long i = 0; i < S; i++){
        cache->table[i] = (Cacheline *)calloc(E, sizeof(Cacheline));
        for(long j = 0; j < B; j++){
            cache->table[i][j].block = (char *)calloc(B, sizeof(char));
            cache->table[i][j].valid = 0;
            /// todo: add tag size
        }
    }

    return cache;
}

int main()
{
    printSummary(0, 0, 0);
    return 0;
}
