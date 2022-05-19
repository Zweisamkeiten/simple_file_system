#ifndef debug_h
#define debug_h

#include <assert.h>
#include <stdbool.h>

#define TODO() assert(0)

#define Debug(...) if (debug == true) \
                             printf(__VA_ARGS__)

extern bool debug;

#endif
