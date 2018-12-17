#pragma once

#include <string>
#include <vector>
#include "ResponseHandler.h"

class ResponseSystem
{
public:
    ResponseSystem();
    ~ResponseSystem();

    void AddHandler(const ResponseHandler& handler);
    void AddHandler(const std::function<bool(const std::string&)> matcher, const std::function<void()>& func);
    void RemoveHandler(const std::string& key);
    void ClearHandlers();
    void HandleInput(const std::string& input);
    size_t HandlerCount() const;
private:
    std::vector<std::unique_ptr<ResponseHandler>> m_handlers;
};

