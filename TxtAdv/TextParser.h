/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>

namespace txt
{

/* Class: TextParser
 * Parses a piece of text markup.
 */
class TextParser
{
public:
    virtual ~TextParser() {}

    /* Function: Parse
     * Parses a string of text and returns the result.
     *
     * Parameters:
     *
     *    text - The text to change
     */
    std::string Parse(const std::string& text);
private:
    virtual std::string ParseText(const std::string& text) = 0;
};

} // namespace txt
