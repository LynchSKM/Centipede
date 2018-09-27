#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <string>
#include <vector>

using std::string;
using std::vector;

/** \class AssetManager
*   \brief  A data class containing a AssetType and the path to the asset.Loads
*   the assets (textures, fonts, sounds) used by the game.
*   \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
*   \version 3.0
*/

class AssetManager{
	public:
		/** \brief AssetManager - Default Class Constructor.
		*/
		AssetManager();

        /** \enum AssetType
         *  \brief A strongly typed enum class that contains the different game assets.
         */
		enum class AssetType
		{
            FONT = 0,
            GUNSHOT_SOUND,
            MUSHROOM_REGEN,
            SCORPION_MOVE,
            SPIDER_MOVE,
            PLAYER,
            BULLET,
            CENTIPEDE,
            MUSHROOM,
            SCORPION,
            SPIDER
		};

		/** \brief AssetManager - Parameterized Class Constructor.
		*	Used to create a Asset Manager object containing the type
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
        *   all the asset information for the project
        * 	\return vector<AssetManager>
        */
        vector<AssetManager> getAssetInfo();

	private:
		AssetType assetType_; /**< A variable of type enum class AssetType. Determines the type of asset. */
		string assetPath_; /**< A string variable holding the path to the asset. */
};

#endif //ASSETMANAGER_H
