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

void StoryPoint::SetMarkup(const std::string& text, const std::vector<std::function<std::string()>>& expr)
{
    m_text = text;
    m_expressions = expr;
}

void StoryPoint::SetHandlers(const std::vector<std::shared_ptr<ResponseHandler>>& handlers)
{
    m_handlers = handlers;
}

void StoryPoint::NotifyHandlers(const std::string& message)
{
    for (auto& handler : m_handlers)
        handler->HandleInput(message);
}

std::string StoryPoint::ParseText(const std::string& text,
    const std::vector<std::function<std::string()>>& expr) const
{
    std::string parsedText = text;
    for (unsigned int i = 0; i < expr.size(); ++i)
    {
        std::string var = "$" + std::to_string(i);
        std::string replacement = expr[i]();
        if (IsIllegalText(replacement))
            replacement = "";

        size_t curPos = 0;
        while ((curPos = parsedText.find(var, curPos)) != std::string::npos)
            parsedText.replace(curPos, var.length(), replacement);
    }
    return parsedText;
}

bool StoryPoint::IsIllegalText(const std::string& text) const
{
    bool hasDollar = text.find("$") != std::string::npos;
    return hasDollar;
}

std::string StoryPoint::GetText() const
{
    return ParseText(m_text, m_expressions);
}

size_t StoryPoint::GetHandlerCount() const
{
    return m_handlers.size();
}

std::vector<std::shared_ptr<ResponseHandler>> StoryPoint::GetHandlers() const
{
    return m_handlers;
}
