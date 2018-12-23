/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <string>
#include <vector>

namespace txt
{

/* Class: ResponseMatch
 * Represents a result of the matcher function in <LambdaResponseHandler>.
 */
class ResponseMatch
{
public:
    /* Constructor: ResponseMatch
     *
     * Parameters:
     *
     *    isMatch - Indicates whether the matching function accepted the input
     *    captures - A list of captures that the matchin function caught
     */
    ResponseMatch(bool isMatch, const std::vector<std::string>& captures);

    /* Constructor: ResponseMatch
     * Shorthand for:
     * > ResponseMatch(isMatch, {});
     *
     * Parameters:
     *
     *    isMatch - Indicates whether the matching function accepted the input
     */
    ResponseMatch(bool isMatch);
    ~ResponseMatch();

    /* Function: IsMatch
     *
     * Returns:
     *
     *    The value set in the constructor
     */
    bool IsMatch() const;

    /* Function: CaptureCount
     *
     * Returns:
     *
     *    The number of captures
     */
    size_t CaptureCount() const;

    /* Function: GetCapture
     * Get a capture with a certain index.
     *
     * Parameters:
     *
     *    index - The index of the capture, must be less than the total number of captures
     *
     * Returns:
     *
     *    The capture at the index
     *
     * Throws:
     *
     *    std::out_of_range if index >= number of captures
     */
    std::string GetCapture(size_t index) const;
private:
    bool m_isMatch;
    std::vector<std::string> m_captures;
};

} // namespace txt
