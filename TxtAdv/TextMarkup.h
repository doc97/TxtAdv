/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "Text.h"

namespace txt
{

/* Class: TextMarkup
 * Handles text markup parsing, the result is a <Text>.
 */
class TextMarkup
{
public:
    /* Constructor: TextMarkup
     *
     * Parameters:
     *
     *    raw - The raw markup text
     */
    TextMarkup(const std::string& raw);
    ~TextMarkup();

    /* Function: GetText
     *
     * Returns:
     *
     *    The parsed <Text> object
     */
    Text GetText() const;
private:
    Text m_text;

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
        std::bitset<MetadataChangeBits::CHANGE_BIT_COUNT> changeMask;
    };

    struct TextTagChange
    {
        size_t idx = 0;
        size_t len = 0;
        std::string name;
    };

    void Parse(const std::string& raw);
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

    /* Metadata */
    std::vector<TextMetadataChange> ParseMetadataChanges(const std::string& str) const;
    std::vector<TextMetadataChange> ParseSizeChanges(const std::string& str) const;
    std::vector<TextMetadataChange> ParseColorChanges(const std::string& str) const;
    void CombineMetadataChanges(std::vector<TextMetadataChange>& orig,
        const std::vector<TextMetadataChange>& append) const;
    void SortMetadataChanges(std::vector<TextMetadataChange>& changes) const;
    std::vector<TextMetadata> ExtractMetadata(const std::vector<TextMetadataChange>& changes,
        const size_t strLen) const;

    /* Remove ranges */
    std::vector<TextRemoveRange> ParseRemoveRanges(const std::string& str) const;
    std::vector<TextRemoveRange> ParseEscapeSequences(const std::string& str) const;
    void CombineRemoveRanges(std::vector<TextRemoveRange>& orig,
        const std::vector<TextRemoveRange>& append) const;
    void SortRemoveRanges(std::vector<TextRemoveRange>& points) const;

    /* Tags */
    std::vector<TextTagChange> ParseTagChanges(const std::string& str) const;
    std::vector<TextTag> ExtractTags(const std::vector<TextTagChange>& changes);
};

} // namespace txt
