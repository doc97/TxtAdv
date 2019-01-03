/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "Text.h"
#include <algorithm>
#include <cctype>

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

std::string Text::Parse(const std::string& raw)
{
    std::string res = raw;
    std::vector<TextEmphasisChange> emphasis = ParseEmphasisChanges(res);
    std::vector<TextMetadataChange> metadata = ParseMetadataChanges(res);

    SortEmphasisChanges(emphasis);
    SortMetadataChanges(metadata);

    RemoveMarkupCharacters(res, emphasis, metadata);

    m_emphasis = ExtractEmphasisStyles(emphasis, res.length());
    m_emphasis = CompressEmphasisStyles(m_emphasis);

    m_metadata = ExtractMetadata(metadata, res.length());
    m_metadata = CompressMetadata(m_metadata);
    return res;
}

void Text::RemoveMarkupCharacters(std::string& str,
    std::vector<TextEmphasisChange>& emphasisChanges,
    std::vector<TextMetadataChange>& metadataChanges) const
{
    std::vector<TextEmphasisChange>::iterator emIt = emphasisChanges.begin();
    std::vector<TextMetadataChange>::iterator mdIt = metadataChanges.begin();
    size_t lastEmIdx = SIZE_MAX;
    size_t lastMdIdx = SIZE_MAX;
    size_t charsRemoved = 0;

    do
    {
        size_t emIdx = SIZE_MAX;
        size_t mdIdx = SIZE_MAX;
        if (emIt != emphasisChanges.end())
            emIdx = emIt->idx;
        if (mdIt != metadataChanges.end())
            mdIdx = mdIt->idx;

        if (emIdx < mdIdx)
        {
            if (lastEmIdx == emIdx)
                continue;
            lastEmIdx = emIdx;
            emIt->idx -= charsRemoved;
            charsRemoved += emIt->style_len;
            str.erase(emIt->idx, emIt->style_len);

            ++emIt;
        }
        else if (mdIdx < emIdx)
        {
            if (lastMdIdx == mdIdx)
                continue;
            lastMdIdx = mdIdx;
            mdIt->idx -= charsRemoved;
            charsRemoved += mdIt->len;
            str.erase(mdIt->idx, mdIt->len);

            ++mdIt;
        }

    } while (emIt != emphasisChanges.end() || mdIt != metadataChanges.end());
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

    changes.reserve(sizeChanges.size());
    CombineMetadataChanges(changes, sizeChanges);
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

void Text::RemoveMarkupCharacters(std::string& str, std::vector<TextMetadataChange>& changes) const
{
    std::vector<TextMetadataChange>::iterator it = changes.begin();
    size_t i = 0;
    size_t lastIdx = SIZE_MAX;
    for (size_t i = 0; it != changes.end(); ++it)
    {
        if (lastIdx == it->idx)
            continue;
        lastIdx = it->idx;
        it->idx -= i;
        i += it->len;
        str.erase(it->idx, it->len);
    }
}

std::vector<TextMetadata> Text::ExtractMetadata(const std::vector<TextMetadataChange>& changes,
    const size_t strLen) const
{
    std::vector<TextMetadata> metadata;
    size_t start = 0;
    TextSize size = TextSize::S1;
    for (auto it = changes.begin(); it != changes.end(); ++it)
    {
        size_t len = it->idx - start;
        if (len > 0)
        {
            TextMetadata data;
            data.start = start;
            data.len = len;
            data.size = size;
            metadata.push_back(data);
        }

        if (it->changeMask[MetadataChangeBits::SIZE_CHANGE])
            size = it->data.size;
        start = it->idx;
    }
    size_t len = strLen - start;
    if (len > 0)
    {
        TextMetadata data;
        data.start = start;
        data.len = len;
        data.size = size;
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
        if (cur->size == lastMetadata.size)
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

} // namespace txt
