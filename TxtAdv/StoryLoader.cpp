/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "StoryLoader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "LuaResponseHandler.h"
#include "StringUtil.h"

namespace txt
{

StoryLoader::StoryLoader()
{
}

StoryLoader::~StoryLoader()
{
}

std::vector<StoryPoint> StoryLoader::Load(const std::string& filename)
{
    m_isComment = false;
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string metaFile = GetMetaFile(file);
        std::vector<StoryPoint> ret = GetStoryPoints(file);
        std::unordered_map<std::string, std::vector<Metadata>> metadata = GetMetadata(metaFile);
        MergeMetadataWithStoryPoints(ret, metadata);

        file.close();
        return ret;
    }
    throw std::runtime_error("Could not open file!");
}

bool StoryLoader::NextLine(std::ifstream& file, std::string& line)
{
    while (std::getline(file, line))
    {
        if (HandleMultilineComment(line) && HandleSinglelineComment(line))
            return true;
    }
    return false;
}

bool StoryLoader::HandleMultilineComment(std::string& line)
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

bool StoryLoader::HandleSinglelineComment(std::string& line)
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

std::string StoryLoader::GetMetaFile(std::ifstream& file)
{
    std::string line;
    std::string prefix = "Meta:";
    while (NextLine(file, line))
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


std::vector<StoryPoint> StoryLoader::GetStoryPoints(std::ifstream& file)
{
    bool hasStarted = false;
    std::string line;
    std::vector<StoryPoint> points;

    std::stringstream ss;
    std::string pointName;
    while (NextLine(file, line))
    {
        if (hasStarted)
        {
            if (line.empty())
                ss << "\n";
            else if (line.compare(0, 4, "    ") == 0)
                ss << line.substr(4) << " ";
            else if (!std::isspace(line.at(0)))
            {
                points.push_back(CreateStoryPoint(pointName, ss.str()));

                pointName = line;
                ss.str("");
                ss.clear();
            }
        }
        else if (!line.empty() && !std::isspace(line.at(0)))
        {
            pointName = line;
            hasStarted = true;
        }
    }
    points.push_back(CreateStoryPoint(pointName, ss.str()));

    return points;
}

std::unordered_map<std::string, std::vector<StoryLoader::Metadata>> StoryLoader::GetMetadata(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::unordered_map<std::string, std::vector<Metadata>> ret;
        std::string line;
        while (NextLine(file, line))
        {
            std::vector<std::string> data = txt::split(line, ',');
            if (data.size() != 4)
                throw std::runtime_error("Invalid data format in .meta file!");
            for_each(data.begin(), data.end(), txt::trim);

            Metadata metadata;
            metadata.storypoint = data[0];
            metadata.script = data[1];
            metadata.matcher_func = data[2];
            metadata.action_func = data[3];

            ret[metadata.storypoint].push_back(metadata);
        }
        file.close();
        return ret;
    }
    throw std::runtime_error("Could not open file!");
}

StoryPoint StoryLoader::CreateStoryPoint(const std::string& name, const std::string& txt) const
{
    std::string str = txt;
    txt::trim(str);
    txt::repl(str, " \n", "\n");

    StoryPoint point(name);
    point.SetTextStr(str);
    return point;
}

void StoryLoader::MergeMetadataWithStoryPoints(std::vector<StoryPoint>& points,
    std::unordered_map<std::string, std::vector<Metadata>>& metadata) const
{
    for (StoryPoint& point : points)
    {
        bool hasMetadata = metadata.find(point.GetName()) != metadata.end();
        if (hasMetadata)
        {
            std::vector<Metadata> data = metadata[point.GetName()];
            MergeMetadataWithStoryPoint(point, data);
        }
    }
}

void StoryLoader::MergeMetadataWithStoryPoint(StoryPoint& point, std::vector<Metadata>& metadata) const
{
    std::vector<std::shared_ptr<ResponseHandler>> handlers;
    for (const Metadata& meta : metadata)
    {
        handlers.push_back(std::make_shared<LuaResponseHandler>(
            meta.script,
            meta.matcher_func,
            meta.action_func
        ));
    }
    point.SetHandlers(handlers);
}

} // namespace txt
