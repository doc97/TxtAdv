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
    void SetParentBranch(const StoryBranch& parent);
    void UnsetParentBranch();
    std::shared_ptr<StoryPoint> GetPointAt(unsigned int index) const;
    std::shared_ptr<StoryPoint> GetHead() const;
    std::shared_ptr<StoryBranch> GetParentBranch() const;
    unsigned int Length() const;
    bool Empty() const;
private:
    std::vector<std::shared_ptr<StoryPoint>> m_points;
    std::shared_ptr<StoryBranch> m_parent;
    unsigned int m_head;
};

