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

void GameState::UpdateInt(const std::string& key, int value)
{
    if (!HasInt(key))
        throw std::invalid_argument("No int-state exists with key: " + key);
    m_intState[key] = value;
}

void GameState::UpdateFloat(const std::string& key, float value)
{
    if (!HasFloat(key))
        throw std::invalid_argument("No float-state exists with key: " + key);
    m_floatState[key] = value;
}

void GameState::UpdateString(const std::string& key, const std::string& value)
{
    if (!HasString(key))
        throw std::invalid_argument("No string-state exists with key: " + key);
    m_stringState[key] = value;
}

int GameState::GetInt(const std::string& key) const
{
    if (!HasInt(key))
        throw std::invalid_argument("No int-state exists with key: " + key);
    return m_intState.at(key);
}

float GameState::GetFloat(const std::string& key) const
{
    if (!HasFloat(key))
        throw std::invalid_argument("No float-state exists with key: " + key);
    return m_floatState.at(key);
}

std::string GameState::GetString(const std::string& key) const
{
    if (!HasString(key))
        throw std::invalid_argument("No string-state exists with key: " + key);
    return m_stringState.at(key);
}

int GameState::ReadInt(const std::string& key, int defValue) const
{
    if (HasInt(key))
        return m_intState.at(key);
    return defValue;
}

float GameState::ReadFloat(const std::string& key, float defValue) const
{
    if (HasFloat(key))
        return m_floatState.at(key);
    return defValue;
}

std::string GameState::ReadString(const std::string& key, const std::string& defValue) const
{
    if (HasString(key))
        return m_stringState.at(key);
    return defValue;
}

bool GameState::HasInt(const std::string& key) const
{
    return m_intState.find(key) != m_intState.end();
}

bool GameState::HasFloat(const std::string& key) const
{
    return m_floatState.find(key) != m_floatState.end();
}

bool GameState::HasString(const std::string& key) const
{
    return m_stringState.find(key) != m_stringState.end();
}
