/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include "StoryPoint.h"
#include "TxtFileReader.h"
#include "MetaFileReader.h"

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
     * Loads a set of <StoryPoint>s from a .txt file.
     *
     * Parameters:
     *
     *    filename - The path to the .txt file
     *
     * Returns:
     *
     *    A vector of the loaded story points.
     */
    std::vector<StoryPoint> Load(const std::string& filename);
private:
    TxtFileReader m_txtReader;
    MetaFileReader m_metaReader;

    void MergeMetadataWithStoryPoints(TxtInfo& txtInfo, MetaInfo& metaInfo) const;
    void MergeMetadataWithStoryPoint(StoryPoint& point, std::vector<Metadata>& metadata) const;
};

} // namespace txt
