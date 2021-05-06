/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include <unordered_map>
#include "StoryPoint.h"

namespace txt
{

class StoryPointStore
{
public:
    StoryPointStore();
    ~StoryPointStore();

    /* Function: Add
     * Adds a <StoryPoint> to the store.
     *
     * Parameters:
     *
     *    point - The <StoryPoint> to add
     */
    void Add(const StoryPoint& point);

    /* Function: Get
     * Gets a <StoryPoint> by its name.
     *
     * Parameters:
     *
     *    name - The name of the <StoryPoint>
     *
     * Returns:
     *
     *    A pointer to the point, or nullptr if no point with that name could be found 
     */
    StoryPoint Get(const std::string& name);
private:
    std::unordered_map<std::string, StoryPoint> m_points;
};

} // namespace txt
