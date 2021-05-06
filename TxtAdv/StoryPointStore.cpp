/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "StoryPointStore.h"

namespace txt
{

StoryPointStore::StoryPointStore()
{
}


StoryPointStore::~StoryPointStore()
{
}

void StoryPointStore::Add(const StoryPoint& point)
{
    m_points[point.GetName()] = point;
}

StoryPoint StoryPointStore::Get(const std::string& name)
{
    return m_points.at(name);
}

} // namespace txt
