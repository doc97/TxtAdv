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
    void SetMarkup(const std::string& text, const std::vector<std::function<std::string()>>& expr);
    void SetHandlers(const std::vector<ResponseHandler>& handlers);
    void NotifyHandlers(const std::string& message);
    std::string GetText() const;
    size_t GetHandlerCount() const;
    std::vector<ResponseHandler> GetHandlers() const;
private:
    std::string m_text;
    std::vector<ResponseHandler> m_handlers;
    std::vector<std::function<std::string()>> m_expressions;

    std::string ParseText(const std::string& text, const std::vector<std::function<std::string()>>& expr) const;
    bool IsIllegalText(const std::string& text) const;
};

