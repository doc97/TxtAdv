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
    void RemoveHandler(const std::string& key);
    void HandleInput(const std::string& input);
    unsigned int HandlerCount() const;
private:
    std::vector<std::unique_ptr<ResponseHandler>> m_handlers;
};

