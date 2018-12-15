#include "GameState.h"

GameState::GameState()
{
}

GameState::~GameState()
{
}

void GameState::Reset()
{
    m_intState.clear();
    m_floatState.clear();
    m_stringState.clear();
}

void GameState::SetInt(const std::string& key, int value)
{
    m_intState[key] = value;
}

void GameState::SetFloat(const std::string& key, float value)
{
    m_floatState[key] = value;
}

void GameState::SetString(const std::string& key, const std::string& value)
{
    m_stringState[key] = value;
}

int GameState::GetInt(const std::string& key)
{
    if (!HasInt(key))
        throw std::invalid_argument("No int-state exists with key: " + key);
    return m_intState[key];
}

float GameState::GetFloat(const std::string& key)
{
    if (!HasFloat(key))
        throw std::invalid_argument("No float-state exists with key: " + key);
    return m_floatState[key];
}

std::string GameState::GetString(const std::string& key)
{
    if (!HasString(key))
        throw std::invalid_argument("No string-state exists with key: " + key);
    return m_stringState[key];
}

bool GameState::HasInt(const std::string& key)
{
    return m_intState.find(key) != m_intState.end();
}

bool GameState::HasFloat(const std::string& key)
{
    return m_floatState.find(key) != m_floatState.end();
}

bool GameState::HasString(const std::string& key)
{
    return m_stringState.find(key) != m_stringState.end();
}
