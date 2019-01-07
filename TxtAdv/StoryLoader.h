/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include "StoryPoint.h"
#include "TxtContentReader.h"
#include "CtrlContentReader.h"
#include "StyleContentReader.h"

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
    TxtContentReader m_txtReader;
    CtrlContentReader m_ctrlReader;
    StyleContentReader m_styleReader;

    void MergeMetadataWithStoryPoints(TxtContentInfo& txtInfo, CtrlContentInfo& metaInfo) const;
    void MergeMetadataWithStoryPoint(StoryPoint& point, std::vector<CtrlContent>& ctrlInfo) const;
    void MergeStyleSheetWithStoryPoints(TxtContentInfo& txtInfo, TextStyleSheet style) const;
};

} // namespace txt
