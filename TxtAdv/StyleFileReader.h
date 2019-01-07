/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <unordered_map>
#include "LineReader.h"
#include "TextStyleSheet.h"

namespace txt
{

class StyleFileReader
{
public:
    StyleFileReader();
    ~StyleFileReader();

    /* Function: Read
     * Reads the input from a file and parses the content.
     *
     * Parameters:
     *
     *    filename - Path to the file to read
     *
     * Returns:
     *
     *    The data in the form of a <TextStyleSheet> object
     *
     * Throws:
     *
     *    std::runtime_error if there is an I/O error and the file could not be opened
     *    std::invalid_argument if there is a color format error
     */
    TextStyleSheet Read(const std::string& filename);

    /* Function: Read
     * Reads an input stream and parses the content.
     *
     * Parameters:
     *
     *    stream - The stream to read
     *
     * Returns:
     *
     *    The parsed data in the form of a <TextStyleSheet> object
     *
     * Throws:
     *
     *    std::invalid_argument if there is a color format error
     */
    TextStyleSheet Read(std::istream& stream);
private:
    LineReader m_reader;

    TextStyle GetTextStyle(std::istream& stream);
    void SetTextStyleAttribute(TextStyle& style, const std::string& name, const std::string& value) const;
    void SetSizeAttribute(TextStyle& style, const std::string& value) const;
    void SetEmphasisAttribute(TextStyle& style, const std::string& value) const;
    void SetOutlineColorAttribute(TextStyle& style, const std::string& value) const;
    void SetFillColorAttribute(TextStyle& style, const std::string& value) const;
    void SetBgColorAttribute(TextStyle& style, const std::string& value) const;
};

} // namespace txt
