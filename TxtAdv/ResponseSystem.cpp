#include "ResponseSystem.h"

ResponseSystem::ResponseSystem()
{
}

ResponseSystem::~ResponseSystem()
{
}

void ResponseSystem::AddHandler(ResponseHandler* handler)
{
    m_handlers.push_back(handler);
}

void ResponseSystem::RemoveHandler(ResponseHandler* handler)
{
    std::vector<ResponseHandler*>::iterator it = m_handlers.begin();
    for (; it != m_handlers.end(); ++it)
        if ((*it) == handler)
            it = m_handlers.erase(it);
}

void ResponseSystem::HandleInput(const std::string& input)
{
    for (ResponseHandler* handler : m_handlers)
    {
        handler->HandleInput(input);
    }
}
