#ifndef MUSHROOMFACTORY_H
#define MUSHROOMFACTORY_H

#include "Mushroom.h"
#include "Grid.h"
#include <vector>
#include <memory>
#include <cmath>
#include <map>

using std::map;
using std::pair;
using std::vector;
using std::shared_ptr;
using std::make_shared;

/** \class MushroomFactory
 *  \brief Creates all the Mushroom objects of the game. The game grid is divided
 *  into cells of size 16x16 pixels. Each cell is paired with a bool indicating whether
 *  the cell is occupied or not. Mushrooms are randomly created on the grid excluding the
 *  player's screen boundary, they are created using the centre of each cell provided the
 *  cell is not occupied. Creation of one mushroom given a position only maps the position
 *  to a cell without querying it status.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */
class MushroomFactory
{
    public:

        /** \brief Parameterized constructor. Creates a MushroomFactory object.
         *  \param grid of type Grid.
         */
        MushroomFactory(const Grid& grid);

        /** \brief Default Destructor. Destroys a Mushroom Factory object.
         */
        ~MushroomFactory();

        /** \brief Generates mushrooms.
         *  \return vector<shared_ptr<Mushroom>>
         */
        vector <shared_ptr<Mushroom>> generateMushrooms();

        /** \brief Generates a mushroom at the given position.
         *  \param position is of type Position.
         *  \return shared_ptr<Mushroom>
         */
        shared_ptr<Mushroom> generateAMushroom(Position position);

    private:
        const Grid grid_;
        int maxCol_, maxRow_, maxMushrooms_;
        map<unsigned int, bool> cell_ID_List_;

        /** \brief Maps the grid into rows and columns (cells).
         */
        void defineRowAndCol();

        /** \brief Maps the position into the defined xpos and ypos.
         *  \param position is of type Position.
         *  \return Position
         */
        Position gridPointLink(Position position);

        /** \brief Maps the position into the defined rows and columns.
         *  \param position is of type Position.
         *  \return Position
         */
        Position gridRowCol(Position position);

        /** \brief Checks if a cell is occupied.
         *  \param x is an int and contains the centre x position of a cell.
         *  \param y is an int and contains the centre y position of a cell.
         *  \return bool stating if the cell is occupied or not.
         */
        bool isCellOccupied(int x, int y);
};

#endif // MUSHROOMFACTORY_H
