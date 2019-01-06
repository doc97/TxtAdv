/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <unordered_map>
#include "FileLineReader.h"
#include "TextStyleSheet.h"

namespace txt
{

class StyleFileReader
{
public:
    StyleFileReader();
    ~StyleFileReader();

    /* Function: Read
     *
     * Parameters:
     *
     *    filename - Path to the file to read
     *
     * Returns:
     *
     *    The data in the form of a <StyleInfo> object
     *
     * Throws:
     *
     *    std::runtime_error if there is an error such as file format error or I/O error
     */
    TextStyleSheet Read(const std::string& filename);
private:
    FileLineReader m_reader;

    TextStyleSheet GetTextStyleSheet(std::ifstream& file);
    TextStyle GetTextStyle(std::ifstream& file);
    void SetTextStyleAttribute(TextStyle& style, const std::string& name, const std::string& value) const;
    void SetSizeAttribute(TextStyle& style, const std::string& value) const;
    void SetEmphasisAttribute(TextStyle& style, const std::string& value) const;
    void SetOutlineColorAttribute(TextStyle& style, const std::string& value) const;
    void SetFillColorAttribute(TextStyle& style, const std::string& value) const;
    void SetBgColorAttribute(TextStyle& style, const std::string& value) const;
};

} // namespace txt
