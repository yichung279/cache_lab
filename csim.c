#include "cachelab.h"
#include "csim.h"

Cache cache_create(int s, int E, int b){
    Cache cache = malloc(sizeof(Cache));
    
    long S = 2 << s;
    long B = 2 << b;

    cache->sets = (Set *)calloc(S, sizeof(Set));
    
    for(long i = 0; i < S; i++){
        cache->sets[i] = (Cacherow *)calloc(E, sizeof(Cacherow));
        cache->sets[i]->block = (char *)calloc(B, sizeof(char));
    }

    return cache;
}

int main()
{
    printSummary(0, 0, 0);
    return 0;
}
