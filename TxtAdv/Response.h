#pragma once

#include <string>

class Response
{
public:
    Response(const std::string& input);
    ~Response();

private:
    std::string m_input;
};