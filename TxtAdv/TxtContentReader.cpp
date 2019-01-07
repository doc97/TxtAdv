/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "TxtContentReader.h"
#include "StringUtil.h"
#include <fstream>

namespace txt
{

TxtContentReader::TxtContentReader()
{
}

TxtContentReader::~TxtContentReader()
{
}

TxtContentInfo TxtContentReader::Read(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Could not open file!");

    TxtContentInfo info = Read(file);
    file.close();
    return info;
}

TxtContentInfo TxtContentReader::Read(std::istream& stream)
{
    TxtContentInfo info;
    if (!GetKeyValue(stream, "Meta", info.ctrl_filename, false))
        throw std::runtime_error("FileFormatError: No Meta-field found!");
    GetKeyValue(stream, "Style", info.style_filename, true);
    info.story_points = GetStoryPoints(stream);
    return info;
}

bool TxtContentReader::GetKeyValue(std::istream& file, const std::string& key, std::string& value, bool oneline)
{
    std::string line;
    std::string prefix = key + ":";
    while (m_reader.NextLine(file, line))
    {
        if (line.compare(0, prefix.size(), prefix) == 0)
        {
            value = line.substr(prefix.size());
            txt::trim(value);
            return true;
        }
        if (oneline)
            break;
    }
    return false;
}

std::vector<StoryPoint> TxtContentReader::GetStoryPoints(std::istream& file)
{
    bool hasStarted = false;
    std::string line;
    std::vector<StoryPoint> points;

    std::stringstream ss;
    std::string pointName;
    while (m_reader.NextLine(file, line))
    {
        if (hasStarted)
        {
            if (line.empty())
                ss << "\n";
            else if (line.compare(0, 4, "    ") == 0)
                ss << line.substr(4) << " ";
            else if (line.find("Story:") != std::string::npos)
            {
                points.push_back(CreateStoryPoint(pointName, ss.str()));

                pointName = txt::trim_copy(line.substr(6));
                ss.str("");
                ss.clear();
            }
        }
        else if (line.find("Story:") != std::string::npos)
        {
            pointName = txt::trim_copy(line.substr(6));
            hasStarted = true;
        }
    }
    points.push_back(CreateStoryPoint(pointName, ss.str()));

    return points;
}

StoryPoint TxtContentReader::CreateStoryPoint(const std::string& name, const std::string& txt) const
{
    std::string str = txt;
    txt::trim(str);
    txt::repl(str, " \n", "\n");

    StoryPoint point(name);
    point.SetTextStr(str);
    return point;
}

} // namespace txt
