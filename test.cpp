#include "date.h"
#include <iostream>

int
main()
{
    using namespace std::chrono;
    std::cout << date::format("%F %T\n", time_point_cast<milliseconds>(system_clock::now()));
}