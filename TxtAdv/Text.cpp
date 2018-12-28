/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "Text.h"

namespace txt
{

Text::Text(const std::string& text)
{
    m_str = text;
}


Text::~Text()
{
}

std::string Text::Str() const
{
    return m_str;
}

} // namespace txt
