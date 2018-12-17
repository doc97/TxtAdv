#pragma once

#include <string>
#include <vector>
#include "ResponseHandler.h"

class StoryPoint
{
public:
    StoryPoint();
    ~StoryPoint();

    void SetText(const std::string& text);
    void SetHandlers(const std::vector<ResponseHandler*>& handlers);
    std::string GetText() const;
    std::vector<ResponseHandler*> GetHandlers() const;
private:
    std::string m_text;
    std::vector<ResponseHandler*> m_handlers;
};

