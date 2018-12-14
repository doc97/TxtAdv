#include "catch.hpp"
#include "ResponseHandler.h"
#include "ResponseListener.h"
#include <string>

struct TestListener : public ResponseListener
{
    bool m_hasActed = false;

    void Act() override
    {
        m_hasActed = true;
    }
};

TEST_CASE("InputHandler")
{
    std::string key = "a";
    TestListener listener;
    ResponseHandler handler(key, &listener);

    SECTION("matching key")
    {
        handler.HandleInput(key);
        REQUIRE(listener.m_hasActed);

    }
    SECTION("non-matching key")
    {
        handler.HandleInput("b");
        REQUIRE(!listener.m_hasActed);
    }
}

