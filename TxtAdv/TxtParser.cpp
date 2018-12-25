/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "TxtParser.h"
#include <regex>
#include <sstream>
#include <iomanip> // std::setprecision

namespace txt
{

TxtParser::TxtParser(const GameState& state)
    : m_state(state)
{
}

TxtParser::~TxtParser()
{
}


void TxtParser::AddExpression(const std::string& name, const std::function<std::string()>& expr)
{
    m_expressions[name] = expr;
}

std::string TxtParser::ParseTextImpl(const std::string& text)
{
    std::string prevResult;
    std::string result = text;
    size_t depth = 0;
    while (result != prevResult && depth++ < TxtParser::DEPTH_MAX)
    {
        std::vector<std::string> vars = ParseVariables(result);
        prevResult = result;
        result = ReplaceVariables(result, vars);
    }
    return result;
}

std::vector<std::string> TxtParser::ParseVariables(const std::string& text) const
{
    std::regex rgx("\\{([fisx]_\\w+)\\}");
    std::sregex_iterator iter(text.begin(), text.end(), rgx);
    std::sregex_iterator end;
    std::vector<std::string> captures;

    for (; iter != end; ++iter)
    {
        for (size_t i = 1; i < iter->size(); ++i)
            captures.push_back((*iter)[i]);
    }

    return captures;
}

std::string TxtParser::ReplaceVariables(const std::string& text, const std::vector<std::string>& vars) const
{
    std::string result = text;
    for (const std::string& var : vars)
    {
        std::string type = var.substr(0, 2);
        std::string name = var.substr(2, std::string::npos);
        std::string value = GetVariableString(type, name);
        std::regex rgx("\\{" + var + "\\}");
        result = std::regex_replace(result, rgx, value);
    }
    return result;
}

std::string TxtParser::GetVariableString(const std::string& type, const std::string& name, bool throwError) const
{
    try
    {
        if (type == "i_")
            return std::to_string(m_state.GetInt(name));
        else if (type == "f_")
            return FloatToString(m_state.GetFloat(name), 2);
        else if (type == "s_")
            return m_state.GetString(name);
        else if (type == "x_")
            return ExprToString(name);
        else
            throw std::invalid_argument("type must either be i_, f_, s_ or x_");
    }
    catch (std::invalid_argument)
    {
        if (throwError)
            throw;
        else
            return "<unknown>";
    }
}

std::string TxtParser::FloatToString(float value, size_t precision) const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(precision) << value;
    return ss.str();
}

std::string TxtParser::ExprToString(const std::string& name) const
{
    if (m_expressions.find(name) == m_expressions.end())
        throw new std::invalid_argument("No expression found with the name: " + name);
    return m_expressions.at(name)();
}

} // namespace txt
