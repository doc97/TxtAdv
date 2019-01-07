/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "CtrlContentReader.h"
#include <fstream>
#include "StringUtil.h"

namespace txt
{

CtrlContentReader::CtrlContentReader()
{
}


CtrlContentReader::~CtrlContentReader()
{
}

CtrlContentInfo CtrlContentReader::Read(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file!");

    CtrlContentInfo info = Read(file);
    file.close();
    return info;
}

CtrlContentInfo CtrlContentReader::Read(std::istream& stream)
{
    CtrlContentInfo info;
    std::string line;
    while (m_reader.NextLine(stream, line))
    {
        std::vector<std::string> data = txt::split(line, ',');
        if (data.size() != 4)
            throw std::runtime_error("Invalid data format in .meta file!");
        for_each(data.begin(), data.end(), txt::trim);

        CtrlContent metadata;
        metadata.storypoint = data[0];
        metadata.script = data[1];
        metadata.matcher_func = data[2];
        metadata.action_func = data[3];

        info.metadata[metadata.storypoint].push_back(metadata);
    }
    return info;
}

} // namespace txt
