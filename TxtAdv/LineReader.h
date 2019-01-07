/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <sstream>
#include <string>

namespace txt
{

/* Class: LineReader
 * Reads line from a stream while ignoring comments.
 *
 * One line comments start with //, multiline comments are denoted by \/* *\/.
 */
class LineReader
{
public:
    LineReader();
    ~LineReader();
    
    /* Function: NextLine
     * Reads the next non-commented line.
     *
     * Parameters:
     *
     *    stream - The stream to read from
     *    line - The read line is stored here
     *
     * Returns:
     *
     *    true if there is more to read
     */
    bool NextLine(std::istream& stream, std::string& line);
protected:
    bool m_isComment = false;

    bool HandleMultilineComment(std::string& line);
    bool HandleSinglelineComment(std::string& line);
};

} // namespace txt
