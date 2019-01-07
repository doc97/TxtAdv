/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "StoryLoader.h"
#include "LuaResponseHandler.h"
#include <vector>

namespace txt
{

StoryLoader::StoryLoader()
{
}

StoryLoader::~StoryLoader()
{
}

std::vector<StoryPoint> StoryLoader::Load(const std::string& filename)
{
    TxtContentInfo txtInfo = m_txtReader.Read(filename);
    CtrlContentInfo ctrlInfo = m_ctrlReader.Read(txtInfo.ctrl_filename);
    MergeMetadataWithStoryPoints(txtInfo, ctrlInfo);
    if (!txtInfo.style_filename.empty())
    {
        TextStyleSheet sheet = m_styleReader.Read(txtInfo.style_filename);
        MergeStyleSheetWithStoryPoints(txtInfo, sheet);
    }
    return txtInfo.story_points;
}

void StoryLoader::MergeMetadataWithStoryPoints(TxtContentInfo& txtInfo, CtrlContentInfo& metaInfo) const
{
    for (StoryPoint& point : txtInfo.story_points)
    {
        bool hasMetadata = metaInfo.metadata.find(point.GetName()) != metaInfo.metadata.end();
        if (hasMetadata)
        {
            std::vector<CtrlContent> data = metaInfo.metadata[point.GetName()];
            MergeMetadataWithStoryPoint(point, data);
        }
    }
}

void StoryLoader::MergeMetadataWithStoryPoint(StoryPoint& point, std::vector<CtrlContent>& metadata) const
{
    std::vector<std::shared_ptr<ResponseHandler>> handlers;
    for (const CtrlContent& meta : metadata)
    {
        handlers.push_back(std::make_shared<LuaResponseHandler>(
            meta.script,
            meta.matcher_func,
            meta.action_func
        ));
    }
    point.SetHandlers(handlers);
}

void StoryLoader::MergeStyleSheetWithStoryPoints(TxtContentInfo& txtInfo, TextStyleSheet style) const
{
    for (StoryPoint& point : txtInfo.story_points)
    {
        Text text = point.GetText();
        style.Apply(text);
        point.SetText(text);
    }
}

} // namespace txt
