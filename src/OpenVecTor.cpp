#include <iostream>

#include <OpenVecTor.hpp>

#define QUOTE(str) #str
#define EXPAND_AND_QUOTE(str) QUOTE(str)


const char* openvector_version()
{
    return EXPAND_AND_QUOTE(PROJECT_VERSION);
}
