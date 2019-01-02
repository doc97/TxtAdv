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

std::vector<StoryPoint> StoryLoader::Load(const std::string& filename) const
{
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

std::unordered_map<std::string, std::vector<StoryLoader::Metadata>> StoryLoader::GetMetadata(const std::string& filename) const
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::unordered_map<std::string, std::vector<Metadata>> ret;
        std::string line;
        while (std::getline(file, line))
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
