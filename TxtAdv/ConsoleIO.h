/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "IO.h"

namespace txt
{

class ConsoleIO : public IO
{
public:
    ConsoleIO();
    ~ConsoleIO();

    void Write(const std::string& string) override;
    void WriteLine(const std::string& string) override;
    void GetLine(std::string& string) override;
};

} // namespace txt
