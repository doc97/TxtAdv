#include "ResponseSystem.h"
#include <algorithm>

ResponseSystem::ResponseSystem()
{
}

ResponseSystem::~ResponseSystem()
{
}

void ResponseSystem::AddHandler(std::shared_ptr<InputHandler> handler)
{
    m_handlers.emplace_back(std::move(handler));
}

void ResponseSystem::AddHandlers(const std::vector<std::shared_ptr<InputHandler>>& handlers)
{
    for (const std::shared_ptr<InputHandler>& ptr : handlers)
        AddHandler(ptr);
}

void ResponseSystem::AddResponseHandler(const std::function<ResponseMatch(const std::string&)> matcher,
    const std::function<void(const ResponseMatch& match)>& func)
{
    m_handlers.push_back(std::make_unique<ResponseHandler>(matcher, func));
}

void ResponseSystem::RemoveHandler(const std::string& key)
{
    m_handlers.erase(
        std::remove_if(
            m_handlers.begin(),
            m_handlers.end(),
            [&](const std::shared_ptr<InputHandler>& p) { return p->Matches(key); }),
        m_handlers.end());
}

void ResponseSystem::ClearHandlers()
{
    m_handlers.clear();
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
