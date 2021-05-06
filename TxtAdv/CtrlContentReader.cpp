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
        if (line.empty())
            continue;
        std::vector<std::string> data = txt::split(line, ',');
        if (data.size() != 4)
            throw std::runtime_error("Invalid data format in .ctrl file!");
        for_each(data.begin(), data.end(), txt::trim);

        CtrlContent ctrl_content;
        ctrl_content.storypoint = data[0];
        ctrl_content.script = data[1];
        ctrl_content.matcher_func = data[2];
        ctrl_content.action_func = data[3];

        if (ctrl_content.storypoint.empty())
            throw std::runtime_error("StoryPoint ID-field cannot be left empty");
        if (ctrl_content.script.empty() || ctrl_content.matcher_func.empty() || ctrl_content.action_func.empty())
            continue;

        info.ctrl_content[ctrl_content.storypoint].push_back(ctrl_content);
    }
    return info;
}

} // namespace txt
