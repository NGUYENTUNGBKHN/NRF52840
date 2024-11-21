#include <stdio.h>
#include "log.h"

static void jump_app();
static void jump_boot();

int main()
{

    logInit();
    logPrintf("OS : Bootloader 1 \n");

    if (1)
    {
        jump_app();
    }
    else
    {
        jump_boot();
    }

    while (1)
    {
        /* code */
    }
    
    return 0;
}

static void jump_app()
{
    
}

static void jump_boot()
{

}
