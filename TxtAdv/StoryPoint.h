#pragma once

#include <string>

class StoryPoint
{
public:
    StoryPoint();
    ~StoryPoint();

    void SetText(const std::string& text);
    std::string GetText() const;
private:
    std::string m_text;
};

