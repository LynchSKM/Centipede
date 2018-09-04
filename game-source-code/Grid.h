#ifndef GRID_H
#define GRID_H


/** \class Grid
*   \brief This is a Class contains details about the screen.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*
*/
class Grid
{
    public:

        /** \brief Creates a grid object with a default size of 800x600.
         * \param unsigned int width.
         * \param unsigned int height.
         */
        Grid(unsigned int width = 800, unsigned int height = 600);

        /** \brief destroys the Grid object
         */
        ~Grid();

        /** \brief get a constant copy of the object's width
         * \return unsigned int constant copy of the width
         */
        unsigned int getWidth() const;

        /** \brief get a constant copy of the object's height
         * \return unsigned int constant copy of the height
         */
        unsigned int getHeight() const;

    private:
        unsigned int width_;
        unsigned int height_;
};

#endif // GRID_H
