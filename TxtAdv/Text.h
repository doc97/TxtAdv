/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <bitset>
#include <string>
#include <vector>

namespace txt
{

/* Enum: Emphasis
 * Bit mask constants used to switch on/off text emphasis styles.
 *
 *    NONE - No emphasis
 *    ITALIC - Italics emphasis active
 *    BOLD - Bold emphasis active
 *    UNDERL - Underline emphasis active
 *    STRIKE - Strikethrough emphasis active
 *    ALL - All of the emphasis styles active
 *
 * Examples:
 * === C++ ===
 * unsigned char emphasis = Emphasis::NONE;
 * emphasis ^= Emphasis::ITALIC; // Toggle italics
 * emphasis ^= Emphasis::BOLD; // Toggle bold - both italics and bold are active
 * ===========
 */
enum Emphasis
{
    NONE   = 0x00,
    ITALIC = 0x01,
    BOLD   = 0x02,
    UNDERL = 0x04,
    STRIKE = 0x08,
    ALL    = 0x0F,
};

/* Enum: EmphasisBits
 * Constants referring to the bit indices in the emphasis bit mask.
 *
 *    ITALIC_BIT - The first bit
 *    BOLD_BIT - The second bit
 *    UNDERL_BIT - The third bit
 *    STRIKE_BIT - The fourth bit
 *    BIT_COUNT - The bit count, used as the size of the bit mask
 *
 * See Also:
 *
 *    <Emphasis>
 *    <TextEmphasis>
 */
enum EmphasisBits
{
    ITALIC_BIT = 0,
    BOLD_BIT   = 1,
    UNDERL_BIT = 2,
    STRIKE_BIT = 3,
    BIT_COUNT  = 4
};

/* Enum: TextSize
 * Text sizes 1-5.
 *
 *    S1 - Size 1
 *    S2 - Size 2
 *    S3 - Size 3
 *    S4 - Size 4
 *    S5 - Size 5
 *    SIZE_COUNT - The number of text sizes, not to be used
 */
enum TextSize
{
    S1 = 0, S2, S3, S4, S5, SIZE_COUNT
};

/* Struct: Color
 * Represents a 32-bit RGBA color.
 */
struct Color
{
    unsigned char r = 0;
    unsigned char g = 0;
    unsigned char b = 0;
    unsigned char a = 0;
};

inline bool operator==(const Color& a, const Color& b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

/* Struct: TextEmphasis
 * A POD-struct representing a text style.
 *
 * See Also:
 *
 *    <Emphasis>
 */
struct TextEmphasis
{
    size_t start = 0;
    size_t len = 0;
    std::bitset<EmphasisBits::BIT_COUNT> bitmask;
};

/* Struct: TextMetadata
 * A POD-struct representing text metadata such as text size and color.
 */
struct TextMetadata
{
    size_t start = 0;
    size_t len = 0;
    TextSize size = TextSize::S1;
    Color color = { 0, 0, 0, 0 };
};

inline bool operator==(const TextMetadata& a, const TextMetadata& b)
{
    return a.size == b.size && a.color == b.color;
}

/* Struct: TextTag
 * A struct for representing a text tag.
 */
struct TextTag
{
    size_t start = 0;
    size_t len = 0;
    std::string name;
};

/* Class: Text
 * Represents stylized text.
 */
class Text
{
public:
    /* Constructor: Text
     * Parses the raw text into styles.
     *
     * Parameters:
     *
     *    text - The raw markup text
     */
    Text(const std::string& text);
    ~Text();

    /* Function: Str
     * Returns the cleaned text.
     *
     * Any markup symbols will be cleaned and removed from the string. To
     * do your own cleaning and/or parsing, you can use the <RawStr> function
     * to access the unmodified string.
     *
     * Returns:
     *
     *    The cleaned string
     */
    std::string Str() const;

    /* Function: RawStr
     * Return the string as it was when it was passed to the constructor.
     *
     * Returns:
     *
     *    The unmodified string
     */
    std::string RawStr() const;

    /* Function: GetStyles
     * Get the parsed emphasis styles from the markup text given to the constructor.
     *
     * The vector is ordered and continuous in that sense that each part of
     * the string is mapped to some style. E.g.
     *
     * '*Hey* _cutie_': [0,2] ('Hey') is in bold, [3,4] (' ') is normal,
     * [5,9] ('cutie') is in italics.
     *
     * Returns:
     *
     *    The emphasis styles generated from the markup text
     *
     * See Also:
     *
     *    <TextEmphasis>
     */
    std::vector<TextEmphasis> GetEmphasisStyles() const;

    /* Function: GetMetadata
     * Get the parsed text metadata from the markup text given to the constructor.
     *
     * The vector is ordered and continuous in that sense that each part of
     * the string is mapped to some metadata.
     *
     * Returns:
     *
     *    The text metadata generated from the markup text
     *
     * See Also:
     *
     *    <TextMetadata>
     */
    std::vector<TextMetadata> GetMetadata() const;

    /* Function: GetTags
     * Get the parsed text tags from the markup text given to the constructor.
     *
     * Returns:
     *
     *    The text tags generated from the markup text
     *
     * See Also:
     *
     *    <TextTag>
     */
    std::vector<TextTag> GetTags() const;
private:
    /* Enum: MetadataChangeBits
     * Bit mask constants used to mark metadata changes.
     *
     *    SIZE_CHANGE - Text size change
     *    COLOR_CHANGE - Text color change
     */
    enum MetadataChangeBits
    {
        SIZE_CHANGE = 0x00,
        COLOR_CHANGE = 0x01,
        CHANGE_COUNT = 0x02
    };

    /* Struct: TextRemoveRange
     * Represents a range in the string to remove.
     */
    struct TextRemoveRange
    {
        size_t idx = 0;
        size_t len = 0;
    };

    struct TextEmphasisChange
    {
        size_t idx = 0;
        size_t len = 1;
        std::bitset<EmphasisBits::BIT_COUNT> mask;
    };

    struct TextMetadataChange
    {
        size_t idx = 0;
        size_t len = 2;
        TextMetadata data;
        std::bitset<MetadataChangeBits::CHANGE_COUNT> changeMask;
    };

    struct TextTagChange
    {
        size_t idx = 0;
        size_t len = 0;
        std::string name;
    };

    std::string m_raw;
    std::string m_str;
    std::vector<TextEmphasis> m_emphasis;
    std::vector<TextMetadata> m_metadata;
    std::vector<TextTag> m_tags;

    std::string Parse(const std::string& raw);
    void RemoveMarkupCharacters(std::string& str,
        std::vector<TextEmphasisChange>& emphasisChanges,
        std::vector<TextMetadataChange>& metadataChanges,
        std::vector<TextRemoveRange>& removals,
        std::vector<TextTagChange>& tagChanges) const;

    /* Emphasis styles*/
    std::vector<TextEmphasisChange> ParseEmphasisChanges(const std::string& str) const;
    std::vector<TextEmphasisChange> ParseEmphasisChange(const std::string& str, const std::string& styleId,
        Emphasis emphasis) const;
    void CombineEmphasisChanges(std::vector<TextEmphasisChange>& orig,
        const std::vector<TextEmphasisChange>& append) const;
    void SortEmphasisChanges(std::vector<TextEmphasisChange>& changes) const;
    std::vector<TextEmphasis> ExtractEmphasisStyles(const std::vector<TextEmphasisChange>& changes,
        const size_t strLen) const;
    std::vector<TextEmphasis> CompressEmphasisStyles(const std::vector<TextEmphasis>& styles) const;

    /* Metadata */
    std::vector<TextMetadataChange> ParseMetadataChanges(const std::string& str) const;
    std::vector<TextMetadataChange> ParseSizeChanges(const std::string& str) const;
    std::vector<TextMetadataChange> ParseColorChanges(const std::string& str) const;
    void CombineMetadataChanges(std::vector<TextMetadataChange>& orig,
        const std::vector<TextMetadataChange>& append) const;
    void SortMetadataChanges(std::vector<TextMetadataChange>& changes) const;
    std::vector<TextMetadata> ExtractMetadata(const std::vector<TextMetadataChange>& changes,
        const size_t strLen) const;
    std::vector<TextMetadata> CompressMetadata(const std::vector<TextMetadata>& metadata) const;

    /* Remove ranges */
    std::vector<TextRemoveRange> ParseRemoveRanges(const std::string& str) const;
    std::vector<TextRemoveRange> ParseEscapeSequences(const std::string& str) const;
    void CombineRemoveRanges(std::vector<TextRemoveRange>& orig,
        const std::vector<TextRemoveRange>& append) const;
    void SortRemoveRanges(std::vector<TextRemoveRange>& points) const;

    /* Tags */
    std::vector<TextTagChange> ParseTagChanges(const std::string& str) const;
    std::vector<TextTag> ExtractTags(const std::vector<TextTagChange>& changes);
    std::vector<TextTag> CompressTags(const std::vector<TextTag>& tags) const;
};

} // namespace txt
