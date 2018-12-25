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
     *
     * Parameters:
     *
     *    string - The string to write
     */
    inline void Write(const std::string& string)
    {
        WriteImpl(string);
    }

    /* Function: WriteLine
     *
     * Parameters:
     *
     *    string - The string to write
     */
    inline void WriteLine(const std::string& string)
    {
        WriteLineImpl(string);
    }

    /* Function: GetLine
     *
     * Parameters:
     *
     *    string - The result is stored in this variable
     */
    inline void GetLine(std::string& string)
    {
        GetLineImpl(string);
    }

private:
    virtual void WriteImpl(const std::string& string) = 0;
    virtual void WriteLineImpl(const std::string& string) = 0;
    virtual void GetLineImpl(std::string& string) = 0;
};

} // namespace txt
