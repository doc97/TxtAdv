#include "StoryPoint.h"

StoryPoint::StoryPoint()
{
}

StoryPoint::~StoryPoint()
{
}

void StoryPoint::SetText(const std::string& text)
{
    m_text = text;
}

std::string StoryPoint::GetText() const
{
    return m_text;
}
