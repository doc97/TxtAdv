#pragma once
class Game
{
public:
    Game();
    ~Game();

    void Run();
    void Exit();

protected:
    virtual void Init() = 0;
    virtual void Update() = 0;

private:
    bool m_isRunning;
};
