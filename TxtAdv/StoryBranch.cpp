#include "StoryBranch.h"

StoryBranch::StoryBranch()
{
}

StoryBranch::~StoryBranch()
{
}

void StoryBranch::AddPoint(const StoryPoint& point)
{
    m_points.push_back(std::make_shared<StoryPoint>(point));
}

void StoryBranch::AddPoint(const std::string& text)
{
    StoryPoint point;
    point.SetText(text);
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

std::shared_ptr<StoryPoint> StoryBranch::GetPointAt(unsigned int index) const
{
    return m_points.at(index);
}

std::shared_ptr<StoryPoint> StoryBranch::GetHead() const
{
    if (m_points.empty())
        return nullptr;
    return m_points.at(m_head);
}

unsigned int StoryBranch::Length() const
{
    return m_points.size();
}

bool StoryBranch::Empty() const
{
    return Length() == 0;
}
