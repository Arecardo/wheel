#include <iostream>
using namespace std;

#include "Logger.h"

int main()
{
    wheel::Logger my_logger(wheel::Level::INFO, "test.log", 1000000);
    while (true)
    { 
        my_logger.Log(wheel::Level::INFO, __FILE__, __LINE__, "This is a message");
    }
    return 0;
}