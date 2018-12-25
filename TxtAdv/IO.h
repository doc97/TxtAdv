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
    void Write(const std::string& string);

    /* Function: WriteLine
     * Implement line-ended output here.
     *
     * Parameters:
     *
     *    string - The string to write
     */
    void WriteLine(const std::string& string);

    /* Function: GetLine
     * Implement line input here.
     *
     * Parameters:
     *
     *    string - The result is stored in this variable
     */
    void GetLine(std::string& string);

private:
    virtual void WriteImpl(const std::string& string) = 0;
    virtual void WriteLineImpl(const std::string& string) = 0;
    virtual void GetLineImpl(std::string& string) = 0;
};

} // namespace txt
