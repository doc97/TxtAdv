/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "Expression.h"
#include <functional>

namespace txt
{

/* Class: LambdaExpression
 * Implements expression handling via lambda expressions.
 *
 * Extends:
 *
 *    <Expression>
 */
class LambdaExpression : public Expression
{
public:
    /* Constructor: LambdaExpression
     *
     * Parameters:
     *
     *    func - The lambda expression used to to implement expression handling functionality
     */
    LambdaExpression(const std::function<std::string()>& func);
    ~LambdaExpression();
private:
    std::string ExecImpl() const override;
    std::function<std::string()> m_func;
};

} // namespace txt
