#pragma once

#include <string>

class IO
{
public:
    virtual void Write(const std::string& string) = 0;
    virtual void WriteLine(const std::string& string) = 0;
    virtual void GetLine(std::string& string) = 0;
};
