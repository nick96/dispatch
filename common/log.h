#ifndef DISPATCH_LOG_H
#define DISPATCH_LOG_H

#ifdef DISABLE_LOG
#define LOG(...) // Do nothing
#else
#define LOG(...) fprintf(stderr, ...)
#endif

#endif
