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

void StoryPoint::SetHandlers(const std::vector<ResponseHandler*>& handlers)
{
    m_handlers = handlers;
}

std::string StoryPoint::GetText() const
{
    return m_text;
}

std::vector<ResponseHandler*> StoryPoint::GetHandlers() const
{
    return m_handlers;
}
