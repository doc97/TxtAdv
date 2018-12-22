#pragma once

namespace txt
{

class Game
{
public:
    Game();
    virtual ~Game();

    void Run();
    void Exit();

protected:
    virtual void Init() = 0;
    virtual void Update() = 0;

private:
    bool m_isRunning;
};

} // namespace txt
