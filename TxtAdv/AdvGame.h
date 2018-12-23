/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include "Game.h"
#include "IO.h"
#include "Prompt.h"
#include "ResponseSystem.h"
#include "StoryBranch.h"
#include "GameState.h"
#include "LuaManager.h"

namespace txt
{

/* Class: AdvGame
 * Game framework class.
 *
 * Extends:
 *
 *    <Game>
 */
class AdvGame : public Game
{
public:
    /* Constructor: AdvGame
     *
     * Parameters:
     *
     *    io - A pointer to the I/O interface to use
     */
    AdvGame(IO* io);
    ~AdvGame();

    /* Function: GetState
     * Gives access to the game state.
     *
     * Returns:
     *
     *    A reference to the <GameState> instance
     *
     * See Also:
     *
     *    <GameState>
     */
    GameState& GetState();

    /* Function: GetStory
     * Gives access to the story.
     *
     * Returns:
     *
     *    A reference to the <StoryBranch> instance
     *
     * See Also:
     *
     *    <StoryBranch>
     */
    StoryBranch& GetStory();

    /* Function: GetIO
     * Gives access to the I/O interface.
     *
     * Returns:
     *
     *    A pointer to the <IO> instance
     *
     * See Also:
     *
     *    <IO>
     */
    IO* GetIO() const;
protected:
    /* Function: Init
     * Contains game framework initialization code.
     */
    void Init() override;

    /* Function: Update
     * Contains game framework update code.
     */
    void Update() override;
private:
    IO* m_io;
    Prompt m_prompt;
    ResponseSystem m_response;
    StoryBranch m_branch;
    GameState m_state;
    LuaManager m_manager;

    void InitLua();
    void InitMisc();
    void InitStory();
    void InitPointOne();
    void InitPointTwo();
    void InitPointThree();
};

} // namespace txt
