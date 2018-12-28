/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "StoryBranch.h"
#include "LambdaResponseHandler.h"

namespace txt
{

StoryBranch::StoryBranch()
{
}

StoryBranch::StoryBranch(const std::string& name)
    : m_name(name)
{
}

StoryBranch::~StoryBranch()
{
}

void StoryBranch::AddPoint(const StoryPoint& point)
{
    m_points.push_back(std::make_shared<StoryPoint>(point));
}

void StoryBranch::AddPoint(const std::string& text, std::shared_ptr<TextParser> parser,
    const std::vector<std::shared_ptr<ResponseHandler>>& handlers)
{
    StoryPoint point;
    point.SetTextStr(text);
    point.SetParser(parser);
    point.SetHandlers(handlers);
    AddPoint(point);
}

void StoryBranch::Next()
{
    if (m_head + 1 < m_points.size())
        ++m_head;
}

void StoryBranch::Prev()
{
    if (m_head > 0)
        --m_head;
}

void StoryBranch::SetCurrentPoint(unsigned int index)
{
    if (index >= m_points.size())
        throw std::out_of_range("index is out of bounds");
    m_head = index;
}

void StoryBranch::SetParentBranch(const StoryBranch& parent)
{
    m_parent = std::make_shared<StoryBranch>(parent);
}

void StoryBranch::UnsetParentBranch()
{
    m_parent = nullptr;
}

std::string StoryBranch::GetName() const
{
    return m_name;
}

StoryPoint* StoryBranch::GetPointAt(unsigned int index) const
{
    return m_points.at(index).get();
}

StoryPoint* StoryBranch::GetHead() const
{
    if (m_points.empty())
        return nullptr;
    return m_points.at(m_head).get();
}

StoryBranch* StoryBranch::GetParentBranch() const
{
    return m_parent.get();
}

size_t StoryBranch::Length() const
{
    return m_points.size();
}

bool StoryBranch::Empty() const
{
    return Length() == 0;
}

} // namespace txt
