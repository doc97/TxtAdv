/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "FileLineReader.h"

namespace txt
{

FileLineReader::FileLineReader()
{
}

FileLineReader::~FileLineReader()
{
}

bool FileLineReader::NextLine(std::ifstream& file, std::string& line)
{
    if (!file.is_open())
        return false;
    while (std::getline(file, line))
    {
        if (HandleMultilineComment(line) && HandleSinglelineComment(line))
            return true;
    }
    return false;
}

bool FileLineReader::HandleMultilineComment(std::string& line)
{
    std::string tmpLine;
    size_t commentStart = 0;
    if (!m_isComment)
    {
        if ((commentStart = line.find("/*")) != std::string::npos)
        {
            m_isComment = true;
            if (commentStart == 0)
                return false;
            tmpLine = line.substr(0, commentStart);
        }
    }

    if (m_isComment)
    {
        size_t commentEnd;
        if ((commentEnd = line.find("*/", commentStart)) != std::string::npos)
        {
            m_isComment = false;
            if (commentEnd < line.length() - 2)
                tmpLine += line.substr(commentEnd + 2);
            else
                return false;
        }
    }

    if (!tmpLine.empty())
        line = tmpLine;
    return !m_isComment;
}

bool FileLineReader::HandleSinglelineComment(std::string& line)
{
    size_t commentStart;
    if ((commentStart = line.find("//")) != std::string::npos)
    {
        if (commentStart == 0)
            return false;
        line = line.substr(0, commentStart);
    }
    return true;
}

} // namespace txt
