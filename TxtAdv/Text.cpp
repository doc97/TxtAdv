/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "Text.h"
#include <algorithm>

namespace txt
{

Text::Text(const std::string& text)
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
    
    return res;
}

std::vector<TextStyleChange> Text::ParseStyles(const std::string& str) const
{
    std::vector<TextStyleChange> changes;
    std::vector<TextStyleChange> italics = ParseStyle(str, "_", Styles::ITALIC);
    std::vector<TextStyleChange> bold = ParseStyle(str, "*", Styles::BOLD);
    std::vector<TextStyleChange> strike = ParseStyle(str, "~", Styles::STRIKE);
    changes.reserve(italics.size() + bold.size() + strike.size());
    changes.insert(changes.end(), italics.begin(), italics.end());
    changes.insert(changes.end(), bold.begin(), bold.end());
    changes.insert(changes.end(), strike.begin(), strike.end());
    return changes;
}

std::vector<TextStyleChange> Text::ParseStyle(const std::string& str, const std::string& styleId, Styles style) const
{
    std::vector<TextStyleChange> changes;

    size_t offset = 0;
    size_t startIdx = 0;
    while ((startIdx = str.find(styleId, offset)) != std::string::npos)
    {
        size_t endIdx = str.find(styleId, startIdx + 1);
        if (endIdx == std::string::npos)
            break;

        changes.push_back({ startIdx, (unsigned char)style });
        changes.push_back({ endIdx, (unsigned char)style });
        offset = endIdx + 1;
    }
    return changes;
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
    for (size_t i = 0; it != changes.end(); ++i, ++it)
    {
        it->idx -= i;
        str.erase(it->idx, 1);
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

} // namespace txt
