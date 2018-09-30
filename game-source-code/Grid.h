#ifndef GRID_H
#define GRID_H

/** \class Grid
 *  \brief This class contains details about the screen such as the screen width
 *	and height.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *	\version 3.0
 */
class Grid
{
    public:

        /** \brief Creates a grid object with a default size 592x640.
         *  \param width is an unsigned int.
         *  \param height is an unsigned int.
         */
        Grid(unsigned int width = 592, unsigned int height = 640);

        /** \brief Default Destructor. Destroys a Grid object.
         */
        ~Grid();

        /** \brief Returns the grid's width.
         *  \return unsigned int
         */
        unsigned int getWidth() const;

        /** \brief Returns the grid's height.
         *  \return unsigned int
         */
        unsigned int getHeight() const;

    private:
        unsigned int width_;
        unsigned int height_;
};

#endif // GRID_H
