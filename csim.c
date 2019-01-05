#include "cachelab.h"
#include "csim.h"

#include <stdlib.h>

Cache cache_create(int s, int E, int b){
    Cache cache;
    
    long S = 2 << s;
    long B = 2 << b;

    cache.sets = (Set *)calloc(S, sizeof(Set));
    
    for(long i = 0; i < S; i++){
        cache.sets[i].cacherow = (Cacherow *)calloc(E, sizeof(Cacherow));
        for(long j = 0; j < B; i++){
            cache.sets[i].cacherow[j].block = (char *)calloc(B, sizeof(char));
            cache.sets[i].cacherow[j].valid = 0;
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
