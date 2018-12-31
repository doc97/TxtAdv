/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include <vector>
#include "StoryPoint.h"

namespace txt
{

/* Class: StoryLoader
 * Takes care of loading <StoryPoint>s from files.
 */
class StoryLoader
{
public:
    StoryLoader();
    ~StoryLoader();

    /* Function: Load
     * Loads a set of <StoryPoint>s from a file.
     *
     * Parameters:
     *
     *    filename - The path to the file
     *
     * Returns:
     *
     *    A vector of the loaded story points.
     */
    std::vector<StoryPoint> Load(const std::string& filename) const;
private:
    std::string GetMetaFile(std::ifstream& file) const;
    std::vector<StoryPoint> GetStoryPoints(std::ifstream& file) const;
    StoryPoint GetStoryPoint(std::ifstream& file, const std::string& lastLine) const;
};

} // namespace txt
