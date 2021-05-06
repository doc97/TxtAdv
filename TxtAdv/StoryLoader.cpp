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

std::vector<StoryPoint> StoryLoader::Load(const std::string& filename, TextMarkup* markup, LuaManager* lua)
{
    TxtContentInfo txtInfo = m_txtReader.Read(filename);
    CtrlContentInfo ctrlInfo = m_ctrlReader.Read(txtInfo.ctrl_filename);
    MergeCtrlInfoWithStoryPoints(txtInfo, ctrlInfo, lua);
    if (!txtInfo.style_filename.empty())
    {
        TextStyleSheet sheet = m_styleReader.Read(txtInfo.style_filename);
        MergeStyleSheetWithStoryPoints(txtInfo, sheet);
    }

    for (auto& point : txtInfo.story_points) {
        point.SetMarkup(markup);
    }
    return txtInfo.story_points;
}

void StoryLoader::MergeCtrlInfoWithStoryPoints(TxtContentInfo& txtInfo, CtrlContentInfo& ctrlInfo, LuaManager* lua) const
{
    for (StoryPoint& point : txtInfo.story_points)
    {
        bool hasMetadata = ctrlInfo.ctrl_content.find(point.GetName()) != ctrlInfo.ctrl_content.end();
        if (hasMetadata)
        {
            std::vector<CtrlContent> data = ctrlInfo.ctrl_content[point.GetName()];
            MergeCtrlInfoWithStoryPoint(point, data, lua);
        }
    }
}

void StoryLoader::MergeCtrlInfoWithStoryPoint(StoryPoint& point, std::vector<CtrlContent>& ctrl_content, LuaManager* lua) const
{
    std::vector<std::shared_ptr<ResponseHandler>> handlers;
    for (const CtrlContent& ctrl : ctrl_content)
    {
        handlers.push_back(std::make_shared<LuaResponseHandler>(
            lua,
            ctrl.script,
            ctrl.matcher_func,
            ctrl.action_func
        ));
    }
    point.SetHandlers(handlers);
}

void StoryLoader::MergeStyleSheetWithStoryPoints(TxtContentInfo& txtInfo, TextStyleSheet style) const
{
    for (StoryPoint& point : txtInfo.story_points)
    {
        point.SetStyleSheet(style);
    }
}

} // namespace txt
