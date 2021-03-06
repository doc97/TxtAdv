/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "ConsoleIO.h"
#include <iostream>

namespace txt
{

ConsoleIO::ConsoleIO()
{
}

ConsoleIO::~ConsoleIO()
{
}

void ConsoleIO::WriteImpl(const std::string& string)
{
    std::cout << string;
}

void ConsoleIO::WriteLineImpl(const std::string& string)
{
    std::cout << string << std::endl;
}

void ConsoleIO::GetLineImpl(std::string& string)
{
    std::getline(std::cin, string);
}

} // namespace txt
