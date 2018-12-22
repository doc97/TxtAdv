/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>

namespace txt
{

class ResponseHandler
{
public:
    virtual ~ResponseHandler() {}
    virtual void HandleInput(const std::string& input) = 0;
    virtual bool Matches(const std::string& input) = 0;
};

} // namespace txt
