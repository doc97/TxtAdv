/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>

namespace txt
{

/* Interface: IO
 * Used to implement I/O operations.
 */
class IO
{
public:
    virtual ~IO() {}

    /* Function: Write
     * Implement output here.
     *
     * Parameters:
     *
     *    string - The string to write
     */
    virtual void Write(const std::string& string) = 0;

    /* Function: WriteLine
     * Implement line-ended output here.
     *
     * Parameters:
     *
     *    string - The string to write
     */
    virtual void WriteLine(const std::string& string) = 0;

    /* Function: GetLine
     * Implement line input here.
     *
     * Parameters:
     *
     *    string - The result is stored in this variable
     */
    virtual void GetLine(std::string& string) = 0;
};

} // namespace txt
