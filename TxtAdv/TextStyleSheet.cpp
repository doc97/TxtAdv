/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "TextStyleSheet.h"

namespace txt
{

TextStyleSheet::TextStyleSheet()
{
}

TextStyleSheet::~TextStyleSheet()
{
}

void TextStyleSheet::Apply(Text& text) const
{
    std::vector<TextTag> tags = text.GetTags();
    for (const TextTag& tag : tags)
    {
        if (!HasStyle(tag.name))
            continue;

        size_t start = tag.start;
        size_t len = tag.len;
        TextStyle style = GetStyle(tag.name);

        text.SetEmphasisStyle(start, len, style.bitmask);
        text.SetMetadata(start, len, style.size, style.outline_color, style.fill_color, style.bg_color,
            MetadataChangeBits::ALL_CHANGED);
    }
}

void TextStyleSheet::SetStyle(const std::string& tag, const TextStyle& style)
{
    m_styles[tag] = style;
}

void TextStyleSheet::UnsetStyle(const std::string& tag)
{
    m_styles.erase(tag);
}

bool TextStyleSheet::HasStyle(const std::string& tag) const
{
    return m_styles.find(tag) != m_styles.end();
}

TextStyle TextStyleSheet::GetStyle(const std::string& tag) const
{
    if (m_styles.find(tag) != m_styles.end())
        return m_styles.at(tag);
    return TextStyle{};
}

} // namespace txt
