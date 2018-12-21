#pragma once

#include <string>
#include <vector>
#include "LambdaResponseHandler.h"

class ResponseSystem
{
public:
    ResponseSystem();
    ~ResponseSystem();

    void AddHandler(std::shared_ptr<ResponseHandler> handler);
    void AddHandlers(const std::vector<std::shared_ptr<ResponseHandler>>& handlers);
    void AddLambdaResponseHandler(const std::function<ResponseMatch(const std::string&)> matcher,
        const std::function<void(const ResponseMatch&)>& func);
    void RemoveHandler(const std::string& key);
    void ClearHandlers();
    void HandleInput(const std::string& input);
    size_t HandlerCount() const;
private:
    std::vector<std::shared_ptr<ResponseHandler>> m_handlers;
};

