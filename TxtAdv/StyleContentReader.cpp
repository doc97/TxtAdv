/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "StyleContentReader.h"
#include "StringUtil.h"
#include <fstream>

namespace txt
{

StyleContentReader::StyleContentReader()
{
}


StyleContentReader::~StyleContentReader()
{
}

TextStyleSheet StyleContentReader::Read(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file!");

    TextStyleSheet tss = Read(file);
    file.close();
    return tss;
}

TextStyleSheet StyleContentReader::Read(std::istream& stream)
{
    TextStyleSheet tss;
    std::string line;
    std::string tag;
    while (m_reader.NextLine(stream, line))
    {
        if (std::isalpha(line.at(0)))
        {
            tag = line;
            TextStyle style = GetTextStyle(stream);
            tss.SetStyle(tag, style);
        }
    }
    return tss;
}

TextStyle StyleContentReader::GetTextStyle(std::istream& stream)
{
    TextStyle style;
    std::string line;
    while (m_reader.NextLine(stream, line))
    {
        // At least 2 space indentation
        if (line.compare(0, 2, "  ") == 0)
        {
            line = txt::trim_copy(line.substr(2));
            std::vector<std::string> data = txt::split(line, ':');
            std::string attrName = txt::trim_copy(data[0]);
            std::string attrValue = txt::trim_copy(data[1]);
            SetTextStyleAttribute(style, attrName, attrValue);
        }
        else
        {
            break;
        }
    }
    return style;
}

void StyleContentReader::SetTextStyleAttribute(TextStyle& style, const std::string& name, const std::string& value) const
{
    if (name == "size")
        SetSizeAttribute(style, value);
    else if (name == "emphasis")
        SetEmphasisAttribute(style, value);
    else if (name == "outline_color")
        SetOutlineColorAttribute(style, value);
    else if (name == "fill_color")
        SetFillColorAttribute(style, value);
    else if (name == "bg_color")
        SetBgColorAttribute(style, value);
}

void StyleContentReader::SetSizeAttribute(TextStyle& style, const std::string& value) const
{
    size_t size = std::stoi(value);

    // Size attribute ranges from 1 to 5
    if (size == 0 || size > 5)
        return;

    if (size == 1)
        style.size = TextSize::S1;
    else if (size == 2)
        style.size = TextSize::S2;
    else if (size == 3)
        style.size = TextSize::S3;
    else if (size == 4)
        style.size = TextSize::S4;
    else if (size == 5)
        style.size = TextSize::S5;
}

void StyleContentReader::SetEmphasisAttribute(TextStyle& style, const std::string& value) const
{
    style.bitmask = Emphasis::NONE;
    if (value.find("bold") != std::string::npos)
        style.bitmask ^= Emphasis::BOLD;
    if (value.find("italic") != std::string::npos)
        style.bitmask ^= Emphasis::ITALIC;
    if (value.find("underline") != std::string::npos)
        style.bitmask ^= Emphasis::UNDERL;
    if (value.find("strikethrough") != std::string::npos)
        style.bitmask ^= Emphasis::STRIKE;
}

void StyleContentReader::SetOutlineColorAttribute(TextStyle& style, const std::string& value) const
{
    if (value.at(0) != '#')
        throw std::invalid_argument("Argument is not a valid color, has to start with a '#'");
    if (value.length() > 9)
        throw std::invalid_argument("RGBA hex color string is too long");
    unsigned int color = txt::hex2int(value.substr(1));
    style.outline_color.r = (color & 0xFF000000) >> 24;
    style.outline_color.g = (color & 0x00FF0000) >> 16;
    style.outline_color.b = (color & 0x0000FF00) >> 8;
    style.outline_color.a = (color & 0x000000FF);
}

void StyleContentReader::SetFillColorAttribute(TextStyle& style, const std::string& value) const
{
    if (value.at(0) != '#')
        throw std::invalid_argument("Argument is not a valid color, has to start with a '#'");
    if (value.length() > 9)
        throw std::invalid_argument("RGBA hex color string is too long");
    unsigned int color = txt::hex2int(value.substr(1));
    style.fill_color.r = (color & 0xFF000000) >> 24;
    style.fill_color.g = (color & 0x00FF0000) >> 16;
    style.fill_color.b = (color & 0x0000FF00) >> 8;
    style.fill_color.a = (color & 0x000000FF);
}

void StyleContentReader::SetBgColorAttribute(TextStyle& style, const std::string& value) const
{
    if (value.at(0) != '#')
        throw std::invalid_argument("Argument is not a valid color, has to start with a '#'");
    if (value.length() > 9)
        throw std::invalid_argument("RGBA hex color string is too long");
    unsigned int color = txt::hex2int(value.substr(1));
    style.bg_color.r = (color & 0xFF000000) >> 24;
    style.bg_color.g = (color & 0x00FF0000) >> 16;
    style.bg_color.b = (color & 0x0000FF00) >> 8;
    style.bg_color.a = (color & 0x000000FF);
}

} // namespace txt
