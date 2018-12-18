#pragma once

#include <vector>
#include <string>
#include "StoryPoint.h"

class StoryBranch
{
public:
    StoryBranch();
    StoryBranch(const std::string& name);
    ~StoryBranch();

    void AddPoint(const StoryPoint& point);
    void AddPoint(const std::string& text);
    void AddPoint(const std::string& text, const std::vector<std::function<std::string()>>& expr);
    void AddPoint(const std::string& text, const std::vector<std::shared_ptr<InputHandler>>& handlers);
    void AddPoint(const std::string& text, const std::vector<std::function<std::string()>>& expr,
        const std::vector<std::shared_ptr<InputHandler>>& handlers);
    void Next();
    void Prev();
    void SetCurrentPoint(unsigned int index);
    void SetParentBranch(const StoryBranch& parent);
    void UnsetParentBranch();
    std::string GetName() const;
    std::shared_ptr<StoryPoint> GetPointAt(unsigned int index) const;
    std::shared_ptr<StoryPoint> GetHead() const;
    std::shared_ptr<StoryBranch> GetParentBranch() const;
    size_t Length() const;
    bool Empty() const;
private:
    std::vector<std::shared_ptr<StoryPoint>> m_points;
    std::shared_ptr<StoryBranch> m_parent;
    std::string m_name;
    unsigned int m_head;
};

