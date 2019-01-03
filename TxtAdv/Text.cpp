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

std::vector<TextEmphasis> Text::GetEmphasisStyles() const
{
    return m_emphasis;
}

std::string Text::Parse(const std::string& raw)
{
    std::string res = raw;
    ParseEmphasisStyles(res);

    return res;
}

void Text::ParseEmphasisStyles(std::string& str)
{
    std::vector<TextEmphasisChange> changes = ParseEmphasisChanges(str);
    SortEmphasisChanges(changes);
    RemoveMarkupCharacters(str, changes);
    m_emphasis = ExtractEmphasisStyles(changes, str.length());
    m_emphasis = CompressEmphasisStyles(m_emphasis);
}

std::vector<Text::TextEmphasisChange> Text::ParseEmphasisChanges(const std::string& str) const
{
    std::vector<TextEmphasisChange> changes;
    std::vector<TextEmphasisChange> underline = ParseEmphasisChange(str, "__", Emphasis::UNDERL);
    std::vector<TextEmphasisChange> italics = ParseEmphasisChange(str, "_", Emphasis::ITALIC);
    std::vector<TextEmphasisChange> bold = ParseEmphasisChange(str, "*", Emphasis::BOLD);
    std::vector<TextEmphasisChange> strikethrough = ParseEmphasisChange(str, "~", Emphasis::STRIKE);
    changes.reserve(underline.size() + italics.size() + bold.size() + strikethrough.size());

    // Important - Underline before italics
    CombineEmphasisChanges(changes, underline);
    CombineEmphasisChanges(changes, italics);
    CombineEmphasisChanges(changes, bold);
    CombineEmphasisChanges(changes, strikethrough);
    return changes;
}

std::vector<Text::TextEmphasisChange> Text::ParseEmphasisChange(const std::string& str, const std::string& styleId, Emphasis emphasis) const
{
    std::vector<TextEmphasisChange> changes;

    size_t offset = 0;
    size_t startIdx = 0;
    while ((startIdx = str.find(styleId, offset)) != std::string::npos)
    {
        size_t endIdx = str.find(styleId, startIdx + styleId.length());
        if (endIdx == std::string::npos)
            break;

        changes.push_back({ startIdx, styleId.length(), (unsigned char)emphasis });
        changes.push_back({ endIdx, styleId.length(), (unsigned char)emphasis });
        offset = endIdx + 1;
    }
    return changes;
}

void Text::CombineEmphasisChanges(std::vector<TextEmphasisChange>& orig, const std::vector<TextEmphasisChange>& append) const
{
    std::vector<TextEmphasisChange>::const_iterator it;
    for (it = append.begin(); it != append.end(); ++it)
    {
        bool isUnique = true;
        for (const TextEmphasisChange& origStyle : orig)
        {
            if (origStyle.idx == it->idx)
            {
                isUnique = false;
                if ((it->mask & Emphasis::ITALIC) == Emphasis::ITALIC)
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

void Text::SortEmphasisChanges(std::vector<TextEmphasisChange>& changes) const
{
    std::sort(changes.begin(), changes.end(), [](const TextEmphasisChange& a, const TextEmphasisChange& b)
    {
        return a.idx < b.idx;
    });
}

void Text::RemoveMarkupCharacters(std::string& str, std::vector<TextEmphasisChange>& changes) const
{
    std::vector<TextEmphasisChange>::iterator it = changes.begin();
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

std::vector<TextEmphasis> Text::ExtractEmphasisStyles(const std::vector<TextEmphasisChange>& changes, const size_t strLen) const
{
    std::vector<TextEmphasis> styles;
    size_t start = 0;
    unsigned char styleMask = Emphasis::NORMAL;
    for (auto it = changes.begin(); it != changes.end(); ++it)
    {
        size_t len = it->idx - start;
        if (len > 0)
            styles.push_back({ start, len, styleMask });
        styleMask ^= it->mask;
        start = it->idx;
    }
    size_t len = strLen - start;
    if (len > 0)
        styles.push_back({ start, len, styleMask });
    return styles;
}

std::vector<TextEmphasis> Text::CompressEmphasisStyles(const std::vector<TextEmphasis>& styles) const
{
    std::vector<TextEmphasis> result;
    if (styles.empty())
        return result;
    std::vector<TextEmphasis>::const_iterator last = styles.begin();
    std::vector<TextEmphasis>::const_iterator cur = styles.begin() + 1;
    TextEmphasis lastStyle = *last;

    for (; cur != styles.end(); ++last, ++cur)
    {
        if (cur->emphasis == lastStyle.emphasis)
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
