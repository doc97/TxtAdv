/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "Text.h"
#include <algorithm>
#include <cctype>
#include <sstream>

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

std::vector<TextMetadata> Text::GetMetadata() const
{
    return m_metadata;
}

std::vector<TextTag> Text::GetTags() const
{
    return m_tags;
}

std::string Text::Parse(const std::string& raw)
{
    std::string res = raw;
    std::vector<TextEmphasisChange> emphasis = ParseEmphasisChanges(res);
    std::vector<TextMetadataChange> metadata = ParseMetadataChanges(res);
    std::vector<TextRemoveRange> removals = ParseRemoveRanges(res);
    std::vector<TextTagChange> tags = ParseTagChanges(res);

    SortEmphasisChanges(emphasis);
    SortMetadataChanges(metadata);
    SortRemoveRanges(removals);

    RemoveMarkupCharacters(res, emphasis, metadata, removals, tags);

    m_emphasis = ExtractEmphasisStyles(emphasis, res.length());
    m_emphasis = CompressEmphasisStyles(m_emphasis);

    m_metadata = ExtractMetadata(metadata, res.length());
    m_metadata = CompressMetadata(m_metadata);

    m_tags = ExtractTags(tags);
    m_tags = CompressTags(m_tags);

    return res;
}

void Text::RemoveMarkupCharacters(std::string& str,
    std::vector<TextEmphasisChange>& emphasisChanges,
    std::vector<TextMetadataChange>& metadataChanges,
    std::vector<TextRemoveRange>& removals,
    std::vector<TextTagChange>& tagChanges) const
{
    std::vector<TextEmphasisChange>::iterator emIt = emphasisChanges.begin();
    std::vector<TextMetadataChange>::iterator mdIt = metadataChanges.begin();
    std::vector<TextRemoveRange>::iterator rmIt = removals.begin();
    std::vector<TextTagChange>::iterator tgIt = tagChanges.begin();
    size_t charsRemoved = 0;

    while (emIt != emphasisChanges.end() || mdIt != metadataChanges.end() ||
        rmIt != removals.end() || tgIt != tagChanges.end())
    {
        size_t emIdx = (emIt == emphasisChanges.end() ? SIZE_MAX : emIt->idx);
        size_t mdIdx = (mdIt == metadataChanges.end() ? SIZE_MAX : mdIt->idx);
        size_t rmIdx = (rmIt == removals.end() ? SIZE_MAX : rmIt->idx);
        size_t tgIdx = (tgIt == tagChanges.end() ? SIZE_MAX : tgIt->idx);

        if (emIdx < mdIdx && emIdx < rmIdx && emIdx < tgIdx)
        {
            emIt->idx -= charsRemoved;
            charsRemoved += emIt->style_len;
            str.erase(emIt->idx, emIt->style_len);

            ++emIt;
        }
        else if (mdIdx < emIdx && mdIdx < rmIdx && mdIdx < tgIdx)
        {
            mdIt->idx -= charsRemoved;
            charsRemoved += mdIt->len;
            str.erase(mdIt->idx, mdIt->len);

            ++mdIt;
        }
        else if (rmIdx < emIdx && rmIdx < mdIdx && rmIdx < tgIdx)
        {
            rmIt->idx -= charsRemoved;
            charsRemoved += rmIt->len;
            str.erase(rmIt->idx, rmIt->len);

            ++rmIt;
        }
        else if (tgIdx < emIdx && tgIdx < mdIdx && tgIdx < rmIdx)
        {
            tgIt->idx -= charsRemoved;
            charsRemoved += tgIt->len;
            str.erase(tgIt->idx, tgIt->len);

            ++tgIt;
        }
    }
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

std::vector<Text::TextEmphasisChange> Text::ParseEmphasisChange(const std::string& str, const std::string& styleId,
    Emphasis emphasis) const
{
    std::vector<TextEmphasisChange> changes;

    size_t offset = 0;
    size_t startIdx = 0;
    while ((startIdx = str.find(styleId, offset)) != std::string::npos)
    {
        if (startIdx > 0 && str.at(startIdx - 1) == '\\')
        {
            offset = startIdx + 1;
            continue;
        }

        size_t endIdx = str.find(styleId, startIdx + styleId.length());
        if (endIdx == std::string::npos)
            break;

        TextEmphasisChange startChange;
        startChange.idx = startIdx;
        startChange.style_len = styleId.length();
        startChange.mask = std::bitset<EmphasisBits::BIT_COUNT>((unsigned long)emphasis);

        TextEmphasisChange endChange;
        endChange.idx = endIdx;
        endChange.style_len = styleId.length();
        endChange.mask = std::bitset<EmphasisBits::BIT_COUNT>((unsigned long)emphasis);

        changes.push_back(startChange);
        changes.push_back(endChange);
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
                if (it->mask[EmphasisBits::ITALIC_BIT])
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

std::vector<TextEmphasis> Text::ExtractEmphasisStyles(const std::vector<TextEmphasisChange>& changes, const size_t strLen) const
{
    std::vector<TextEmphasis> styles;
    size_t start = 0;
    std::bitset<EmphasisBits::BIT_COUNT> styleMask;
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
        if (cur->bitmask == lastStyle.bitmask)
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

std::vector<Text::TextMetadataChange> Text::ParseMetadataChanges(const std::string& str) const
{
    std::vector<TextMetadataChange> changes;
    std::vector<TextMetadataChange> sizeChanges = ParseSizeChanges(str);
    std::vector<TextMetadataChange> colorChanges = ParseColorChanges(str);

    changes.reserve(sizeChanges.size() + colorChanges.size());
    CombineMetadataChanges(changes, sizeChanges);
    CombineMetadataChanges(changes, colorChanges);
    return changes;
}

std::vector<Text::TextMetadataChange> Text::ParseSizeChanges(const std::string& str) const
{
    std::vector<TextMetadataChange> changes;
    size_t offset = 0;
    size_t startIdx = 0;

    while ((startIdx = str.find("!", offset)) != std::string::npos)
    {
        // Increment first to avoid incrementing at each flow exit
        offset = startIdx + 1;

        if (startIdx > 0 && str.at(startIdx - 1) == '\\')
            continue;

        if (startIdx == str.length() - 1)
            break;

        char sizeCh = str.at(startIdx + 1);
        if (!std::isdigit(sizeCh))
            continue;

        size_t sizeDigit = sizeCh - '0';
        TextMetadata data;
        switch (sizeDigit)
        {
        case 1:
            data.size = TextSize::S1;
            break;
        case 2:
            data.size = TextSize::S2;
            break;
        case 3:
            data.size = TextSize::S3;
            break;
        case 4:
            data.size = TextSize::S4;
            break;
        case 5:
            data.size = TextSize::S5;
            break;
        default:
            continue;
        }

        TextMetadataChange change;
        change.idx = startIdx;
        change.len = 2;
        change.data = data;
        change.changeMask.set(MetadataChangeBits::SIZE_CHANGE, true);
        changes.push_back(change);
    }
    return changes;
}

std::vector<Text::TextMetadataChange> Text::ParseColorChanges(const std::string& str) const
{
    std::vector<TextMetadataChange> changes;
    size_t offset = 0;
    size_t startIdx = 0;

    while ((startIdx = str.find("#", offset)) != std::string::npos)
    {
        // Increment first to avoid incrementing at each flow exit
        offset = startIdx + 1;

        if (startIdx > 0 && str.at(startIdx - 1) == '\\')
            continue;

        if (startIdx + 8 >= str.length() - 1)
            break;

        unsigned int hexVal;
        std::string hexStr = str.substr(startIdx + 1, 8);
        std::istringstream converter(hexStr);
        converter >> std::hex >> hexVal;
        if (converter.fail())
            continue;

        TextMetadata data;
        data.color.r = (hexVal & 0xFF000000) >> 24;
        data.color.g = (hexVal & 0x00FF0000) >> 16;
        data.color.b = (hexVal & 0x0000FF00) >> 8;
        data.color.a = (hexVal & 0x000000FF);

        TextMetadataChange change;
        change.idx = startIdx;
        change.len = 9;
        change.data = data;
        change.changeMask.set(MetadataChangeBits::COLOR_CHANGE, true);
        changes.push_back(change);

        offset += 8;
    }
    return changes;
}

void Text::CombineMetadataChanges(std::vector<TextMetadataChange>& orig,
    const std::vector<TextMetadataChange>& append) const
{
    std::vector<TextMetadataChange>::const_iterator it;
    for (it = append.begin(); it != append.end(); ++it)
        orig.push_back(*it);
}

void Text::SortMetadataChanges(std::vector<TextMetadataChange>& changes) const
{
    std::sort(changes.begin(), changes.end(), [](const TextMetadataChange& a, const TextMetadataChange& b)
    {
        return a.idx < b.idx;
    });
}

std::vector<TextMetadata> Text::ExtractMetadata(const std::vector<TextMetadataChange>& changes,
    const size_t strLen) const
{
    std::vector<TextMetadata> metadata;
    size_t start = 0;
    TextSize size = TextSize::S1;
    Color color = { 255, 255, 255, 255 };
    for (auto it = changes.begin(); it != changes.end(); ++it)
    {
        size_t len = it->idx - start;
        if (len > 0)
        {
            TextMetadata data;
            data.start = start;
            data.len = len;
            data.size = size;
            data.color = color;
            metadata.push_back(data);
        }

        if (it->changeMask[MetadataChangeBits::SIZE_CHANGE])
            size = it->data.size;
        if (it->changeMask[MetadataChangeBits::COLOR_CHANGE])
            color = it->data.color;
        start = it->idx;
    }
    size_t len = strLen - start;
    if (len > 0)
    {
        TextMetadata data;
        data.start = start;
        data.len = len;
        data.size = size;
        data.color = color;
        metadata.push_back(data);
    }
    return metadata;
}

std::vector<TextMetadata> Text::CompressMetadata(const std::vector<TextMetadata>& metadata) const
{
    std::vector<TextMetadata> result;
    if (metadata.empty())
        return result;
    std::vector<TextMetadata>::const_iterator last = metadata.begin();
    std::vector<TextMetadata>::const_iterator cur = metadata.begin() + 1;
    TextMetadata lastMetadata = *last;

    for (; cur != metadata.end(); ++last, ++cur)
    {
        if (*cur == lastMetadata)
        {
            lastMetadata.len += cur->len;
        }
        else
        {
            result.push_back(lastMetadata);
            lastMetadata = *cur;
        }
    }
    result.push_back(lastMetadata);
    return result;
}

std::vector<Text::TextRemoveRange> Text::ParseRemoveRanges(const std::string& str) const
{
    std::vector<TextRemoveRange> removals;
    std::vector<TextRemoveRange> escapeSequences = ParseEscapeSequences(str);

    removals.reserve(escapeSequences.size());
    CombineRemoveRanges(removals, escapeSequences);
    return removals;
}

std::vector<Text::TextRemoveRange> Text::ParseEscapeSequences(const std::string& str) const
{
    std::vector<TextRemoveRange> points;
    size_t offset = 0;
    size_t startIdx = 0;

    while ((startIdx = str.find("\\", offset)) != std::string::npos)
    {
        offset = startIdx + 1;

        if (startIdx < str.length() && str.at(startIdx + 1) == '\\')
            ++offset; // Increment to skip over the next backslash

        TextRemoveRange point;
        point.idx = startIdx;
        point.len = 1;
        points.push_back(point);
    }
    return points;
}

void Text::CombineRemoveRanges(std::vector<TextRemoveRange>& orig,
    const std::vector<TextRemoveRange>& append) const
{
    std::vector<TextRemoveRange>::const_iterator it;
    for (it = append.begin(); it != append.end(); ++it)
        orig.push_back(*it);
}

void Text::SortRemoveRanges(std::vector<TextRemoveRange>& points) const
{
    std::sort(points.begin(), points.end(), [](const TextRemoveRange& a, const TextRemoveRange& b)
    {
        return a.idx < b.idx;
    });
}

std::vector<Text::TextTagChange> Text::ParseTagChanges(const std::string& str) const
{
    std::vector<TextTagChange> changes;
    size_t offset = 0;
    while (offset < str.length())
    {
        size_t start;
        if ((start = str.find("<", offset)) == std::string::npos)
            break;

        offset = start + 1;
        if (start > 0 && str.at(start - 1) == '\\')
            continue;

        size_t startEnd;
        if ((startEnd = str.find(">", offset)) == std::string::npos)
            break;

        std::string name = str.substr(start + 1, startEnd - start - 1);

        offset = startEnd + 1;
        if (str.at(startEnd - 1) == '\\')
            continue;

        size_t end;
        while ((end = str.find("</" + name + ">", offset)) != std::string::npos)
        {
            offset = end + 1;
            if (str.at(end - 1) == '\\')
                continue;
            break;
        }
        if (end == std::string::npos)
            break;

        size_t endEnd = end + name.length() + 2;
        offset = endEnd + 1;
        if (str.at(end - 1) == '\\')
            continue;

        TextTagChange startChange;
        startChange.idx = start;
        startChange.len = startEnd - start + 1;
        startChange.name = name;

        changes.push_back(startChange);

        TextTagChange endChange;
        endChange.idx = end;
        endChange.len = endEnd - end + 1;
        endChange.name = name;

        changes.push_back(endChange);
    }

    return changes;
}

std::vector<TextTag> Text::ExtractTags(const std::vector<TextTagChange>& changes)
{
    std::vector<TextTag> tags;
    for (auto it = changes.begin(); it != changes.end() && (it + 1) != changes.end(); it += 2)
    {
        size_t start = it->idx;
        size_t end = (it + 1)->idx;
        size_t len = end - start;

        if (len > 0)
        {
            TextTag tag;
            tag.start = start;
            tag.len = len;
            tag.name = it->name;
            tags.push_back(tag);
        }
    }
    return tags;
}

std::vector<TextTag> Text::CompressTags(const std::vector<TextTag>& tags) const
{
    std::vector<TextTag> result;
    if (tags.empty())
        return result;
    std::vector<TextTag>::const_iterator last = tags.begin();
    std::vector<TextTag>::const_iterator cur = tags.begin() + 1;
    TextTag lastTag = *last;

    for (; cur != tags.end(); ++last, ++cur)
    {
        if (lastTag.start + lastTag.len == cur->start && cur->name == lastTag.name)
        {
            lastTag.len += cur->len;
        }
        else
        {
            result.push_back(lastTag);
            lastTag = *cur;
        }
    }
    result.push_back(lastTag);
    return result;

}

} // namespace txt
