#include "ResponseSystem.h"
#include <algorithm>

ResponseSystem::ResponseSystem()
{
}

ResponseSystem::~ResponseSystem()
{
}

void ResponseSystem::AddHandler(const ResponseHandler& handler)
{
    m_handlers.push_back(std::make_unique<ResponseHandler>(handler));
}

void ResponseSystem::AddHandler(const std::function<bool(const std::string&)> matcher, const std::function<void()>& func)
{
    ResponseHandler handler(matcher, func);
    AddHandler(handler);
}

void ResponseSystem::RemoveHandler(const std::string& key)
{
    m_handlers.erase(
        std::remove_if(
            m_handlers.begin(),
            m_handlers.end(),
            [&](const std::unique_ptr<ResponseHandler>& p) { return p->GetMatcher()(key); }),
        m_handlers.end());
}

void ResponseSystem::HandleInput(const std::string& input)
{
    for (auto&& handler : m_handlers)
    {
        handler->HandleInput(input);
    }
}

size_t ResponseSystem::HandlerCount() const
{
    return m_handlers.size();
}
