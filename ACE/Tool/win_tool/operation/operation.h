/******************************************************************************/
/*! @addtogroup Group2
    @file       operation.h
    @brief      
    @date       2025/07/14
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#pragma once

#include <string>

class operation
{
private:
    /* data */
public:
    operation(/* args */);
    ~operation();
    int flash(std::string hex_path);
};
