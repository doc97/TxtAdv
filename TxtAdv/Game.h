/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

namespace txt
{

/* Interface: Game
 * Abstract class that provides a game loop. Extend to provide behaviour.
 */
class Game
{
public:
    Game();
    virtual ~Game();

    /* Function: Run
     * Starts the game loop. Calls <Init> before the loop and <Update> once every loop.
     */
    void Run();

    /* Function: Exit
     * Terminates the game loop.
     */
    void Exit();

private:
    /* Function: Init
     * Implement initialization code for your game here.
     *
     * See Also:
     *
     *    <Run>
     */
    virtual void Init() = 0;

    /* Function: Init
     * Implement update logic for your game here.
     *
     * See Also:
     *
     *    <Run>
     */
    virtual void Update() = 0;

private:
    bool m_isRunning;
};

} // namespace txt
