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
 *  \brief creates all the mushroom objects of the game.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version
 */
class MushroomFactory
{
    public:

        /** \brief a parameterized constructor.
         * \param grid of type Grid.
         */
        MushroomFactory(const Grid& grid);

        /** \brief destroys the Mushroom Factory object.
         */
        ~MushroomFactory();

        /** \brief generates mushrooms.
         * \return a vector of shared ptr to Mushroom.
         */
        vector <shared_ptr<Mushroom>> generateMushrooms();

        /** \brief generates a mushroom at the given position.
         *  \param a position of type Position
         * \return a  shared ptr to a mushroom.
         */
        shared_ptr<Mushroom> generateAMushroom(Position position);


    private:
        Grid grid_;
        int maxCol_, maxRow_, maxMushrooms_;
        map<unsigned int, bool> cell_ID_List_;
        /** \brief maps the grid into rows and columns.
         */
        void defineRowAndCol();

        /** \brief maps the position into the defined xpos and ypos.
         *  \param a position of type Position.
         *  \return a position of type Position.
         */
        Position gridPointLink(Position position);

        /** \brief maps the position into the defined rows and columns.
         *  \param a position of type Position.
         *  \return a position of type Position.
         */
        Position gridRowCol(Position position);

        /** \brief checks if the cell is occupied.
         *  \param cell xpos int.
         *  \param cell ypos int.
         *  \return a bool stating if the cell is occupied or not.
         */
        bool isCellOccupied(int x, int y);
};

#endif // MUSHROOMFACTORY_H
