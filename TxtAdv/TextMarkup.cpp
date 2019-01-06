/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "TextMarkup.h"
#include <algorithm>
#include <cctype>
#include <sstream>

namespace txt
{

TextMarkup::TextMarkup(const std::string& raw)
{
    Parse(raw);
}

TextMarkup::~TextMarkup()
{
}

Text TextMarkup::GetText() const
{
    return m_text;
}

void TextMarkup::Parse(const std::string& raw)
{
    std::string res = raw;
    std::vector<TextEmphasisChange> emphasisChanges = ParseEmphasisChanges(res);
    std::vector<TextMetadataChange> metadataChanges = ParseMetadataChanges(res);
    std::vector<TextRemoveRange> removals = ParseRemoveRanges(res);
    std::vector<TextTagChange> tagChanges = ParseTagChanges(res);

    SortEmphasisChanges(emphasisChanges);
    SortMetadataChanges(metadataChanges);
    SortRemoveRanges(removals);

    RemoveMarkupCharacters(res, emphasisChanges, metadataChanges, removals, tagChanges);

    std::vector<TextEmphasis> emphasis = ExtractEmphasisStyles(emphasisChanges, res.length());
    std::vector<TextMetadata> metadata = ExtractMetadata(metadataChanges, res.length());
    std::vector<TextTag> tags = ExtractTags(tagChanges);

    m_text = Text(raw, res, emphasis, metadata, tags);
    m_text.CompressEmphasisStyles();
    m_text.CompressMetadata();
    m_text.CompressTags();
}

void TextMarkup::RemoveMarkupCharacters(std::string& str,
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
            charsRemoved += emIt->len;
            str.erase(emIt->idx, emIt->len);

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

std::vector<TextMarkup::TextEmphasisChange> TextMarkup::ParseEmphasisChanges(const std::string& str) const
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

std::vector<TextMarkup::TextEmphasisChange> TextMarkup::ParseEmphasisChange(const std::string& str, const std::string& styleId,
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
        startChange.len = styleId.length();
        startChange.mask = std::bitset<EmphasisBits::BIT_COUNT>((unsigned long)emphasis);

        TextEmphasisChange endChange;
        endChange.idx = endIdx;
        endChange.len = styleId.length();
        endChange.mask = std::bitset<EmphasisBits::BIT_COUNT>((unsigned long)emphasis);

        changes.push_back(startChange);
        changes.push_back(endChange);
        offset = endIdx + 1;
    }
    return changes;
}

void TextMarkup::CombineEmphasisChanges(std::vector<TextEmphasisChange>& orig, const std::vector<TextEmphasisChange>& append) const
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

void TextMarkup::SortEmphasisChanges(std::vector<TextEmphasisChange>& changes) const
{
    std::sort(changes.begin(), changes.end(), [](const TextEmphasisChange& a, const TextEmphasisChange& b)
    {
        return a.idx < b.idx;
    });
}

std::vector<TextEmphasis> TextMarkup::ExtractEmphasisStyles(const std::vector<TextEmphasisChange>& changes, const size_t strLen) const
{
    std::vector<TextEmphasis> styles;
    size_t start = 0;
    std::bitset<EmphasisBits::BIT_COUNT> styleMask;
    for (auto it = changes.begin(); it != changes.end(); ++it)
    {
        size_t len = it->idx - start;
        if (len > 0)
        {
            TextEmphasis style;
            style.start = start;
            style.len = len;
            style.bitmask = styleMask;
            styles.push_back(style);
        }
        styleMask ^= it->mask;
        start = it->idx;
    }
    size_t len = strLen - start;
    if (len > 0)
    {
        TextEmphasis style;
        style.start = start;
        style.len = len;
        style.bitmask = styleMask;
        styles.push_back(style);
    }
    return styles;
}

std::vector<TextMarkup::TextMetadataChange> TextMarkup::ParseMetadataChanges(const std::string& str) const
{
    std::vector<TextMetadataChange> changes;
    std::vector<TextMetadataChange> sizeChanges = ParseSizeChanges(str);
    std::vector<TextMetadataChange> colorChanges = ParseColorChanges(str);

    changes.reserve(sizeChanges.size() + colorChanges.size());
    CombineMetadataChanges(changes, sizeChanges);
    CombineMetadataChanges(changes, colorChanges);
    return changes;
}

std::vector<TextMarkup::TextMetadataChange> TextMarkup::ParseSizeChanges(const std::string& str) const
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
        change.changeMask.set(MetadataChangeBits::SIZE_CHANGE_BIT, true);
        changes.push_back(change);
    }
    return changes;
}

