#include <iostream>
using namespace std;

#include "Logger.h"

int main()
{
    wheel::Logger::GetInstance().open("./test.log");
    wheel::Logger::GetInstance().Log(wheel::Logger::DEBUG, __FILE__, __LINE__, "Hello world");
    return 0;
}