/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include <vector>

namespace txt
{

/* Enum: Styles
 * Bit mask constants used to switch on/off text styles.
 *
 *    NORMAL - No style
 *    ITALIC - Italics style active
 *    BOLD - Bold style active
 *    UNDERL - Underline style active
 *    STRIKE - Strikethrough style active
 *    ALL - All of the styles active
 *
 * Examples:
 * === C++ ===
 * unsigned char style = Styles::NORMAL;
 * style ^= Styles::ITALIC; // Toggle italics
 * style ^= Styles::BOLD; // Toggle bold - both italics and bold are active
 * ===========
 */
enum Styles
{
    NORMAL = 0x00,
    ITALIC = 0x01,
    BOLD   = 0x02,
    UNDERL = 0x04,
    STRIKE = 0x08,
    ALL    = 0xF0
};

/* Struct: TextStyle
 * A POD-struct representing a text style.
 *
 * See Also:
 *
 *    <Styles>
 */
struct TextStyle
{
    size_t start = 0;
    size_t len = 0;
    unsigned char style = Styles::NORMAL;
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
     * Get the parsed styles from the markup text given to the constructor.
     *
     * The vector is ordered and continuous in that sense that each part of
     * the string is mapped to some style. E.g.
     *
     * '*Hey* _cutie_': [0,2] ('Hey') is in bold, [3,4] (' ') is normal,
     * [5,9] ('cutie') is in italics.
     *
     * Returns:
     *
     *    The styles generated from the markup text.
     *
     * See Also:
     *
     *    <TextStyle>
     */
    std::vector<TextStyle> GetStyles() const;
private:
    struct TextStyleChange
    {
        size_t idx = 0;
        size_t style_len = 1;
        unsigned char style_mask = Styles::NORMAL;
    };

    std::string m_raw;
    std::string m_str;
    std::vector<TextStyle> m_styles;

    std::string Parse(const std::string& raw);
    std::vector<TextStyleChange> ParseStyles(const std::string& str) const;
    std::vector<TextStyleChange> ParseStyle(const std::string& str, const std::string& styleId,
        Styles style) const;
    void CombineStyles(std::vector<TextStyleChange>& orig, const std::vector<TextStyleChange>& append) const;
    void SortChanges(std::vector<TextStyleChange>& changes) const;
    void RemoveMarkupCharacters(std::string& str, std::vector<TextStyleChange>& changes) const;
    std::vector<TextStyle> ExtractStyles(const std::vector<TextStyleChange>& changes, const size_t strLen) const;
    std::vector<TextStyle> CompressStyles(const std::vector<TextStyle>& styles) const;
};

} // namespace txt
