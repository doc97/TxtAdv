#pragma once

#include <string>
#include <vector>
#include "ResponseHandler.h"

class ResponseSystem
{
public:
    ResponseSystem();
    ~ResponseSystem();

    void AddHandler(ResponseHandler* handler);
    void RemoveHandler(ResponseHandler* handler);
    void HandleInput(const std::string& input);
private:
    std::vector<ResponseHandler*> m_handlers;
};

