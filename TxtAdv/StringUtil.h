/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once
#include <algorithm>
#include <cctype>
#include <locale>

namespace txt
{

/* Function: ltrim
 * Trims whitespace inline from the beginning.
 *
 * Parameters:
 *
 *    s - The string to trim whitespace from
 */
static inline void ltrim(std::string& s)
{
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
}

/* Function: rtrim
 * Trims whitespace inline from the end.
 *
 * Parameters:
 *
 *    s - The string to trim whitespace from
 */
static inline void rtrim(std::string& s)
{
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
}

/* Function: trim
 * Trims whitespace inline from both the beginning and the end.
 *
 * Parameters:
 *
 *    s - The string to trim whitespace from
 */
static inline void trim(std::string& s)
{
    ltrim(s);
    rtrim(s);
}

/* Function: ltrim_copy
 * Trims whitespace from the beginning and returns the result.
 *
 * Parameters:
 *
 *    s - The string to trim whitespace from (pass by value)
 *
 * Returns:
 *
 *    The modified string
 */
static inline std::string ltrim_copy(std::string s)
{
    ltrim(s);
    return s;
}

/* Function: rtrim_copy
 * Trims whitespace from the end and returns the result.
 *
 * Parameters:
 *
 *    s - The string to trim whitespace from (pass by value)
 *
 * Returns:
 *
 *    The modified string
 */
static inline std::string rtrim_copy(std::string s)
{
    rtrim(s);
    return s;
}

/* Function: trim_copy
 * Trims whitespace from both the beginning and the end and returns the result.
 *
 * Parameters:
 *
 *    s - The string to trim whitespace from (pass by value)
 *
 * Returns:
 *
 *    The modified string
 */
static inline std::string trim_copy(std::string s)
{
    trim(s);
    return s;
}

static inline std::vector<std::string> split(const std::string& s, char delim)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream stream(s);
    while (std::getline(stream, token, delim))
        tokens.push_back(token);
    return tokens;
}

} // namespace txt
