#pragma once

#include <functional>
#include <string>
#include "ResponseListener.h"

class ResponseHandler
{
public:
    ResponseHandler(const std::string& key, const std::function<void()>& func);
    ~ResponseHandler();

    void HandleInput(const std::string& input);
    std::string GetKey() const;
private:
    std::string m_key;
    std::function<void()> m_func;
};

