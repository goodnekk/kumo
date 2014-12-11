#pragma once
#include <iostream>
#define DebugMode 1
#if DebugMode
#define LOG_DEBUG(string) std::cout<<string<<std::endl
#else
#define LOG_DEBUG(string)
#endif

#define LOG_ERROR(string) std::cout<<"ERROR: "<<string<<std::endl
#define LOG(string) std::cout<<"> "<<string<<std::endl
