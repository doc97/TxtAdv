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
    Color outline_color = { 255, 255, 255, 255 };
    Color fill_color = { 255, 255, 255, 255 };
    Color bg_color = { 0, 0, 0, 0 };
};

inline bool operator==(const TextMetadata& a, const TextMetadata& b)
{
    return a.size == b.size && a.outline_color == b.outline_color && a.fill_color == b.fill_color && a.bg_color == b.bg_color;
}

/* Enum: MetadataChangeBits
 * Bit mask constants used to mark metadata changes.
 *
 *    SIZE_CHANGE_BIT - Text size change bit
 *    FILL_COLOR_CHANGE_BIT - Text fill color change bit
 *    OUT_COLOR_CHANGE_BIT - Text outline color change bit
 *    BG_COLOR_CHANGE_BIT - Text background color change bit
 *    ALL_CHANGED - Value used to set all bits to true
 */
enum MetadataChangeBits
{
    SIZE_CHANGE_BIT = 0,
    FILL_COLOR_CHANGE_BIT = 1,
    OUT_COLOR_CHANGE_BIT = 2,
    BG_COLOR_CHANGE_BIT = 3,
    CHANGE_BIT_COUNT = 4,
    ALL_CHANGED = 15,
};

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
     * Creates an empty text.
     */
    Text();

    /* Constructor: Text
     * Creates a styleless text.
     *
     * Parameters:
     *
     *    text - The text, without markup
     */
    Text(const std::string& text);

    /* Constructor: Text
     * Create text from the parameters.
     *
     * Parameters:
     *
     *    raw - The raw markup text
     *    text - The parsed text
     *    emphasis - The parsed emphasis styles
     *    metadata - The parsed metadata
     *    tags - The parsed tags
     */
    Text(const std::string& raw, const std::string& text,
        const std::vector<TextEmphasis> emphasis,
        const std::vector<TextMetadata> metadata,
        const std::vector<TextTag> tags);

    /* Constructor: Text
     * Copy constructor.
     *
     * Parameters:
     *
     *    other - The other text to copy
     */
    Text(const Text& other);

    ~Text();

    /* Function: SetEmphasisStyle
     * Sets an emphasis style for the range [start, start+len).
     *
     * Parameters:
     *
     *    start - The starting index, if < string length it throws std::out_of_range
     *    len - The length of the range, it is clamped to span to the end of the string
     *    mask - The style to set, overrides any existing style in [start, start + len)
     */
    void SetEmphasisStyle(size_t start, size_t len, std::bitset<EmphasisBits::BIT_COUNT> mask);

    /* Function: ToggleEmphasisStyle
     * Toggles an emphasis style for the range [start, start+len).
     *
     * Parameters:
     *
     *    start - The starting index, if < string length it throws std::out_of_range
     *    len - The length of the range, it is clamped to span to the end of the string
     *    mask - The style to toggle
     *
     * See Also:
     *
     *    <SetEmphasisStyle>
     */
    void ToggleEmphasisStyle(size_t start, size_t len, std::bitset<EmphasisBits::BIT_COUNT> mask);

    /* Function: SetMetadata
     * Sets metadata for the range [start, start+len).
     *
     * Parameters:
     *
     *    start - The start index, if < string length it throws std::out_of_range
     *    len - The length of the range, it is clamped to span to the end of the string
     *    size - The text size
     *    outline - The text outline color
     *    fill - The text fill color
     *    bg - The text background color
     *    changeMask - The bits decide which of the previous metadata gets applied
     */
    void SetMetadata(size_t start, size_t len, const TextSize& size,
        const Color& outline, const Color& fill, const Color& bg,
        const std::bitset<MetadataChangeBits::CHANGE_BIT_COUNT>& changeMask);

    /* Function: SetMetadataSize
     * Sets size metadata for the range [start, start+len).
     *
     * Parameters:
     *
     *    start - The start index, if < string length it throws std::out_of_range
     *    len - The length of the range, it is clamped to span to the end of the string
     *    size - The text size
     *
     * See Also:
     *
     *    <SetMetadata>
     */
    void SetMetadataSize(size_t start, size_t len, const TextSize& size);

    /* Function: SetMetadataOutlineColor
     * Sets text outline color metadata for the range [start, start+len).
     *
     * Parameters:
     *
     *    start - The start index, if < string length it throws std::out_of_range
     *    len - The length of the range, it is clamped to span to the end of the string
     *    outline - The text outline color
     *
     * See Also:
     *
     *    <SetMetadata>
     */
    void SetMetadataOutlineColor(size_t start, size_t len, const Color& outline);

    /* Function: SetMetadataFillColor
     * Sets text fill color metadata for the range [start, start+len).
     *
     * Parameters:
     *
     *    start - The start index, if < string length it throws std::out_of_range
     *    len - The length of the range, it is clamped to span to the end of the string
     *    fill - The text fill color
     *
     * See Also:
     *
     *    <SetMetadata>
     */
    void SetMetadataFillColor(size_t start, size_t len, const Color& fill);

    /* Function: SetMetadataBgColor
     * Sets text background color metadata for the range [start, start+len).
     *
     * Parameters:
     *
     *    start - The start index, if < string length it throws std::out_of_range
     *    len - The length of the range, it is clamped to span to the end of the string
     *    bg - The text background color
     *
     * See Also:
     *
     *    <SetMetadata>
     */
    void SetMetadataBgColor(size_t start, size_t len, const Color& bg);

    /* Function: CompressEmphasisStyles
     */
    void CompressEmphasisStyles();

    void CompressMetadata();

    void CompressTags();

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
    std::string m_raw;
    std::string m_str;
    std::vector<TextEmphasis> m_emphasis;
    std::vector<TextMetadata> m_metadata;
    std::vector<TextTag> m_tags;

    std::vector<TextEmphasis> CompressEmphasisStyles(const std::vector<TextEmphasis>& styles) const;
    std::vector<TextMetadata> CompressMetadata(const std::vector<TextMetadata>& metadata) const;
    std::vector<TextTag> CompressTags(const std::vector<TextTag>& tags) const;
};

} // namespace txt
