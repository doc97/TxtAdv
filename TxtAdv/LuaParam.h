#pragma once

struct LuaParam
{
    enum DataType { Bool = 0, Int, Double, String } type;
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