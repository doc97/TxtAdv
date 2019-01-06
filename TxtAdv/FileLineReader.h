/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <fstream>
#include <string>

namespace txt
{

/* Class: FileLineReader
 * Reads line from a file while ignoring comments.
 *
 * One line comments start with //, multiline comments are denoted by \/* *\/.
 */
class FileLineReader
{
public:
    FileLineReader();
    ~FileLineReader();
    
    /* Function: NextLine
     * Reads the next non-commented line.
     *
     * Parameters:
     *
     *    file - The opened file stream to read from, if the stream is closed this function just returns false
     *    line - The read line is stored here
     *
     * Returns:
     *
     *    true if there is more to read
     */
    bool NextLine(std::ifstream& file, std::string& line);
protected:
    bool m_isComment = false;

    bool HandleMultilineComment(std::string& line);
    bool HandleSinglelineComment(std::string& line);
};

} // namespace txt
