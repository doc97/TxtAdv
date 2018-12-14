#include "ResponseHandler.h"

ResponseHandler::ResponseHandler(const std::string& key, const std::function<void()>& func)
    : m_key(key), m_func(func)
{
}

ResponseHandler::~ResponseHandler()
{
}

void ResponseHandler::HandleInput(const std::string& input)
{
    if (m_key == input)
        m_func();
}

std::string ResponseHandler::GetKey() const
{
    return m_key;
}
