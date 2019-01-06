/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <functional>
#include <string>
#include <vector>
#include "ResponseHandler.h"
#include "TextParser.h"
#include "Text.h"

namespace txt
{

/* Class: StoryPoint
 * Represent an atomic point in a storyline.
 */
class StoryPoint
{
public:
    StoryPoint(const std::string& name);
    ~StoryPoint();

    /* Function: SetText
     *
     * Parameters:
     *
     *    text - The new text
     */
    void SetText(const Text& text);

    /* Function: SetTextStr
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
    void SetTextStr(const std::string& text);

    /* Function: SetParser
     * Sets the <TextParser> to use to parse the markup text.
     *
     * Parameters:
     *
     *    parser - The parser
     */
    void SetParser(std::shared_ptr<TextParser> parser);

    /* Function: SetHandlers
     * Sets a list of handlers associated with this point.
     *
     * Parameters:
     *
     *    handlers - The list of <ResponseHandler>s
     */
    void SetHandlers(const std::vector<std::shared_ptr<ResponseHandler>>& handlers);

    /* Function: GetName
     *
     * Returns:
     *
     *    Get the name
     */
    std::string GetName() const;

    /* Function: GetTextStr
     *
     * Returns:
     *
     *    Get the parsed text string
     *
     * See Also:
     *
     *    <SetMarkup>
     */
    std::string GetTextStr() const;

    /* Function: GetText
     *
     * Returns:
     *
     *    The underlying <Text> object
     */
    Text GetText() const;

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
    std::string m_name;
    Text m_text;
    std::vector<std::shared_ptr<ResponseHandler>> m_handlers;
    std::shared_ptr<TextParser> m_parser = nullptr;
};

} // namespace txt
