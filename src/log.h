#pragma once
#include <iostream>
#include <stdlib.h>
#define DebugMode 1
#if DebugMode
#define LOG_DEBUG(string) std::cout<<string<<std::endl
#else
#define LOG_DEBUG(string)
#endif

#define LOG_COMPILE_ERROR(string) std::cout<<"COMPILE ERROR: "<<string<<std::endl
#define LOG_ERROR(string) std::cout<<"ERROR: "<<string<<std::endl
#define LOG(string) std::cout<<"> "<<string<<std::endl
#define STOP() exit(1)
