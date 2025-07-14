/******************************************************************************/
/*! @addtogroup Group2
    @file       operation.c
    @brief      
    @date       2025/07/14
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "inc.h"
#include <string>
#include <iostream>
#include <fstream>  // For file stream operations
#include "operation.h"
#include <cstdio>   // For std::remove

operation::operation()
{

}

operation::~operation()
{

}

int operation::flash(std::string hex_path)
{
    int res_sys = 0;
    std::ofstream outputFile("flash.jlink");

    if (!outputFile.is_open())
    {
        return -1;
    }

    outputFile << "h" << std::endl;
    outputFile << "loadfile " << hex_path << std::endl;
    outputFile << "r" << std::endl;
    outputFile << "g" << std::endl;
    outputFile << "exit" << std::endl;

    outputFile.close();

    std::string cmd;

    cmd = "JLink.exe ";
    cmd += "-device nRF52832_xxAA ";
    cmd += "-if SWD ";
    cmd += "-speed 4000 ";
    cmd += "-CommanderScript flash.jlink";
    cmd += ">flash.log 2>&1";
    const char* cmd_script = cmd.c_str();
    res_sys = system(cmd_script);
    if (res_sys != 0)
    {
        std::cout << "Flash failed : " << res_sys << std::endl;
        return -1;
    }
    std::cout << "Flash OK" << std::endl;

    std::remove("flash.jlink");
    
    return 1;
}
