#include "AssetManager.h"
#include <algorithm>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

using std::find_if;
TEST_CASE("Asset path and entity type set can be retrieved successfully")
{

    AssetManager::AssetType assetType = AssetManager::AssetType::PLAYER;
    string assetPath = "Assets/PlayerAlt.png";
    AssetManager assetManager{assetType, assetPath };

    CHECK(assetManager.getAssetType() == assetType);
    CHECK(assetManager.getAssetPath() == assetPath);
}

TEST_CASE("Player Asset details are correctly stored and retrieved successfully")
{
    AssetManager assetManager{};
    AssetManager::loadTextureDetails();
    auto assets = assetManager.getAssetInfo();
    AssetManager::AssetType assetType = AssetManager::AssetType::PLAYER;

    auto iter_found = find_if(assets.begin(),
                              assets.end(),
                              [&, assetType](const AssetManager& asset)
                              {
                                 return(asset.getAssetType()==assetType);
                              });

    auto[details, direction] = iter_found->getTextureDetails();
    auto rows_in_image    = details.at(0);
    auto columns_in_image = details.at(1);
    auto rows_in_player_texture = 1;
    auto columns_in_player_texture = 1;

    CHECK(rows_in_image == rows_in_player_texture);
    CHECK(columns_in_image == columns_in_player_texture);
}

TEST_CASE("PlayerBullet Asset details are correctly stored and retrieved successfully")
{
    AssetManager assetManager{};
    AssetManager::loadTextureDetails();
    auto assets = assetManager.getAssetInfo();
    AssetManager::AssetType assetType = AssetManager::AssetType::BULLET;

    auto iter_found = find_if(assets.begin(),
                              assets.end(),
                              [&, assetType](const AssetManager& asset)
                              {
                                 return(asset.getAssetType()==assetType);
                              });

    auto[details, direction] = iter_found->getTextureDetails();
    auto rows_in_image    = details.at(0);
    auto columns_in_image = details.at(1);
    auto rows_in_player_texture = 1;
    auto columns_in_player_texture = 1;

    CHECK(rows_in_image == rows_in_player_texture);
    CHECK(columns_in_image == columns_in_player_texture);
}

TEST_CASE("Mushroom Asset details are correctly stored and retrieved successfully")
{
    AssetManager assetManager{};
    AssetManager::loadTextureDetails();
    auto assets = assetManager.getAssetInfo();
    AssetManager::AssetType assetType = AssetManager::AssetType::MUSHROOM;

    auto iter_found = find_if(assets.begin(),
                              assets.end(),
                              [&, assetType](const AssetManager& asset)
                              {
                                 return(asset.getAssetType()==assetType);
                              });

    auto[details, direction] = iter_found->getTextureDetails();
    auto rows_in_image    = details.at(0);
    auto columns_in_image = details.at(1);
    auto rows_in_player_texture = 2;
    auto columns_in_player_texture = 4;

    CHECK(rows_in_image == rows_in_player_texture);
    CHECK(columns_in_image == columns_in_player_texture);
}


TEST_CASE("Centipede Asset details are correctly stored and retrieved successfully")
{
    AssetManager assetManager{};
    AssetManager::loadTextureDetails();
    auto assets = assetManager.getAssetInfo();
    AssetManager::AssetType assetType = AssetManager::AssetType::CENTIPEDE;

    auto iter_found = find_if(assets.begin(),
                              assets.end(),
                              [&, assetType](const AssetManager& asset)
                              {
                                 return(asset.getAssetType()==assetType);
                              });

    auto[details, direction] = iter_found->getTextureDetails();
    auto rows_in_image    = details.at(0);
    auto columns_in_image = details.at(1);
    auto rows_in_player_texture = 2;
    auto columns_in_player_texture = 8;

    CHECK(rows_in_image == rows_in_player_texture);
    CHECK(columns_in_image == columns_in_player_texture);
}

TEST_CASE("Scorpion Asset details are correctly stored and retrieved successfully")
{
    AssetManager assetManager{};
    AssetManager::loadTextureDetails();
    auto assets = assetManager.getAssetInfo();
    AssetManager::AssetType assetType = AssetManager::AssetType::SCORPION;

    auto iter_found = find_if(assets.begin(),
                              assets.end(),
                              [&, assetType](const AssetManager& asset)
                              {
                                 return(asset.getAssetType()==assetType);
                              });

    auto[details, direction] = iter_found->getTextureDetails();
    auto rows_in_image    = details.at(0);
    auto columns_in_image = details.at(1);
    auto rows_in_player_texture = 1;
    auto columns_in_player_texture = 4;

    CHECK(rows_in_image == rows_in_player_texture);
    CHECK(columns_in_image == columns_in_player_texture);
}

TEST_CASE("Spider Asset details are correctly stored and retrieved successfully")
{
    AssetManager assetManager{};
    AssetManager::loadTextureDetails();
    auto assets = assetManager.getAssetInfo();
    AssetManager::AssetType assetType = AssetManager::AssetType::SPIDER;

    auto iter_found = find_if(assets.begin(),
                              assets.end(),
                              [&, assetType](const AssetManager& asset)
                              {
                                 return(asset.getAssetType()==assetType);
                              });

    auto[details, direction] = iter_found->getTextureDetails();
    auto rows_in_image    = details.at(0);
    auto columns_in_image = details.at(1);
    auto rows_in_player_texture = 2;
    auto columns_in_player_texture = 8;

    CHECK(rows_in_image == rows_in_player_texture);
    CHECK(columns_in_image == columns_in_player_texture);
}
