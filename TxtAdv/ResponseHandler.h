#pragma once

#include <string>
#include "ResponseListener.h"

class ResponseHandler
{
public:
    ResponseHandler(const std::string& key, ResponseListener* listener);
    ~ResponseHandler();

    void HandleInput(const std::string& input);

private:
    std::string m_key;
    ResponseListener* m_listener;
};

