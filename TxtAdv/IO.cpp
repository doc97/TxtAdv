/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "IO.h"

namespace txt
{
void IO::Write(const std::string& string)
{
    WriteImpl(string);
}

void IO::WriteLine(const std::string& string)
{
    WriteLineImpl(string);
}

void IO::GetLine(std::string& string)
{
    GetLineImpl(string);
}

} // namespace txt
