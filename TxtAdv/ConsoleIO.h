#pragma once

#include "IO.h"

class ConsoleIO : public IO
{
public:
    ConsoleIO();
    ~ConsoleIO();

    void Write(const std::string& string) override;
    void WriteLine(const std::string& string) override;
    void GetLine(std::string& string) override;
};

