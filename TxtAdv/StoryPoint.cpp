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
    m_handlers.clear();
    for (const ResponseHandler& handler : handlers)
        m_handlers.emplace_back(std::make_shared<ResponseHandler>(handler));
}

std::string StoryPoint::GetText() const
{
    return m_text;
}

size_t StoryPoint::GetHandlerCount() const
{
    return m_handlers.size();
}
