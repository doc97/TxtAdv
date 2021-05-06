/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <unordered_map>
#include <string>

namespace txt
{

/* Class: GameState
 * Represents the game state.
 *
 * You can store key-value pairs, where the keys are strings and the value is a
 *
 * - int
 * - float
 * - string
 *
 * You can think of it as a hash map wrapper for different types.
 */
class GameState
{
public:
    GameState();
    ~GameState();

    /* Function: Init
     * Initializes the state.
     *
     * Parameters:
     *
     *    intState - The integer key-values
     *    floatState - The floating-point key-values
     *    stringState - The string key-values
     */
    void Init(
        std::unordered_map<std::string, int> intState,
        std::unordered_map<std::string, float> floatState,
        std::unordered_map<std::string, std::string> stringState
    );

    /* Function: Reset
     * Resets the state, a.k.a. removes all key-value pairs.
     */
    void Reset();

    /* Function: SetInt
     * Stores an integer.
     *
     * Parameters:
     *
     *    key - The name of the integer
     *    value - The value to store
     */
    void SetInt(const std::string& key, int value);

    /* Function: SetFloat
     * Stores a float.
     *
     * Parameters:
     *
     *    key - The name of the float
     *    value - The value to store
     */
    void SetFloat(const std::string& key, float value);

    /* Function: SetString
     * Stores a string.
     *
     * Parameters:
     *
     *    key - The name of the string
     *    value - The value to store
     */
    void SetString(const std::string& key, const std::string& value);

    /* Function: UpdateInt
     * Replaces a stored integer.
     *
     * Parameters:
     *
     *    key - The name of the integer
     *    value - The value to store
     *
     * Throws:
     *
     *     std::invalid_argument if an integer with the name *key* does not exist
     */
    void UpdateInt(const std::string& key, int value);

    /* Function: UpdateFloat
     * Replaces a stored float.
     *
     * Parameters:
     *
     *    key - The name of the float
     *    value - The value to store
     *
     * Throws:
     *
     *     std::invalid_argument if a float with the name *key* does not exist
     */
    void UpdateFloat(const std::string& key, float value);

    /* Function: UpdateString
     * Replaces a stored string.
     *
     * Parameters:
     *
     *    key - The name of the string
     *    value - The value to store
     *
     * Throws:
     *
     *     std::invalid_argument if a string with the name *key* does not exist
     */
    void UpdateString(const std::string& key, const std::string& value);

    /* Function: GetInt
     * Returns a stored integer.
     *
     * Parameters:
     *
     *    key - The name of the integer
     *
     * Returns:
     *
     *    The value of the stored integer
     *
     * Throws:
     *
     *     std::invalid_argument if an integer with the name *key* does not exist
     */
    int GetInt(const std::string& key) const;

    /* Function: GetFloat
     * Returns a stored float.
     *
     * Parameters:
     *
     *    key - The name of the float
     *
     * Returns:
     *
     *    The value of the stored float
     *
     * Throws:
     *
     *     std::invalid_argument if a float with the name *key* does not exist
     */
    float GetFloat(const std::string& key) const;

    /* Function: GetString
     * Returns a stored string.
     *
     * Parameters:
     *
     *    key - The name of the string
     *
     * Returns:
     *
     *    The value of the stored string
     *
     * Throws:
     *
     *     std::invalid_argument if a string with the name *key* does not exist
     */
    std::string GetString(const std::string& key) const;

    /* Function: ReadInt
     * Returns a stored integer, or a default value if it doesn't exist.
     *
     * Parameters:
     *
     *    key - The name of the integer
     *    def - The default value
     *
     * Returns:
     *
     *    The value of the stored integer, or the default value
     */
    int ReadInt(const std::string& key, int def) const;

    /* Function: ReadFloat
     * Returns a stored float, or a default value if it doesn't exist.
     *
     * Parameters:
     *
     *    key - The name of the float
     *    def - The default value
     *
     * Returns:
     *
     *    The value of the stored float, or the default value
     */
    float ReadFloat(const std::string& key, float def) const;

    /* Function: ReadString
     * Returns a stored string, or a default value if it doesn't exist.
     *
     * Parameters:
     *
     *    key - The name of the string
     *    def - The default value
     *
     * Returns:
     *
     *    The value of the stored string, or the default value
     */
    std::string ReadString(const std::string& key, const std::string& def) const;

    /* Function: GetAllInts
     * Returns all stored integers.
     *
     * Returns:
     *
     *    A std::unordered_map<std::string, int> with all of the values
     */
    std::unordered_map<std::string, int> GetAllInts() const;

    /* Function: GetAllFloats
     * Returns all stored floats.
     *
     * Returns:
     *
     *    A std::unordered_map<std::string, float> with all of the values
     */
    std::unordered_map<std::string, float> GetAllFloats() const;

    /* Function: GetAllStrings
     * Returns all stored strings.
     *
     * Returns:
     *
     *    A std::unordered_map<std::string, std::string> with all of the values
     */
    std::unordered_map<std::string, std::string> GetAllStrings() const;

    /* Function: HasInt
     * Checks whether an integer with the name has been stored.
     *
     * Parameters:
     *
     *    key - The name of the integer to check
     *
     * Returns:
     *
     *    True if an integer with the name *key* exists
     */
    bool HasInt(const std::string& key) const;

    /* Function: HasFloat
     * Checks whether a float with the name has been stored.
     *
     * Parameters:
     *
     *    key - The name of the float to check
     *
     * Returns:
     *
     *    True if a float with the name *key* exists
     */
    bool HasFloat(const std::string& key) const;

    /* Function: HasString
     * Checks whether a string with the name has been stored.
     *
     * Parameters:
     *
     *    key - The name of the string to check
     *
     * Returns:
     *
     *    True if a string with the name *key* exists
     */
    bool HasString(const std::string& key) const;

private:
    std::unordered_map<std::string, int> m_intState{};
    std::unordered_map<std::string, float> m_floatState{};
    std::unordered_map<std::string, std::string> m_stringState{};
};

} // namespace txt
