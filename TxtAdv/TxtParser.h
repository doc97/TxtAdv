/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "TextParser.h"
#include "GameState.h"
#include <vector>

namespace txt
{

/* Class: TxtParser
 * Default text parser for TxtAdv.
 *
 * Extends:
 *
 *    <TextParser>
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
    TxtParser(const GameState& state);
    ~TxtParser();

private:
    GameState m_state;
    std::string ParseText(const std::string& text) override;
    std::vector<std::string> ParseVariables(const std::string& text) const;
    std::string ReplaceVariables(const std::string& text, const std::vector<std::string>& vars) const;
    std::string GetVariableString(const std::string& type, const std::string& name, bool throwError = false) const;
    std::string FloatToString(float value, size_t precision) const;
};

} // namespace txt
