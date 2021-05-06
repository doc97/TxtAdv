/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "StoryPoint.h"

namespace txt
{

StoryPoint::StoryPoint()
    : m_name(""), m_text("")
{
}

StoryPoint::StoryPoint(const std::string& name)
    : m_name(name), m_text("")
{
}

StoryPoint::~StoryPoint()
{
}

void StoryPoint::SetText(const Text& other)
{
    m_text = other;
}

void StoryPoint::SetTextStr(const std::string& text)
{
    m_text = Text{ text };
}

void StoryPoint::SetStyleSheet(const TextStyleSheet style)
{
    m_style = style;
}

void StoryPoint::SetParser(TextParser* parser)
{
    m_parser = parser;
}

void StoryPoint::SetMarkup(TextMarkup* markup)
{
    m_markup = markup;
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
    return GetText().Str();
}

Text StoryPoint::GetText() const
{
    Text parsed = m_text; // copy assignment
    if (m_markup)
        parsed = m_markup->ParseText(m_parser ? m_parser->ParseText(m_text.Str()) : m_text.Str());
    else if (m_parser)
        parsed = m_parser->ParseText(m_text.Str());

    m_style.Apply(parsed);
    return parsed;
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
