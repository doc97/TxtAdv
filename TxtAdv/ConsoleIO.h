/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "IO.h"

namespace txt
{

/* Class: ConsoleIO
 * Handles input from stdin and output to stdout.
 *
 * Extends:
 *
 *    <IO>
 */
class ConsoleIO : public IO
{
public:
    ConsoleIO();
    ~ConsoleIO();

    /* Function: Write
     * Writes the string to stdout.
     *
     * Parameters:
     *
     *    string - The string to write
     */
    void Write(const std::string& string) override;

    /* Function: WriteLine
     * Writes the string and a newline to stdout.
     *
     * Parameters:
     *
     *    string - The string to write
     */
    void WriteLine(const std::string& string) override;

    /* Function: GetLine
     * Reads a line from stdin, will block until a line is given.
     *
     * Parameters:
     *
     *    string - The result is stored in this variable
     */
    void GetLine(std::string& string) override;
};

} // namespace txt
