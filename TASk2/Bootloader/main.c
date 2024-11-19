#include <stdio.h>
#include "log.h"


int main()
{

    logInit();
    logPrintf("OS : Bootloader 1 \n");

    while (1)
    {
        /* code */
    }
    
    return 0;
}


