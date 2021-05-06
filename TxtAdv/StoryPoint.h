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
#include "TextMarkup.h"
#include "TextStyleSheet.h"
#include "Text.h"

namespace txt
{

/* Class: StoryPoint
 * Represent an atomic point in a storyline.
 */
class StoryPoint
{
public:
    StoryPoint();
    StoryPoint(const std::string& name);
    ~StoryPoint();

    /* Function: SetText
     * If the markup is set using <SetMarkup>, the markup in this
     * text object will be ignored.
     *
     * Parameters:
     *
     *    text - The new text object
     */
    void SetText(const Text& text);

    /* Function: SetTextStr
     *
     * Parameters:
     *
     *    raw - The raw text string
     */
    void SetTextStr(const std::string& raw);

    /* Function: SetStyleSheet
     *
     * Parameters:
     *
     *    style - The text style sheet
     */
    void SetStyleSheet(const TextStyleSheet style);

    /* Function: SetParser
     * Sets the <TextParser> to use to parse the text.
     * It will only be used if <SetMarkup> has been used.
     *
     * Parameters:
     *
     *    parser - The parser
     */
    void SetParser(TextParser* parser);

    /* Function: SetMarkup
     * Sets the <TextMarkup> to use to parse the text.
     *
     * Parameters:
     *
     *    markup - The markup
     */
    void SetMarkup(TextMarkup* markup);

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
     *    The parsed <Text> object
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
    TextStyleSheet m_style;
    std::vector<std::shared_ptr<ResponseHandler>> m_handlers;
    TextParser* m_parser = nullptr;
    TextMarkup* m_markup = nullptr;
};

} // namespace txt
