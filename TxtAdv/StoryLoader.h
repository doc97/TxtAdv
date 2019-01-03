/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include <unordered_map>
#include <vector>
#include "LuaManager.h"
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
    struct Metadata
    {
        std::string storypoint;
        std::string script;
        std::string matcher_func;
        std::string action_func;
    };

    std::string GetMetaFile(std::ifstream& file) const;
    std::vector<StoryPoint> GetStoryPoints(std::ifstream& file) const;
    StoryPoint CreateStoryPoint(const std::string& name, const std::string& txt) const;
    std::unordered_map<std::string, std::vector<Metadata>> GetMetadata(const std::string& filename) const;
    void MergeMetadataWithStoryPoints(std::vector<StoryPoint>& points,
        std::unordered_map<std::string, std::vector<Metadata>>& metadata) const;
    void MergeMetadataWithStoryPoint(StoryPoint& point, std::vector<Metadata>& metadata) const;
};

} // namespace txt
