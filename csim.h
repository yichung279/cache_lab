#ifndef _CSIM_H
#define _CSIM_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  bool valid;                // valid bit 
  unsigned long long tag;     // tag size = 64-(s+b)
  char *block;                // array of bytes
} Cacheline;

typedef struct {
    Cacheline **table;   // array of caccheline ptr
}Cache;

Cache *cache_create(int s, int E, int b);
#endif
