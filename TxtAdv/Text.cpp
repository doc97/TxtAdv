/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "Text.h"
#include <algorithm>

namespace txt
{

Text::Text(const std::string& text)
    : m_raw(text)
{
    m_str = Parse(text);
}

Text::~Text()
{
}

std::string Text::Str() const
{
    return m_str;
}

std::string Text::RawStr() const
{
    return m_raw;
}

std::vector<TextStyle> Text::GetStyles() const
{
    return m_styles;
}

std::string Text::Parse(const std::string& raw)
{
    std::string res = raw;
    std::vector<TextStyleChange> changes = ParseStyles(res);
    SortChanges(changes);
    RemoveMarkupCharacters(res, changes);
    m_styles = ExtractStyles(changes, res.length());
    m_styles = CompressStyles(m_styles);
    
    return res;
}

std::vector<Text::TextStyleChange> Text::ParseStyles(const std::string& str) const
{
    std::vector<TextStyleChange> changes;
    std::vector<TextStyleChange> underline = ParseStyle(str, "__", Styles::UNDERL);
    std::vector<TextStyleChange> italics = ParseStyle(str, "_", Styles::ITALIC);
    std::vector<TextStyleChange> bold = ParseStyle(str, "*", Styles::BOLD);
    std::vector<TextStyleChange> strikethrough = ParseStyle(str, "~", Styles::STRIKE);
    changes.reserve(underline.size() + italics.size() + bold.size() + strikethrough.size());

    // Important - Underline before italics
    CombineStyles(changes, underline);
    CombineStyles(changes, italics);
    CombineStyles(changes, bold);
    CombineStyles(changes, strikethrough);
    return changes;
}

std::vector<Text::TextStyleChange> Text::ParseStyle(const std::string& str, const std::string& styleId, Styles style) const
{
    std::vector<TextStyleChange> changes;

    size_t offset = 0;
    size_t startIdx = 0;
    while ((startIdx = str.find(styleId, offset)) != std::string::npos)
    {
        size_t endIdx = str.find(styleId, startIdx + styleId.length());
        if (endIdx == std::string::npos)
            break;

        changes.push_back({ startIdx, styleId.length(), (unsigned char)style });
        changes.push_back({ endIdx, styleId.length(), (unsigned char)style });
        offset = endIdx + 1;
    }
    return changes;
}

void Text::CombineStyles(std::vector<TextStyleChange>& orig, const std::vector<TextStyleChange>& append) const
{
    std::vector<TextStyleChange>::const_iterator it;
    for (it = append.begin(); it != append.end(); ++it)
    {
        bool isUnique = true;
        for (const TextStyleChange& origStyle : orig)
        {
            if (origStyle.idx == it->idx)
            {
                isUnique = false;
                if ((it->style_mask & Styles::ITALIC) == Styles::ITALIC)
                    ++it;
                break;
            }
            else if (origStyle.idx > it->idx)
            {
                break;
            }
        }
        if (isUnique && it != append.end())
            orig.push_back(*it);
    }
}

void Text::SortChanges(std::vector<TextStyleChange>& changes) const
{
    std::sort(changes.begin(), changes.end(), [](const TextStyleChange& a, const TextStyleChange& b)
    {
        return a.idx < b.idx;
    });
}

void Text::RemoveMarkupCharacters(std::string& str, std::vector<TextStyleChange>& changes) const
{
    std::vector<TextStyleChange>::iterator it = changes.begin();
    size_t i = 0;
    size_t lastIdx = SIZE_MAX;
    for (size_t i = 0; it != changes.end(); ++it)
    {
        if (lastIdx == it->idx)
            continue;
        lastIdx = it->idx;
        it->idx -= i;
        i += it->style_len;
        str.erase(it->idx, it->style_len);
    }
}

std::vector<TextStyle> Text::ExtractStyles(const std::vector<TextStyleChange>& changes, const size_t strLen) const
{
    std::vector<TextStyle> styles;
    size_t start = 0;
    unsigned char styleMask = Styles::NORMAL;
    for (auto it = changes.begin(); it != changes.end(); ++it)
    {
        size_t len = it->idx - start;
        if (len > 0)
            styles.push_back({ start, len, styleMask });
        styleMask ^= it->style_mask;
        start = it->idx;
    }
    size_t len = strLen - start;
    if (len > 0)
        styles.push_back({ start, len, styleMask });
    return styles;
}

std::vector<TextStyle> Text::CompressStyles(const std::vector<TextStyle>& styles) const
{
    std::vector<TextStyle> result;
    if (styles.empty())
        return result;
    std::vector<TextStyle>::const_iterator last = styles.begin();
    std::vector<TextStyle>::const_iterator cur = styles.begin() + 1;
    TextStyle lastStyle = *last;

    for (; cur != styles.end(); ++last, ++cur)
    {
        if (cur->style == lastStyle.style)
        {
            lastStyle.len += cur->len;
        }
        else
        {
            result.push_back(lastStyle);
            lastStyle = *cur;
        }
    }
    result.push_back(lastStyle);
    return result;
}

} // namespace txt
