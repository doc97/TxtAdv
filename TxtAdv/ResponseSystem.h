/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include <vector>
#include "LambdaResponseHandler.h"

namespace txt
{

/* Class: ResponseSystem
 * Handles the response mechanisms in the game.
 */
class ResponseSystem
{
public:
    ResponseSystem();
    ~ResponseSystem();

    /* Function: AddHandler
     *
     * Parameters:
     *
     *    handler - A shared_ptr to the handler to add
     */
    void AddHandler(std::shared_ptr<ResponseHandler> handler);

    /* Function: AddHandlers
     *
     * Parameters:
     *
     *    handlers - A list of handlers to add
     */
    void AddHandlers(const std::vector<std::shared_ptr<ResponseHandler>>& handlers);

    /* Function: AddLambdaResponseHandler
     * Factory method for adding a <LambdaResponseHandler>.
     *
     * Parameters:
     *
     *    matcher - See <LambdaResponseHandler>
     *    func - See <LambdaResponseHandler>
     */
    void AddLambdaResponseHandler(const std::function<ResponseMatch(const std::string&)> matcher,
        const std::function<void(const ResponseMatch&)>& func);

    /* Function: RemoveHandlers
     * Remove all handlers that matches the input.
     *
     * Parameters:
     *
     *    key - The input to match
     */
    void RemoveHandlers(const std::string& key);

    /* Function: ClearHandlers
     * Remove all handlers.
     */
    void ClearHandlers();

    /* Function: HandleInput
     * Forward input to all response handlers.
     *
     * Parameters:
     *
     *    input - The input to forward
     */
    void HandleInput(const std::string& input);

    /* Function: HandlerCount
     *
     * Returns:
     *
     *    The number of handlers
     */
    size_t HandlerCount() const;
private:
    std::vector<std::shared_ptr<ResponseHandler>> m_handlers;
};

} // namespace txt
