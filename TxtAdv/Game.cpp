#include "Game.h"

namespace txt
{

Game::Game()
{
}

Game::~Game()
{
}

void Game::Run()
{
    Init();
    m_isRunning = true;
    while (m_isRunning)
        Update();
}

void Game::Exit()
{
    m_isRunning = false;
}

} // namespace txt