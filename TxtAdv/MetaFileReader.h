/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <unordered_map>
#include "LineReader.h"

namespace txt
{

/* Struct: Metadata
 * Represents <LuaResponseHandler> data about one <StoryPoint>.
 */
struct Metadata
{
    std::string storypoint;
    std::string script;
    std::string matcher_func;
    std::string action_func;
};

/* Struct: MetaInfo
 * The result of <MetaFileReader>.
 */
struct MetaInfo
{
    std::unordered_map<std::string, std::vector<Metadata>> metadata;
};

/* Class: MetaFileReader
 * Takes care of reading and parsing a .meta file.
 */
class MetaFileReader
{
public:
    MetaFileReader();
    ~MetaFileReader();

    /* Function: Read
     *
     * Parameters:
     *
     *    filename - Path to the file to read
     *
     * Returns:
     *
     *    The data in the form of a <MetaInfo> object
     *
     * Throws:
     *
     *    std::runtime_error if there is an error such as file format error or I/O error
     */
    MetaInfo Read(const std::string& filename);

    /* Function: Read
     *
     * Parameters:
     *
     *    filename - Path to the file to read
     *
     * Returns:
     *
     *    The data in the form of a <MetaInfo> object
     *
     * Throws:
     *
     *    std::runtime_error if there is an error such as file format error or I/O error
     */
    MetaInfo Read(std::istream& stream);
private:
    LineReader m_reader;
};

} // namespace txt
