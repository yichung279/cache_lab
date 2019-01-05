#ifndef _CSIM_H
#define _CSIM_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  bool valid;                // valid bit 
  unsigned long tag;     // tag size = t
  int access_time;

} Cacheline;

typedef struct {
    Cacheline **table;   // array of caccheline ptr
    int s, E, b, t;
    long S, B;
    int time;

}Cache;

Cache *cache_create(int s, int E, int b);
void cache_visit(Cache *cache, unsigned long addr);
#endif
