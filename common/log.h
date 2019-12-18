#ifndef DISPATCH_LOG_H
#define DISPATCH_LOG_H

#ifdef DISABLE_LOG
#define LOG(...) // Do nothing
#else
#include <stdio.h>
#define LOG(...) fprintf(stderr, __VA_ARGS__)
#endif

#endif
