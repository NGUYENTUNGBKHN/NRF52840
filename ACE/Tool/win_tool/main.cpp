/******************************************************************************/
/*! @addtogroup Group2
    @file       main.cpp
    @brief      
    @date       2025/07/11
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include <iostream>
#include "inc.h"
#include "parseArg/parseArgs.h"
#include "operation/operation.h"
#include <string>

void showHelp()
{

}

int main(int num_arg, char *arg[])
{
    // parseArgs test ;
    operation test;

    for (int i = 1; i < num_arg; i++)
    {
        std::string strArgs = arg[i];

        if (strArgs == "-f" || strArgs == "--flash")
        {
            if (arg[i + 1] != "")
            {
                test.flash(arg[i + 1]);
                break;
            }
            
        }
        else if (strArgs == "-e" || strArgs == "--erase")
        {
            TRACE_LOG("Erase\n");
        }
        else if (strArgs == "-h" || strArgs == "--help")
        {
            std::cout << "Usage: " << arg[0] << " [options]\n"
                      << "Options:\n"
                      << "  -f, --flash <file>     Flash input file\n"
                      << "  -e, --erase            Erase flash CPU\n"
                      << "  -h, --help             Show this help message\n";
            break;
        }
        else
        {
            std::cout << "Usage: " << arg[0] << " [options]\n"
                      << "Options:\n"
                      << "  -f, --flash <file>     Flash input file\n"
                      << "  -e, --erase            Erase flash CPU\n"
                      << "  -h, --help             Show this help message\n";
            break;
        }
    }

    // while (1)
    // {
    //     /* code */
    // }
    
    return 0;
}
