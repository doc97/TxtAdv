/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include <vector>

namespace txt
{

enum Styles
{
    NORMAL = 0x00,
    ITALIC = 0x01,
    BOLD   = 0x02,
    UNDERL = 0x04,
    STRIKE = 0x08,
    ALL    = 0xF0
};

struct TextStyle
{
    size_t start = 0;
    size_t len = 0;
    unsigned char style = Styles::NORMAL;
};

struct TextStyleChange
{
    size_t idx = 0;
    size_t style_len = 1;
    unsigned char style_mask = Styles::NORMAL;
};

class Text
{
public:
    Text(const std::string& text);
    ~Text();

    std::string Str() const;
    std::string RawStr() const;
    std::vector<TextStyle> GetStyles() const;
private:
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
