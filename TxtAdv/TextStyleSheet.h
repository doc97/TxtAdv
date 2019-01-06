/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "Text.h"
#include <unordered_map>

namespace txt
{

struct TextStyle
{
    TextSize size = TextSize::S1;
    Color outline_color = { 255, 255, 255, 255 };
    Color fill_color = { 255, 255, 255, 255 };
    Color bg_color = { 0, 0, 0, 0 };
    std::bitset<EmphasisBits::BIT_COUNT> bitmask;
};

inline bool operator==(const TextStyle& a, const TextStyle& b)
{
    return a.size == b.size && a.outline_color == b.outline_color && a.fill_color == b.fill_color &&
        a.bg_color == b.bg_color && a.bitmask == b.bitmask;
}

class TextStyleSheet
{
public:
    TextStyleSheet();
    ~TextStyleSheet();

    /* Function: Apply
     * Applies this style sheet to the tags in the text.
     *
     * Parameters:
     *
     *    text - The text to apply the styles on
     */
    void Apply(Text& text) const;

    /* Function: SetStyle
     *
     * Parameters:
     *
     *    tag - The tag name to bind the style to
     *    style - The style
     *
     * See Also:
     *
     *    <TextStyle>
     */
    void SetStyle(const std::string& tag, const TextStyle& style);

    /* Function: UnsetStyle
     *
     * Parameters:
     *
     *    tag - The tag name to unbind the style from
     *
     * See Also:
     *
     *    <TextStyle>
     */
    void UnsetStyle(const std::string& tag);

    /* Function: HasStyle
     *
     * Parameters:
     *
     *    tag - The tag name to search for
     *
     * Returns:
     *
     *    true if the style has been set, false otherwise
     */
    bool HasStyle(const std::string& tag) const;

    /* Function: GetStyle
     * Get the style bound to the tag name, if not found, it returns a <TextStyle> with default values.
     *
     * Parameters:
     *
     *    tag - The tag name to search for
     *
     * Returns:
     *
     *    A text style, use <HasStyle> to see if a style exists
     *
     * See Also:
     *
     *    <TextStyle>
     */
    TextStyle GetStyle(const std::string& tag) const;
private:
    std::unordered_map<std::string, TextStyle> m_styles;
};

} // namespace txt
