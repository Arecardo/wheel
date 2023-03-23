#include <iostream>
using namespace std;

#include "../../src/log/Logger.h"

int main()
{
    SET_LOG_LEVEL(wheel::Level::ERROR);
    while (true)
    { 
        LOG_INFO("Hello World");
        LOG_ERROR("This is error");
    }
    return 0;
}