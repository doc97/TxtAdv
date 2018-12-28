/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "StoryPoint.h"

namespace txt
{

StoryPoint::StoryPoint()
    : m_text("")
{
}

StoryPoint::~StoryPoint()
{
}

void StoryPoint::SetTextStr(const std::string& text)
{
    m_text = Text(text);
}

void StoryPoint::SetParser(std::shared_ptr<TextParser> parser)
{
    m_parser = parser;
}

void StoryPoint::SetHandlers(const std::vector<std::shared_ptr<ResponseHandler>>& handlers)
{
    m_handlers = handlers;
}

std::string StoryPoint::ParseTextImpl(const std::string& text,
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

std::string StoryPoint::GetTextStr() const
{
    if (!m_parser)
        return m_text.Str();
    return m_parser->ParseText(m_text.Str());
}

size_t StoryPoint::GetHandlerCount() const
{
    return m_handlers.size();
}

std::vector<std::shared_ptr<ResponseHandler>> StoryPoint::GetHandlers() const
{
    return m_handlers;
}

} // namespace txt
