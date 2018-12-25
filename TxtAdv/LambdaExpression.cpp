#include "LambdaExpression.h"

namespace txt
{

LambdaExpression::LambdaExpression(const std::function<std::string()>& func)
    : m_func(func)
{
}


LambdaExpression::~LambdaExpression()
{
}

std::string LambdaExpression::ExecImpl() const
{
    return m_func();
}

} // namespace txt

