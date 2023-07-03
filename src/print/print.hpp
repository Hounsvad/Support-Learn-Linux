#ifndef PRINT_StrangeWhiskers
#define PRINT_StrangeWhiskers
#include <iostream>
#include <string>
namespace strange_whiskers::print
{
    void Print(std::string& message, bool flush = true);
    void Println(std::string& message, bool flush = true);
    void Print(std::string message, bool flush = true);
    void Println(std::string message, bool flush = true);
    void Flush();
}

#endif