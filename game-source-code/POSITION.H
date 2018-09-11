#ifndef POSITION_H
#define POSITION_H

/**
 * \class Position Class
 * \brief A data class containing all the setters,getters and variables
 * defining a position of an object.
 * \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 */

class Position{

public:

    /** \brief Parameterized Constructor. Creates a Position object with x and y coordinates of its center.
     *  Default values are x-0 and y=0.
     */
     Position(float x=0, float y=0);

    /** \brief Default destructor. destroys a Position object.
     */
    ~Position();

    /** \brief Sets the x coordinate of an object.
     * \param xPos is a float that defines x coordinate of an object.
     */
    void setX_pos(float xPos);

    /** \brief Sets the y coordinate of an object.
     * \param yPos is a float that defines y coordinate of an object.
     */
    void setY_pos(float yPos);

    /** \brief Gets a constant copy of the current x coordinate of the object.
     * \return float with a constant copy of the x coordinate.
     */
    float getX_pos() const;

    /** \brief Gets a constant copy of the current y coordinate of the object.
     * \return float with a constant copy of the y coordinate.
     */
    float getY_pos() const;

    /** \brief Overloaded subtraction operator (-).
    *   \return Position with the x and y results from the subtraction.
    */
    Position operator -(const Position& rhs);

    /** \brief Overloaded equality operator (==).
    *   \return bool
    */
    bool operator==(const Position& rhs) const;

    /** \brief Overloaded the less than operator (<).
    *   \return bool
    */
    bool operator<(const Position& rhs) const;

private:

    float xPos_, yPos_;

};
#endif // POSITION_H
