/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <unordered_map>
#include "LineReader.h"

namespace txt
{

/* Struct: CtrlContent
 * Represents <LuaResponseHandler> data about one <StoryPoint>.
 */
struct CtrlContent
{
    std::string storypoint;
    std::string script;
    std::string matcher_func;
    std::string action_func;
};

/* Struct: CtrlContentInfo
 * The result of <CtrlContentReader>.
 */
struct CtrlContentInfo
{
    std::unordered_map<std::string, std::vector<CtrlContent>> ctrl_content;
};

/* Class: CtrlContentReader
 * Reads and parses control content.
 */
class CtrlContentReader
{
public:
    CtrlContentReader();
    ~CtrlContentReader();

    /* Function: Read
     *
     * Parameters:
     *
     *    filename - Path to the file to read
     *
     * Returns:
     *
     *    The data in the form of a <CtrlContentInfo> object
     *
     * Throws:
     *
     *    std::runtime_error if there is an error such as file format error or I/O error
     */
    CtrlContentInfo Read(const std::string& filename);

    /* Function: Read
     *
     * Parameters:
     *
     *    filename - Path to the file to read
     *
     * Returns:
     *
     *    The data in the form of a <CtrlContentInfo> object
     *
     * Throws:
     *
     *    std::runtime_error if there is an error such as file format error or I/O error
     */
    CtrlContentInfo Read(std::istream& stream);
private:
    LineReader m_reader;
};

} // namespace txt
