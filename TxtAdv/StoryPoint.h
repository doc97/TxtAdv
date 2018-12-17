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
    void SetHandlers(const std::vector<ResponseHandler>& handlers);
    void NotifyHandlers(const std::string& message);
    std::string GetText() const;
    size_t GetHandlerCount() const;
    std::vector<ResponseHandler> GetHandlers() const;
private:
    std::string m_text;
    std::vector<ResponseHandler> m_handlers;
};

