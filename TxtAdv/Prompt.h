/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include "IO.h"

namespace txt
{

/* Class: Prompt
 * Represents the main user input interface for the game.
 */
class Prompt
{
public:
    Prompt();
    ~Prompt();

    /* Function: PromptInput
     * Asks the I/O interface for input.
     *
     * E.g. if the prompt is: "$ "
     * > $ <input goes here>
     *
     * Returns:
     *
     *    The input response
     *
     * See Also:
     *
     *    <SetInput>
     */
    std::string PromptInput(IO& io);

    /* Function: SetPrompt
     * Sets the prompt with which to ask for input.
     *
     * Parameters:
     *
     *    prompt - The prompt string
     */
    void SetPrompt(const std::string& prompt);
private:
    std::string m_input;
    std::string m_prompt;
};

} // namespace txt
