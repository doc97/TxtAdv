/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include <vector>

namespace txt
{

/* Enum: Emphasis
 * Bit mask constants used to switch on/off text emphasis styles.
 *
 *    NORMAL - No emphasis
 *    ITALIC - Italics emphasis active
 *    BOLD - Bold emphasis active
 *    UNDERL - Underline emphasis active
 *    STRIKE - Strikethrough emphasis active
 *    ALL - All of the emphasis styles active
 *
 * Examples:
 * === C++ ===
 * unsigned char emphasis = Emphasis::NORMAL;
 * emphasis ^= Emphasis::ITALIC; // Toggle italics
 * emphasis ^= Emphasis::BOLD; // Toggle bold - both italics and bold are active
 * ===========
 */
enum Emphasis
{
    NORMAL = 0x00,
    ITALIC = 0x01,
    BOLD   = 0x02,
    UNDERL = 0x04,
    STRIKE = 0x08,
    ALL    = 0x0F
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
    unsigned char emphasis = Emphasis::NORMAL;
};

/* Struct: TextMetadata
 * A POD-struct representing text metadata.
 */
struct TextMetadata
{
    size_t start = 0;
    size_t len = 0;
    TextSize size = TextSize::S1;
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

    /* Function: GetTextData
     * Get the parsed text metadata from the markup text given to the constructor.
     *
     * The vector is ordered and continuous in that sense that each part of
     * the string is mapped to some metadata.
     *
     * Returns:
     *
     *    The text data generated from the markup text
     *
     * See Also:
     *
     *    <TextData>
     */
    std::vector<TextMetadata> GetMetadata() const;
private:
    struct TextEmphasisChange
    {
        size_t idx = 0;
        size_t style_len = 1;
        unsigned char mask = Emphasis::NORMAL;
    };
    struct TextMetadataChange
    {
        size_t idx = 0;
        size_t len = 2;
        TextMetadata data;
    };

    std::string m_raw;
    std::string m_str;
    std::vector<TextEmphasis> m_emphasis;
    std::vector<TextMetadata> m_metadata;

    std::string Parse(const std::string& raw);
    std::vector<TextEmphasisChange> ParseEmphasisStyles(std::string& str);
    std::vector<TextMetadataChange> ParseMetadata(std::string& str);

    /* Emphasis styles*/
    std::vector<TextEmphasisChange> ParseEmphasisChanges(const std::string& str) const;
    std::vector<TextEmphasisChange> ParseEmphasisChange(const std::string& str, const std::string& styleId,
        Emphasis emphasis) const;
    void CombineEmphasisChanges(std::vector<TextEmphasisChange>& orig,
        const std::vector<TextEmphasisChange>& append) const;
    void SortEmphasisChanges(std::vector<TextEmphasisChange>& changes) const;
    void RemoveMarkupCharacters(std::string& str, std::vector<TextEmphasisChange>& changes) const;
    std::vector<TextEmphasis> ExtractEmphasisStyles(const std::vector<TextEmphasisChange>& changes,
        const size_t strLen) const;
    std::vector<TextEmphasis> CompressEmphasisStyles(const std::vector<TextEmphasis>& styles) const;

    /* Metadata */
    std::vector<TextMetadataChange> ParseMetadataChanges(const std::string& str) const;
    std::vector<TextMetadataChange> ParseSizeChanges(const std::string& str) const;
    void CombineMetadataChanges(std::vector<TextMetadataChange>& orig,
        const std::vector<TextMetadataChange>& append) const;
    void RemoveMarkupCharacters(std::string& str, std::vector<TextMetadataChange>& changes) const;
    std::vector<TextMetadata> ExtractMetadata(const std::vector<TextMetadataChange>& changes,
        const size_t strLen) const;
    std::vector<TextMetadata> CompressMetadata(const std::vector<TextMetadata>& metadata) const;
};

} // namespace txt
