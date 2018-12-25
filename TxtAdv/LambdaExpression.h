/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "Expression.h"
#include <functional>

namespace txt
{

class LambdaExpression : public Expression
{
public:
    LambdaExpression(const std::function<std::string()>& func);
    ~LambdaExpression();
private:
    std::string ExecImpl() const override;
    std::function<std::string()> m_func;
};

} // namespace txt
