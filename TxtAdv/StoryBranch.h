/**********************************************************
* License: The MIT License
* https://www.github.com/doc97/TxtAdv/blob/master/LICENSE
**********************************************************/

#pragma once

#include <vector>
#include <string>
#include "StoryPoint.h"

namespace txt
{

/* Class: StoryBranch
 * Represents one storyline in the game.
 *
 * It is made up of a series of <StoryPoint>s.
 */
class StoryBranch
{
public:
    /* Constructor: StoryBranch
     * Creates an anonymous, parentless branch.
     */
    StoryBranch();

    /* Constructor: StoryBranch
     * Creates a named, parentless branch.
     *
     * Parameters:
     *
     *    name - The name of the branch
     */
    StoryBranch(const std::string& name);
    ~StoryBranch();

    /* Function: AddPoint
     *
     * Parameters:
     *
     *    point - The <StoryPoint> to add
     */
    void AddPoint(const StoryPoint& point);

    /* Function: AddPoint
     * Add a <StoryPoint> by using its parameters.
     *
     * Parameters:
     *
     *    name - See <StoryPoint>
     *    text - See <StoryPoint>
     *    parser - See <StoryPoint>
     *    handlers - See <StoryPoint>
     */
    void AddPoint(const std::string& name, const std::string& text, TextParser* parser,
        const std::vector<std::shared_ptr<ResponseHandler>>& handlers);

    /* Function: Next
     * Advances to the next point in the story.
     *
     * *Note*: If it's already at the end of the branch, it does nothing.
     */
    void Next();

    /* Function: Prev
     * Reverses to the previous point in the story.
     *
     * *Note*: If it's at the beginning of the branch, it does nothing.
     */
    void Prev();

    /* Function: Head
     * Returns the position of the head, 0 is at the start.
     */
    int Head();

    /* Function: IsAtStart
     * Returns true, if at the beginning of the branch.
     */
    bool IsAtStart();

    /* Function: IsAtEnd
     * Returns true, if at the end of the branch.
     */
    bool IsAtEnd();

    /* Function: SetHead
     * Moves the head to a certain point in the story line.
     *
     * Parameters:
     *
     *    index - The index of the point in the storyline.
     */
    void SetHead(unsigned int index);

    /* Function: SetHeadByName
     * Moves the head to a certain point in the story line by its name.
     * Does nothing if no story point with that name exists.
     *
     * Parameters:
     *
     *    name - The name of the story point
     */
    void SetHeadByName(const std::string& name);

    /* Function: SetParentBranch
     *
     * Parameters:
     *
     *    The <StoryBranch> which will become the parent
     */
    void SetParentBranch(const StoryBranch& parent);

    /* Function: UnsetParentBranch
     * Makes the branch parentless.
     */
    void UnsetParentBranch();

    /* Function: GetName
     *
     * Returns:
     *
     *    The name of the branch, "" if no name has been set
     */
    std::string GetName() const;

    /* Function: GetPointAt
     *
     * Parameters:
     *
     *    index - The index of a point in the storyline.
     *
     * Returns:
     *
     *    A pointer to the <StoryPoint> at that index, nullpointer if it doesn't exist
     */
    StoryPoint* GetPointAt(unsigned int index) const;

    /* Function: GetHead
     * Returns the current <StoryPoint>.
     *
     * Returns:
     *
     *    A pointer to the <StoryPoint>, nullpointer if the branch is empty.
     *
     * See Also:
     *
     *    <Prev>, <Next>
     */

    StoryPoint* GetHead() const;

    /* Function: GetParentBranch
     *
     * Returns:
     *
     *    A pointer to the parent branch.
     */
    StoryBranch* GetParentBranch() const;

    /* Function: Length
     *
     * Returns:
     *
     *    The number of story points in this branch
     */
    size_t Length() const;

    /* Function: Empty
     *
     * Returns:
     *
     *    True if the <Length> of this branch is 0
     */
    bool Empty() const;
private:
    std::vector<std::shared_ptr<StoryPoint>> m_points;
    std::shared_ptr<StoryBranch> m_parent;
    std::string m_name;
    unsigned int m_head = 0;
};

} // namespace txt
