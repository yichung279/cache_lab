#ifndef _CSIM_H
#define _CSIM_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
  bool valid;                // valid bit 
  unsigned long long tag;     // tag size = 64-(s+b)
  char *block;                // array of bytes
} Cacherow;

typedef struct {
    Cacherow *cacherow;      // array of rows
} Set;   

typedef struct {
    Set *sets;   // array of Set
}Cache;

Cache *cache_create(int s, int E, int b);
#endif
