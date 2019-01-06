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
    TxtInfo txtInfo = m_txtReader.Read(filename);
    MetaInfo metaInfo = m_metaReader.Read(txtInfo.meta_filename);
    MergeMetadataWithStoryPoints(txtInfo, metaInfo);
    return txtInfo.story_points;
}

void StoryLoader::MergeMetadataWithStoryPoints(TxtInfo& txtInfo, MetaInfo& metaInfo) const
{
    for (StoryPoint& point : txtInfo.story_points)
    {
        bool hasMetadata = metaInfo.metadata.find(point.GetName()) != metaInfo.metadata.end();
        if (hasMetadata)
        {
            std::vector<Metadata> data = metaInfo.metadata[point.GetName()];
            MergeMetadataWithStoryPoint(point, data);
        }
    }
}

void StoryLoader::MergeMetadataWithStoryPoint(StoryPoint& point, std::vector<Metadata>& metadata) const
{
    std::vector<std::shared_ptr<ResponseHandler>> handlers;
    for (const Metadata& meta : metadata)
    {
        handlers.push_back(std::make_shared<LuaResponseHandler>(
            meta.script,
            meta.matcher_func,
            meta.action_func
        ));
    }
    point.SetHandlers(handlers);
}

} // namespace txt
