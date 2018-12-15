#pragma once

#include <unordered_map>
#include <string>

class GameState
{
public:
    GameState();
    ~GameState();

    void Reset();
    void SetInt(const std::string& key, int value);
    void SetFloat(const std::string& key, float value);
    void SetString(const std::string& key, const std::string& value);
    void UpdateInt(const std::string& key, int value);
    void UpdateFloat(const std::string& key, float value);
    void UpdateString(const std::string& key, const std::string& value);
    int GetInt(const std::string& key);
    float GetFloat(const std::string& key);
    std::string GetString(const std::string& key);
    int ReadInt(const std::string& key, int defValue);
    float ReadFloat(const std::string& key, float defValue);
    std::string ReadString(const std::string& key, const std::string& defValue);
    bool HasInt(const std::string& key);
    bool HasFloat(const std::string& key);
    bool HasString(const std::string& key);

private:
    std::unordered_map<std::string, int> m_intState;
    std::unordered_map<std::string, float> m_floatState;
    std::unordered_map<std::string, std::string> m_stringState;
};

