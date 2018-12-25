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

private:
    void WriteImpl(const std::string& string) override;
    void WriteLineImpl(const std::string& string) override;
    void GetLineImpl(std::string& string) override;
};

} // namespace txt
