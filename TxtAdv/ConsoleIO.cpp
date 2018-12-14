#include "ConsoleIO.h"
#include <iostream>

ConsoleIO::ConsoleIO()
{
}

ConsoleIO::~ConsoleIO()
{
}

void ConsoleIO::Write(const std::string& string)
{
    std::cout << string;
}

void ConsoleIO::WriteLine(const std::string& string)
{
    std::cout << string << std::endl;
}

void ConsoleIO::GetLine(std::string& string)
{
    std::getline(std::cin, string);
}
