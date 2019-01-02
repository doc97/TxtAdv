/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "StoryLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "StringUtil.h"

namespace txt
{

StoryLoader::StoryLoader()
{
}

StoryLoader::~StoryLoader()
{
}

std::vector<StoryPoint> StoryLoader::Load(const std::string& filename) const
{
    std::ifstream file(filename.c_str());
    if (file.is_open())
    {
        std::string metaFile = GetMetaFile(file);
        std::vector<StoryPoint> ret = GetStoryPoints(file);
        file.close();
        return ret;
    }
    throw std::runtime_error("No such file exists!");
}

std::string StoryLoader::GetMetaFile(std::ifstream& file) const
{
    std::string line;
    std::string prefix = "Meta:";
    while (std::getline(file, line))
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


std::vector<StoryPoint> StoryLoader::GetStoryPoints(std::ifstream& file) const
{
    std::string line;
    std::vector<StoryPoint> points;
    while (std::getline(file, line))
    {
        if (!line.empty() && !std::isspace(line.at(0)))
        {
            StoryPoint point = GetStoryPoint(file, line);
            points.push_back(point);
        }
    }
    return points;
}

StoryPoint StoryLoader::GetStoryPoint(std::ifstream& file, const std::string& lastLine) const
{
    std::string line;
    std::stringstream ss;
    while (std::getline(file, line))
    {
        if (line.compare(0, 4, "    ") == 0)
            ss << line.substr(4);
        else
            break;
    }
    StoryPoint point(lastLine);
    point.SetTextStr(ss.str());
    return point;
}

} // namespace txt
