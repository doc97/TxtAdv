/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <vector>
#include "FileLineReader.h"
#include "StoryPoint.h"

namespace txt
{

/* Struct: TxtInfo
 * The result of the <TxtFileReader>.
 */
struct TxtInfo
{
    std::string meta_filename;
    std::string style_filename;
    std::vector<StoryPoint> story_points;
};

/* Class: TxtFileReader
 * Takes care of reading and parsing a .txt file.
 */
class TxtFileReader
{
public:
    TxtFileReader();
    ~TxtFileReader();

    /* Function: Read
     *
     * Parameters:
     *
     *    filename - Path to the file to read
     *
     * Returns:
     *
     *    The data in the form of a <TxtInfo> object
     *
     * Throws:
     *
     *    std::runtime_error if there is an error such as file format error or I/O error
     */
    TxtInfo Read(const std::string& filename);
private:
    FileLineReader m_reader;

    bool GetKeyValue(std::ifstream& file, const std::string& key, std::string& value, bool oneline);
    std::vector<StoryPoint> GetStoryPoints(std::ifstream& file);
    StoryPoint CreateStoryPoint(const std::string& name, const std::string& txt) const;
};

} // namespace txt
