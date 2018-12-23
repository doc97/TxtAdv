/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <functional>
#include <string>
#include <vector>
#include "ResponseHandler.h"

namespace txt
{

/* Class: StoryPoint
 * Represent an atomic point in a storyline
 */
class StoryPoint
{
public:
    StoryPoint();
    ~StoryPoint();

    /* Function: SetText
     * Sets the raw text of this story point.
     *
     * Parameters:
     *
     *    text - The text to set
     *
     * See Also:
     *
     *    <SetMarkup>
     */
    void SetText(const std::string& text);

    /* Function: SetMarkup
     * Sets the functions to which parse the markup text.
     *
     * Parameters:
     *
     *    expr - The functions for parsing the markup
     *
     * Example:
     *
     * --- C++ ---
     * StoryPoint point;
     * point.SetText("$0 - $1");
     * point.SetMarkup({ []() { return "foo"; }, []() { return "bar"; } });
     * point.GetText(); // Returns "foo - bar"
     * -----------
     */
    void SetMarkup(const std::vector<std::function<std::string()>>& expr);

    /* Function: SetHandlers
     * Sets a list of handlers associated with this point.
     *
     * Parameters:
     *
     *    handlers - The list of <ResponseHandler>s
     */
    void SetHandlers(const std::vector<std::shared_ptr<ResponseHandler>>& handlers);

    /* Function: GetText
     *
     * Returns:
     *
     *    Get the parsed text
     *
     * See Also:
     *
     *    <SetMarkup>
     */
    std::string GetText() const;

    /* Function: GetHandlerCount
     *
     * Returns:
     *
     *    The number of handlers associated with the point
     */
    size_t GetHandlerCount() const;

    /* Function: GetHandlers
     * Get a list of the handlers associated with the point.
     *
     * Returns:
     *
     *    The vector contains shared_ptr's, so you may take ownership of the handlers
     */
    std::vector<std::shared_ptr<ResponseHandler>> GetHandlers() const;
private:
    std::string m_text;
    std::vector<std::shared_ptr<ResponseHandler>> m_handlers;
    std::vector<std::function<std::string()>> m_expressions;

    std::string ParseText(const std::string& text, const std::vector<std::function<std::string()>>& expr) const;
    bool IsIllegalText(const std::string& text) const;
};

} // namespace txt
