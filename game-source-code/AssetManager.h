#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

#include "Direction.h"

using std::string;
using std::vector;
using std::map;
using std::pair;
using std::tuple;

/** \class AssetManager
 *  \brief A data layer class containing a AssetType and the path to the asset. Loads
 *  the assets (textures, fonts, sounds) used by the game. This class also stores
 *  details about the number of images in the game textures and the direction
 *  objects face in the texture if any.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class AssetManager
{
	public:
		/** \brief AssetManager - Default Class Constructor.
		 */
		AssetManager();

        /** \enum AssetType
         *  \brief A strongly typed enum class that contains the different game assets.
		 *	\author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
		 *	\version 3.0
         */
		enum class AssetType
		{
            FONT = 0,       /**< Represents the game font used.*/
            GUNSHOT_SOUND,  /**< Represents the sound used for bullets fired.*/
            LEVEL_UP,       /**< Represents the sound used for Levelling up.*/
            MUSHROOM_REGEN, /**< Represents the sound used for Mushroom regeneration.*/
            SCORPION_MOVE,  /**< Represents the sound used for Scorpion movement.*/
            SPIDER_MOVE,    /**< Represents the sound used for Spider movement.*/
            PLAYER,         /**< Represents the texture used for a Player object.*/
            BULLET,         /**< Represents the texture used for a PlayerBullet object.*/
            CENTIPEDE,      /**< Represents the texture used for a CentipedeSegment object.*/
            MUSHROOM,       /**< Represents the texture used for a Mushroom object.*/
            SCORPION,       /**< Represents the texture used for a Scorpion object.*/
            SPIDER          /**< Represents the texture used for a Spider object.*/
		};

		/** \brief Parameterized Constructor. Creates an AssetManager object.
		 *	Used to create an Asset Manager object containing the type
		 *	of asset being loaded and the path where to find the asset.
		 *	\param asset_type is of type AssetType and contains the type of asset being loaded.
		 *	\param asset_path is of type std::string and contains the path to the asset being loaded.
		 */
		AssetManager(AssetType asset_type, string asset_path);

		/** \brief Returns the AssetType related to the AssetManager.
         * 	\return AssetType enum a strongly typed enumeration of AssetType.
         */
        AssetType getAssetType() const;

        /** \brief Returns the path on the disk related to the asset.
         * 	\return string with path to the asset.
         */
        string getAssetPath() const;

        /**	\brief Returns a vector of type AssetManager containing
         *  all the asset information for the project.
         * 	\return vector<AssetManager>
         */
        vector<AssetManager> getAssetInfo();

        /**	\brief Returns a tuple with a vector of type unsigned int containing
         *  the rows and columns in an image and a direction enum which gives
         *  information about the direction images face in the texture.
         * 	\return tuple<vector<unsigned int>, Direction>
         */
        tuple<vector<unsigned int>, Direction> getTextureDetails() const;

        /**	\brief Populates the map used to store the rows, columns and the default
         *  direction that images face in the texture for each game object. It is
         *  a static function because the map being updated is a static private member.
         */
        static void loadTextureDetails();

	private:
		AssetType assetType_;	/**< A variable of type enum class AssetType. Determines the type of asset.*/
		string assetPath_; 		/**< A string variable holding the path to the asset.*/
		static map<AssetType, tuple<vector<unsigned int>, Direction>> texture_details_;
		/**< A static map that holds the rows, columns and default direction in an image for each texture.*/

        /**	\brief A private static function that helps loadTextureDetails().
         *  Takes in the necessary inputs to be saved into the static private map
         *  called texture_details_.
         *  \param type_asset is of type AssetType.
         *  \param rows_in_image is an int containing the rows in an image.
         *  \param columns_in_image is an int containing the columns in an image.
         *  \param direction is an Direction enum containing the default direction faced in an image.
         */
		static void captureDetails(AssetType type_asset, int rows_in_image,
                                   int columns_in_image, Direction direction);
};

#endif //ASSETMANAGER_H
