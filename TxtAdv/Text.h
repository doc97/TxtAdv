/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>

namespace txt
{

class Text
{
public:
    Text(const std::string& text);
    ~Text();

    std::string Str() const;

private:
    std::string m_str;
};

} // namespace txt
