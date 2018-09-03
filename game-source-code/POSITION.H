#ifndef POSITION_H
#define POSITION_H

/**
 * Position Class - A data class containing all the setters,getters and variables defining a position of an object.
 */

class Position{

public:

    /** \brief Default Constructor. Creates a Position object with x and y coordinates of its center.
     */
    Position();

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


private:

    float xPos_, yPos_;

};
#endif // POSITION_H
