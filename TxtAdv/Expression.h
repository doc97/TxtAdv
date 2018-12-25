/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>

namespace txt
{

/* Interface: Expression
 * Used to implement text parsing expressions.
 */
class Expression
{
public:
    virtual ~Expression() {}

    /* Function: Exec */
    inline std::string Exec() const
    {
        return ExecImpl();
    }
private:
    virtual std::string ExecImpl() const = 0;
};

} // namespace txt
