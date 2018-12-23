/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

namespace txt
{

/* Struct: LuaParam
 * Represents a parameter to a C-function passed to Lua
 *
 * See Also:
 *
 *    <LuaManager>
 */
struct LuaParam
{
    /* Enum: DataType
     *
     * Bool - Signals that the data is of boolean type
     * Int - Signals that the data is of integer type
     * Double - Signals that the data is of double type
     * String - Signals that the data is of string type
     */
    enum DataType { Bool = 0, Int, Double, String } type;

    /* Variable: data
     * A union to hold the parameter value.
     *
     * Value Types:
     *
     *    - bool
     *    - long long
     *    - double
     *    - const char
     */
    union Data
    {
        bool b;
        long long i;
        double d;
        const char* s;

        Data() : b(false) {}
        Data(bool _b) : b(_b) {}
        Data(long long _i) : i(_i) {}
        Data(double _d) : d(_d) {}
        Data(const char* _s) : s(_s) {}
    } data;
};

}
