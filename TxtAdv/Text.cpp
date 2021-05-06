/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "Text.h"
#include <algorithm>
#include "TextMarkup.h"

namespace txt
{

Text::Text()
    : Text("")
{
}

Text::Text(const std::string& text)
    : m_raw(text), m_str(text)
{
    TextEmphasis emphasis;
    emphasis.len = text.length();
    m_emphasis.push_back(emphasis);

    TextMetadata metadata;
    metadata.len = text.length();
    m_metadata.push_back(metadata);
}

Text::Text(const std::string& raw, const std::string& text,
    const std::vector<TextEmphasis> emphasis,
    const std::vector<TextMetadata> metadata,
    const std::vector<TextTag> tags)
    : m_raw(raw), m_str(text), m_emphasis(emphasis), m_metadata(metadata), m_tags(tags)
{
}

Text::Text(const Text& other)
    : m_raw(other.m_raw), m_str(other.m_str),
    m_emphasis(other.m_emphasis), m_metadata(other.m_metadata), m_tags(other.m_tags)
{
}

Text::~Text()
{
}

void Text::SetEmphasisStyle(size_t start, size_t len, std::bitset<EmphasisBits::BIT_COUNT> mask)
{
    /* Description:
    * 
    * Replace 'middle' with 'mask'. Might shrink the size of 'L' and 'R'
    * if 'mask' is bigger than 'middle'.
    *
    * Invariants:
    *    - start <= x0
    *    - len >= x1 - x0
    *    - L is guaranteed to exist
    *
    * Start:
    *
    *             x0              x1
    *       +-----+---------------+-----+
    *       |  L  |    middle     |  R  |
    *   - - o - - o - - - o - - - o - - o - -
    *       ^                           ^
    *       |                           |
    *
    *  lower bound                 upper bound
    *
    * Result:
    *
    *          left       mask     right
    *   - - o - - - - o - - - - o - - - - o - -
    *       ^         ^         ^         ^
    *       |         |         |         |
    *
    *  lower bound  start  start+len  upper bound
    */

    if (start >= m_str.length())
        throw std::out_of_range("start is out of range");
    if (len == 0)
        return;

    len = std::min(m_str.length() - start, len);

    // Reserve to avoid reallocation which destroys iterators
    m_emphasis.reserve(m_emphasis.size() + 2);

    TextEmphasis emphasis;
    emphasis.start = start;
    emphasis.len = len;
    emphasis.bitmask = mask;

    std::vector<TextEmphasis>::iterator lower, upper;
    lower = std::lower_bound(m_emphasis.begin(), m_emphasis.end(), emphasis,
        [](const TextEmphasis& a, const TextEmphasis& emphasis) { return a.start <= emphasis.start; });
    upper = std::upper_bound(m_emphasis.begin(), m_emphasis.end(), emphasis,
        [](const TextEmphasis& emphasis, const TextEmphasis& b) { return emphasis.start + emphasis.len < b.start; });

    /* std::lower_bound gives the element NOT "less" than the element to compare to,
     * decrement to get previous. If there is no such element, std::lower_bound
     * returns the m_emphasis.end().
     *
     * m_emphasis is guaranteed to have at least one element so decrementing m_emphasis.end()
     * is safe.
     */
    --lower;

    size_t toRemove = 0;
    std::bitset<EmphasisBits::BIT_COUNT> rightMask = lower->bitmask;
    std::vector<TextEmphasis>::iterator middle = lower + 1;

    // Traverse forward until reaching the last element BEFORE 'upper'
    while (middle != upper)
    {
        rightMask = middle->bitmask;
        ++middle;
        ++toRemove;
    }

    // The index of the upper style, or the end of the string if there is no upper style.
    size_t upperBound = (upper == m_emphasis.end() ? m_str.length() : upper->start);

    TextEmphasis left, right;

    left.start = lower->start;
    left.len = emphasis.start - left.start;
    left.bitmask = lower->bitmask;

    right.start = emphasis.start + emphasis.len;
    right.len = upperBound - right.start;
    right.bitmask = rightMask;

    // Replace the leftmost style and insert the modified after it (see removal below)
    size_t offset = 0;
    if (left.len > 0)
    {
        *lower = left;
        m_emphasis.insert(lower + ++offset, emphasis);
    }
    else
    {
        *lower = emphasis;
    }
    if (right.len > 0)
        m_emphasis.insert(lower + ++offset, right);

    // Remove the middle styles that was just overwritten by 'emphasis' and 'right'
    std::vector<TextEmphasis>::iterator remover = lower + ++offset;
    for (size_t i = 0; i < toRemove && remover != m_emphasis.end(); ++i)
        remover = m_emphasis.erase(remover);

    CompressEmphasisStyles();
}

void Text::ToggleEmphasisStyle(size_t start, size_t len, std::bitset<EmphasisBits::BIT_COUNT> mask)
{
    TextEmphasis emphasis;
    emphasis.start = start;
    emphasis.len = len;
    emphasis.bitmask = mask;

    // Reserve to avoid reallocation which destroys iterators
    m_emphasis.reserve(m_emphasis.size() + 1);

    std::vector<TextEmphasis>::iterator lower, upper;
    lower = std::lower_bound(m_emphasis.begin(), m_emphasis.end(), emphasis,
        [](const TextEmphasis& a, const TextEmphasis& emphasis) { return a.start <= emphasis.start; });
    upper = std::upper_bound(m_emphasis.begin(), m_emphasis.end(), emphasis,
        [](const TextEmphasis& emphasis, const TextEmphasis& b) { return emphasis.start + emphasis.len < b.start; });

    /* std::lower_bound gives the element NOT "less" than the element to compare to,
     * decrement to get previous. If there is no such element, std::lower_bound
     * returns the m_emphasis.end().
     *
     * m_emphasis is guaranteed to have at least one element so decrementing m_emphasis.end()
     * is safe.
     */
    --lower;

    std::vector<TextEmphasis>::iterator cur = lower;
    std::vector<TextEmphasis>::iterator next = cur + 1;
    bool lowerIsLast = next == m_emphasis.end();
    size_t lowerLen = (lowerIsLast ? len : next->start - start);
    std::bitset<EmphasisBits::BIT_COUNT> lowerMask = lower->bitmask ^ mask;

    if (!lowerIsLast)
    {
        size_t end = start + len;
        ++cur;
        while (++next != m_emphasis.end() && next->start < end)
            (cur++)->bitmask ^= mask;

        SetEmphasisStyle(cur->start, end - cur->start, cur->bitmask ^ mask);
    }

    SetEmphasisStyle(start, lowerLen, lowerMask);
}

void Text::SetMetadata(size_t start, size_t len, const TextSize& size,
    const Color& outline, const Color& fill, const Color& bg,
    const std::bitset<MetadataChangeBits::CHANGE_BIT_COUNT>& changeMask)
{
    if (start >= m_str.length())
        throw std::out_of_range("start is out of range");
    if (len == 0)
        return;

    len = std::min(m_str.length() - start, len);

    // Reserve to avoid reallocation which destroys iterators
    m_metadata.reserve(m_metadata.size() + 2);

    TextMetadata metadata;
    metadata.start = start;
    metadata.len = len;

    std::vector<TextMetadata>::iterator lower, upper;
    lower = std::lower_bound(m_metadata.begin(), m_metadata.end(), metadata,
        [](const TextMetadata& a, const TextMetadata& metadata) { return a.start <= metadata.start; });
    upper = std::upper_bound(m_metadata.begin(), m_metadata.end(), metadata,
        [](const TextMetadata& metadata, const TextMetadata& b) { return metadata.start + metadata.len < b.start; });

    /* std::lower_bound gives the element NOT "less" than the element to compare to,
     * decrement to get previous. If there is no such element, std::lower_bound
     * returns the m_emphasis.end().
     *
     * m_emphasis is guaranteed to have at least one element so decrementing m_emphasis.end()
     * is safe.
     */
    --lower;

    metadata.size = changeMask[MetadataChangeBits::SIZE_CHANGE_BIT] ? size : lower->size;
    metadata.outline_color = changeMask[MetadataChangeBits::OUT_COLOR_CHANGE_BIT] ? outline : lower->outline_color;
    metadata.fill_color = changeMask[MetadataChangeBits::FILL_COLOR_CHANGE_BIT] ? fill : lower->fill_color;
    metadata.bg_color = changeMask[MetadataChangeBits::BG_COLOR_CHANGE_BIT] ? bg : lower->bg_color;

    size_t toRemove = 0;
    TextSize rightSize = lower->size;
    Color rightOutColor = lower->outline_color;
    Color rightFillColor = lower->fill_color;
    Color rightBgColor = lower->bg_color;
    std::vector<TextMetadata>::iterator middle = lower + 1;

    // Traverse forward until reaching the last element BEFORE 'upper'
    while (middle != upper)
    {
        rightSize = middle->size;
        rightOutColor = middle->outline_color;
        rightFillColor = middle->fill_color;
        rightBgColor = middle->bg_color;
        ++middle;
        ++toRemove;
    }

    // The index of the upper style, or the end of the string if there is no upper style.
    size_t upperBound = (upper == m_metadata.end() ? m_str.length() : upper->start);

    TextMetadata left, right;

    left.start = lower->start;
    left.len = metadata.start - left.start;
    left.size = lower->size;
    left.outline_color = lower->outline_color;
    left.fill_color = lower->fill_color;
    left.bg_color = lower->bg_color;

    right.start = metadata.start + metadata.len;
    right.len = upperBound - right.start;
    right.size = rightSize;
    right.outline_color = rightOutColor;
    right.fill_color = rightFillColor;
    right.bg_color = rightBgColor;

    // Replace the leftmost metadata and insert the modified after it (see removal below)
    size_t offset = 0;
    if (left.len > 0)
    {
        *lower = left;
        m_metadata.insert(lower + ++offset, metadata);
    }
    else
    {
        *lower = metadata;
    }
    if (right.len > 0)
        m_metadata.insert(lower + ++offset, right);

    // Remove the middle metadata that was just overwritten by 'metadata' and 'right'
    std::vector<TextMetadata>::iterator remover = lower + ++offset;
    for (size_t i = 0; i < toRemove && remover != m_metadata.end(); ++i)
        remover = m_metadata.erase(remover);

    CompressMetadata();
}

void Text::SetMetadataSize(size_t start, size_t len, const TextSize& size)
{
    std::bitset<MetadataChangeBits::CHANGE_BIT_COUNT> mask;
    mask.set(MetadataChangeBits::SIZE_CHANGE_BIT, true);
    Color notused = { 0, 0, 0, 0 };
    SetMetadata(start, len, size, notused, notused, notused, mask);
}

void Text::SetMetadataOutlineColor(size_t start, size_t len, const Color& outline)
{
    std::bitset<MetadataChangeBits::CHANGE_BIT_COUNT> mask;
    mask.set(MetadataChangeBits::OUT_COLOR_CHANGE_BIT, true);
    Color notused = { 0, 0, 0, 0 };
    SetMetadata(start, len, TextSize::S1, outline, notused, notused, mask);
}

void Text::SetMetadataFillColor(size_t start, size_t len, const Color& fill)
{
    std::bitset<MetadataChangeBits::CHANGE_BIT_COUNT> mask;
    mask.set(MetadataChangeBits::FILL_COLOR_CHANGE_BIT, true);
    Color notused = { 0, 0, 0, 0 };
    SetMetadata(start, len, TextSize::S1, notused, fill, notused, mask);
}

void Text::SetMetadataBgColor(size_t start, size_t len, const Color& bg)
{
    std::bitset<MetadataChangeBits::CHANGE_BIT_COUNT> mask;
    mask.set(MetadataChangeBits::BG_COLOR_CHANGE_BIT, true);
    Color notused = { 0, 0, 0, 0 };
    SetMetadata(start, len, TextSize::S1, notused, notused, bg, mask);
}

void Text::CompressEmphasisStyles()
{
    m_emphasis = CompressEmphasisStyles(m_emphasis);
}

void Text::CompressMetadata()
{
    m_metadata = CompressMetadata(m_metadata);
}

void Text::CompressTags()
{
    m_tags = CompressTags(m_tags);
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
        if (cur->len == 0)
            continue;

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
        if (cur->len == 0)
            continue;

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
        if (cur->len == 0)
            continue;

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
