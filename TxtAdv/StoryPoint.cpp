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

void StoryPoint::SetHandlers(const std::vector<ResponseHandler>& handlers)
{
    m_handlers = handlers;
}

void StoryPoint::NotifyHandlers(const std::string& message)
{
    for (auto& handler : m_handlers)
        handler.HandleInput(message);
}

std::string StoryPoint::GetText() const
{
    return m_text;
}

size_t StoryPoint::GetHandlerCount() const
{
    return m_handlers.size();
}

std::vector<ResponseHandler> StoryPoint::GetHandlers() const
{
    return m_handlers;
}
