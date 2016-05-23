/**
 *  @file debug.hpp
 *  @brief A debug utility.
 *  @version v1.0
 *
 *  @author Created by Bonzo on 2016/3/20.
 *  @author Copyright © 2016 Bonzo. All rights reserved.
 *
 **/

#ifndef debug_hpp
#define debug_hpp

#include <iostream>
/**
 * namespace bonzo.
 * @brief Customized namespace for this library.
 **/
namespace bonzo{
using std::cout;
using std::endl;

/**
 *  @var _DEBUG_ON
 *  @brief global switch to turn on / off debug utility.
 **/
bool _DEBUG_ON = false;

/**
 *  @fn print_dbg_msg(bool dbg_on = false, const char* dbg_msg = "")
 *  @brief print debug message.
 *
 *  @param dbg_on switch to turn on/ off print_dbg_msg.
 *  @param dbg_msg  user specified debug message.
 **/
void print_dbg_msg(bool dbg_on = false, const char* dbg_msg = "")
{
    if(dbg_on)
        cout << dbg_msg << endl;
    return;
}

} // end of namespace bonzo

#endif /* debug_hpp */