std::vector<TextMarkup::TextMetadataChange> TextMarkup::ParseColorChanges(const std::string& str) const
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
        data.fill_color.r = (hexVal & 0xFF000000) >> 24;
        data.fill_color.g = (hexVal & 0x00FF0000) >> 16;
        data.fill_color.b = (hexVal & 0x0000FF00) >> 8;
        data.fill_color.a = (hexVal & 0x000000FF);

        TextMetadataChange change;
        change.idx = startIdx;
        change.len = 9;
        change.data = data;
        change.changeMask.set(MetadataChangeBits::FILL_COLOR_CHANGE_BIT, true);
        changes.push_back(change);

        offset += 8;
    }
    return changes;
}

void TextMarkup::CombineMetadataChanges(std::vector<TextMetadataChange>& orig,
    const std::vector<TextMetadataChange>& append) const
{
    std::vector<TextMetadataChange>::const_iterator it;
    for (it = append.begin(); it != append.end(); ++it)
        orig.push_back(*it);
}

void TextMarkup::SortMetadataChanges(std::vector<TextMetadataChange>& changes) const
{
    std::sort(changes.begin(), changes.end(), [](const TextMetadataChange& a, const TextMetadataChange& b)
    {
        return a.idx < b.idx;
    });
}

std::vector<TextMetadata> TextMarkup::ExtractMetadata(const std::vector<TextMetadataChange>& changes,
    const size_t strLen) const
{
    std::vector<TextMetadata> metadata;
    size_t start = 0;
    TextSize size = TextSize::S1;
    Color fill_color = { 255, 255, 255, 255 };
    Color out_color = { 255, 255, 255, 255 };
    Color bg_color = { 0, 0, 0, 0 };
    for (auto it = changes.begin(); it != changes.end(); ++it)
    {
        size_t len = it->idx - start;
        if (len > 0)
        {
            TextMetadata data;
            data.start = start;
            data.len = len;
            data.size = size;
            data.fill_color = fill_color;
            data.outline_color = out_color;
            data.bg_color = bg_color;
            metadata.push_back(data);
        }

        if (it->changeMask[MetadataChangeBits::SIZE_CHANGE_BIT])
            size = it->data.size;
        if (it->changeMask[MetadataChangeBits::FILL_COLOR_CHANGE_BIT])
            fill_color = it->data.fill_color;
        if (it->changeMask[MetadataChangeBits::OUT_COLOR_CHANGE_BIT])
            out_color = it->data.outline_color;
        if (it->changeMask[MetadataChangeBits::BG_COLOR_CHANGE_BIT])
            bg_color = it->data.bg_color;

        start = it->idx;
    }
    size_t len = strLen - start;
    if (len > 0)
    {
        TextMetadata data;
        data.start = start;
        data.len = len;
        data.size = size;
        data.fill_color = fill_color;
        metadata.push_back(data);
    }
    return metadata;
}

std::vector<TextMarkup::TextRemoveRange> TextMarkup::ParseRemoveRanges(const std::string& str) const
{
    std::vector<TextRemoveRange> removals;
    std::vector<TextRemoveRange> escapeSequences = ParseEscapeSequences(str);

    removals.reserve(escapeSequences.size());
    CombineRemoveRanges(removals, escapeSequences);
    return removals;
}

std::vector<TextMarkup::TextRemoveRange> TextMarkup::ParseEscapeSequences(const std::string& str) const
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

void TextMarkup::CombineRemoveRanges(std::vector<TextRemoveRange>& orig,
    const std::vector<TextRemoveRange>& append) const
{
    std::vector<TextRemoveRange>::const_iterator it;
    for (it = append.begin(); it != append.end(); ++it)
        orig.push_back(*it);
}

void TextMarkup::SortRemoveRanges(std::vector<TextRemoveRange>& points) const
{
    std::sort(points.begin(), points.end(), [](const TextRemoveRange& a, const TextRemoveRange& b)
    {
        return a.idx < b.idx;
    });
}

std::vector<TextMarkup::TextTagChange> TextMarkup::ParseTagChanges(const std::string& str) const
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

std::vector<TextTag> TextMarkup::ExtractTags(const std::vector<TextTagChange>& changes)
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

} // namespace txt
