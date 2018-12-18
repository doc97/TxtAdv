#pragma once

#include <string>
#include <vector>
#include "ResponseHandler.h"

class ResponseSystem
{
public:
    ResponseSystem();
    ~ResponseSystem();

    void AddHandler(std::shared_ptr<InputHandler> handler);
    void AddHandlers(const std::vector<std::shared_ptr<InputHandler>>& handlers);
    void AddResponseHandler(const std::function<ResponseMatch(const std::string&)> matcher,
        const std::function<void(const ResponseMatch&)>& func);
    void RemoveHandler(const std::string& key);
    void ClearHandlers();
    void HandleInput(const std::string& input);
    size_t HandlerCount() const;
private:
    std::vector<std::shared_ptr<InputHandler>> m_handlers;
};

