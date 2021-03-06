/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#include "GameState.h"

namespace txt
{

GameState::GameState()
{
}

GameState::~GameState()
{
}

void GameState::Init(
    std::unordered_map<std::string, int> intState,
    std::unordered_map<std::string, float> floatState,
    std::unordered_map<std::string, std::string> stringState
) {
    m_intState = intState;
    m_floatState = floatState;
    m_stringState = stringState;
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

int GameState::ReadInt(const std::string& key, int def) const
{
    if (HasInt(key))
        return m_intState.at(key);
    return def;
}

float GameState::ReadFloat(const std::string& key, float def) const
{
    if (HasFloat(key))
        return m_floatState.at(key);
    return def;
}

std::string GameState::ReadString(const std::string& key, const std::string& def) const
{
    if (HasString(key))
        return m_stringState.at(key);
    return def;
}

std::unordered_map<std::string, int> GameState::GetAllInts() const
{
    return m_intState;
}

std::unordered_map<std::string, float> GameState::GetAllFloats() const
{
    return m_floatState;
}

std::unordered_map<std::string, std::string> GameState::GetAllStrings() const
{
    return m_stringState;
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

} // namespace txt
