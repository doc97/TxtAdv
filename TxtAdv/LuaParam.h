#pragma once

#include <cstring>
#include <type_traits>

class LuaParam
{
public:
    enum DataType
    {
        Bool = 0, Int, Float, String,
    };

    LuaParam(const DataType type, void* value);
    ~LuaParam();
    DataType GetType() const;
    const void* GetValue() const;
private:
    DataType m_type;
    void* m_value;
};
 
template<class Dest, class Source>
inline Dest bit_cast(const Source& src)
{
    static_assert(sizeof(Dest) >= sizeof(Source), "size of destination and source objects must be equal");
    static_assert(std::is_trivially_copyable<Dest>::value, "destination must be trivially copyable");
    static_assert(std::is_trivially_copyable<Source>::value, "source must be trivially copyable");

    Dest dst;
    std::memcpy(&dst, &src, sizeof(dst));
    return dst;
}