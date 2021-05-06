/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "TextParser.h"
#include "GameState.h"
#include "Expression.h"
#include <functional>
#include <vector>

namespace txt
{

/* Class: TxtParser
 * Default text parser for TxtAdv.
 *
 * The parser replaces the int, float, and string variables with their value from a <GameState>.
 * Additionally, one can use 'expression variables' to refer to stored lambda expressions. The
 * variables should be enclosed in {} to signal a variable and the name should also be prefixed
 * with one of four available variable type identifier.
 *
 * A variable type verifier is one of the following:
 *
 * i_: Integer
 * f_: Float
 * s_: String
 * x_: Expression
 *
 * Extends:
 *
 *    <TextParser>
 *
 * Example:
 *
 * To refer to a float variable named 'score', user '{f_score}'.
 */
class TxtParser : public TextParser
{
public:
    /* Constructor: TxtParser
     *
     * Parameters:
     *
     *    state - The state from where to retrieve variables
     */
    TxtParser(GameState* state);
    ~TxtParser();

    /* Function: AddExpression
     * Saves a lambda expression with a name.
     *
     * Parameters:
     *
     *    name - The name used to refer to the expression
     *    expr - The expression
     */
    void AddExpression(const std::string& name, std::unique_ptr<Expression> expr);
private:
    static const size_t DEPTH_MAX = 8;
    GameState* m_state;
    std::unordered_map<std::string, std::unique_ptr<Expression>> m_expressions;

    std::string ParseTextImpl(const std::string& text) override;
    std::vector<std::string> ParseVariables(const std::string& text) const;
    std::string ReplaceVariables(const std::string& text, const std::vector<std::string>& vars) const;
    std::string GetVariableString(const std::string& type, const std::string& name, bool throwError = false) const;
    std::string FloatToString(float value, size_t precision) const;
    std::string ExprToString(const std::string& name) const;
};

} // namespace txt
