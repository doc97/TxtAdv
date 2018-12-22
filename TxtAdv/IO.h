/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>

namespace txt
{

    class IO
    {
    public:
        virtual ~IO() {}
        virtual void Write(const std::string& string) = 0;
        virtual void WriteLine(const std::string& string) = 0;
        virtual void GetLine(std::string& string) = 0;
    };

} // namespace txt
