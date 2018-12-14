#include "ResponseHandler.h"

ResponseHandler::ResponseHandler(const std::string& key, ResponseListener* listener)
    : m_key(key), m_listener(listener)
{
}

ResponseHandler::~ResponseHandler()
{
}

void ResponseHandler::HandleInput(const std::string& input)
{
    if (m_key == input)
        m_listener->Act();
}
