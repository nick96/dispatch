#ifndef DISPATCH_WINDOWS_SHIM_H
#define DISPATCH_WINDOWS_SHIM_H


#if (defined(WIN32) || defined(_WIN32))
#include <windows.h>
#include <direct.h>

#define mkdir _mkdir
#define access(parent, type) (searchpath(parent) ? 0 : -1)

#endif

#endif
