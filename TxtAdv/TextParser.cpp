/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "TextParser.h"

namespace txt
{

std::string TextParser::ParseText(const std::string& text)
{
    return ParseTextImpl(text);
}

} // namespace txt
