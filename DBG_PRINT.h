#ifndef DBG_PRINT_H__
#define DBG_PRINT_H_

// this is basically task number 4.

#include<stdio.h>

#define DBG_PRINT(debugLevel, format, ...) {\
    printf("[%d][%s][%d] ",debugLevel,__FILE__,__LINE__);\
    printf(format, __VA_ARGS__);\
}

#define clearScreen() printf("\033[H\033[J") 

#endif
