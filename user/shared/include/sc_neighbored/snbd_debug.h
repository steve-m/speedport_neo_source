#ifndef _SNBD_DEBUG_H_
#define _SNBD_DEBUG_H_

#include <stdio.h>
#include <stdarg.h>

#define SNBD_DEBUG(...) do {\
    printf("%s: ", __FUNCTION__);\
    printf("%d: ", __LINE__);\
    printf(__VA_ARGS__);\
} while(0);
#define SNBD_WARN(...) do {\
    printf("%s: ", __FUNCTION__);\
    printf("%d: ", __LINE__);\
    printf(__VA_ARGS__);\
} while(0);
#define SNBD_ERROR(...) do {\
    printf("%s: ", __FUNCTION__);\
    printf("%d: ", __LINE__);\
    printf(__VA_ARGS__);\
} while(0);

#endif /* _SNBD_DEBUG_H_ */
