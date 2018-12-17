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
private:
    std::string m_text;
    std::vector<std::shared_ptr<ResponseHandler>> m_handlers;
};

