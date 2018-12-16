#pragma once

#include <vector>
#include "StoryPoint.h"

class StoryBranch
{
public:
    StoryBranch();
    ~StoryBranch();

    void AddPoint(const StoryPoint& point);
    void AddPoint(const std::string& text);
    void Next();
    void Prev();
    void SetCurrentPoint(unsigned int index);
    std::shared_ptr<StoryPoint> GetPointAt(unsigned int index) const;
    std::shared_ptr<StoryPoint> GetHead() const;
    unsigned int Length() const;
    bool Empty() const;
private:
    std::vector<std::shared_ptr<StoryPoint>> m_points;
    unsigned int m_head;
};

