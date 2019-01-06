/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "TxtFileReader.h"
#include "StringUtil.h"
#include <sstream>

namespace txt
{

TxtFileReader::TxtFileReader()
{
}

TxtFileReader::~TxtFileReader()
{
}

TxtInfo TxtFileReader::Read(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        TxtInfo info;
        info.meta_filename = GetMetaFile(file);
        info.story_points = GetStoryPoints(file);

        file.close();
        return info;
    }
    throw std::runtime_error("Could not open file!");
}

std::string TxtFileReader::GetMetaFile(std::ifstream& file)
{
    std::string line;
    std::string prefix = "Meta:";
    while (m_reader.NextLine(file, line))
    {
        if (line.compare(0, prefix.size(), prefix) == 0)
        {
            std::string metaFile = line.substr(prefix.size());
            txt::trim(metaFile);
            return metaFile;
        }
    }
    throw std::runtime_error("No Meta-field found!");
}

std::vector<StoryPoint> TxtFileReader::GetStoryPoints(std::ifstream& file)
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

StoryPoint TxtFileReader::CreateStoryPoint(const std::string& name, const std::string& txt) const
{
    std::string str = txt;
    txt::trim(str);
    txt::repl(str, " \n", "\n");

    StoryPoint point(name);
    point.SetTextStr(str);
    return point;
}

} // namespace txt
