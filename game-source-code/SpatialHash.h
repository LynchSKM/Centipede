#ifndef SPATIALHASH_H
#define SPATIALHASH_H

#include "Grid.h"
#include "IEntity.h"
#include "POSITION.H"

#include <algorithm>
#include <memory>
#include <vector>
#include <map>

using std::unique_copy;
using std::sort;
using std::find;
using std::begin;
using std::end;
using std::vector;
using std::shared_ptr;
using std::map;
using std::pair;

using IEntity_ptr = shared_ptr<IEntity>;

/** \class SpatialHash
 *  \brief This class will be used by collision detection to query for objects
 *  around the object of interest.
 *  \details The screen is divided up into cells. A map will be
 *  populated with the cells (row,col) as a key and the value will be a stl container
 *  that has shared_ptr(s) to game objects in each cell. The container(s) will be returned
 *  for cells where an object exists.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version
 */

class SpatialHash
{
    public:
        /** \brief Parameterized constructor. Creates a SpatialHash object.
         *  \param grid is of type Grid and has the screen's width and height
         */
        SpatialHash(const Grid& grid);

        /** \brief Saves the cell locations of an object into a map which will be
         * used to query the objects near it.
         * \param game_objects is vector of IEntity and contains the game objects created in the game.
         * \return void
         */
        void generateSpatialHashTable(vector<IEntity_ptr>& game_objects);

        /** \brief Queries the map for the cells the object is located in and
         * returns a vector of shared pointers to all the objects in the cells
         * where the object of interest is located.
         * \param object is a shared pointer of type IEntity.
         * \return vector<shared_ptr<IEntity>>
         */
        vector<IEntity_ptr> retrieveNearbyObjects(IEntity_ptr object);

        /** \brief Clears the vectors in the game_object_table_.
         * \return void
         */
        void clearAll();

        /** Default Destructor. Destroys a SpatialHash object.
         */
        ~SpatialHash();

    private:
        Grid grid_;
        map<unsigned int, vector<shared_ptr<IEntity>> > game_object_table_;
        unsigned int cell_size_;

        // Private functions:
        /** \brief Builds the keys for the map game_object_table_.
         *  The keys are the centres of cells created on the grid.
         * \return void
         */
        void buildMapKeys();

        /** \brief Retrieves the screen positions where the object's centre and
         * boundary box vertices are located.
         * \param object shared pointer of type IEntity.
         * \return vector<Position>
         */
        vector<Position> getObjectLocations(IEntity_ptr& object);

        /** \brief Maps a position to a cell based on the grid's width, height and
         * the chosen cell size.
         * \param position is of type Position.
         * \return unsigned int
         */
        unsigned int generateMapKey(const Position& position);

        /** \brief Maps positions to a cell based on the grid's width, height, and
         * the chosen cell size.
         * \param positions is a vector of type Position.
         * \return  vector<unsigned int>
         */
        vector<unsigned int> generateMapKeys(vector<Position>& positions);

        /** \brief Saves a shared pointer to the object at the cells where the
         * object is located into the map game_object_table_;
         * \param object is a shared_ptr to IEntity and is pointing to a game object.
         * \param game_object_locations is a vector containing the positions which
         * the object occupies.
         * \return void
         */
        void saveLocations(IEntity_ptr object);
};

#endif // SPATIALHASH_H
