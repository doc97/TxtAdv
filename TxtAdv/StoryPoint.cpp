/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "StoryPoint.h"
#include "TextMarkup.h"

namespace txt
{

StoryPoint::StoryPoint(const std::string& name)
    : m_name(name)
{
}

StoryPoint::~StoryPoint()
{
}

void StoryPoint::SetTextStr(const std::string& text)
{
    TextMarkup markup(text);
    m_text = markup.GetText();
}

void StoryPoint::SetParser(std::shared_ptr<TextParser> parser)
{
    m_parser = parser;
}

void StoryPoint::SetHandlers(const std::vector<std::shared_ptr<ResponseHandler>>& handlers)
{
    m_handlers = handlers;
}

std::string StoryPoint::GetName() const
{
    return m_name;
}

std::string StoryPoint::GetTextStr() const
{
    if (!m_parser)
        return m_text.Str();
    return m_parser->ParseText(m_text.Str());
}

Text StoryPoint::GetText() const
{
    return m_text;
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
