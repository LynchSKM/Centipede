#include "Presentation.h"
#include <iostream>
using std::cout;
using std::endl;
Presentation::Presentation(const unsigned int screen_width, const unsigned int screen_height):
    window_(sf::VideoMode(screen_width, screen_height), "Centipede LM", sf::Style::Close),
    background_(sf::Color(0,0,0)),isLeftPressed_{false}, isRightPressed_{false},
    isUpPressed_{false}, isDownPressed_{false}, isSpacePressed_{false}
{

}
void Presentation::checkInput(const sf::Keyboard::Key key, const bool isPressed)
{
        if(key == sf::Keyboard::Left) isLeftPressed_ = isPressed;
        else if(key == sf::Keyboard::Right) isRightPressed_ = isPressed;
        else if(key == sf::Keyboard::Up) isUpPressed_ = isPressed;
        else if(key == sf::Keyboard::Down) isDownPressed_ = isPressed;
        else if(key == sf::Keyboard::Space) isSpacePressed_ = isPressed;

}

void Presentation::processInputEvents()
{
    sf::Event event;
    while(window_.pollEvent(event)){
        switch(event.type){

            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::KeyPressed:
                checkInput(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                checkInput(event.key.code, false);
                break;
            default:
                break;
        }//switch

    }//while
}
void Presentation::populateSpriteSheets(ObjectType object_type, unsigned int row,
                                    sf::Vector2u imageCount, float switchTime,
                                    Direction direction)
{
    auto iter_map = game_textures.find(object_type);
    // Add to spritesheet for animations:
    SpriteSheet sprite_image{object_type, &(iter_map->second),
                 imageCount, switchTime, row, direction};

    sprite_sheets_.push_back(sprite_image);
}

void Presentation::loadTextures(vector<AssetManager>game_assets)
{
    // Get font:
    auto switch_time = 0.1f;
    for(const auto& asset : game_assets){
        if(asset.getAssetType() == AssetManager::AssetType::FONT)
            font_.loadFromFile(game_assets.at(0).getAssetPath());

        else if(asset.getAssetType() == AssetManager::AssetType::PLAYER){

            sf::Texture texture;
            texture.loadFromFile("Assets/PlayerAlt.png");
            auto temp = pair<ObjectType, sf::Texture>(ObjectType::PLAYER, texture);
            game_textures.insert(temp);

        }//else if
        else if(asset.getAssetType() == AssetManager::AssetType::BULLET){

            sf::Texture texture;
            texture.loadFromFile("Assets/bullet.png");
            auto temp = pair<ObjectType, sf::Texture>(ObjectType::PLAYER_LASER_BULLET, texture);
            game_textures.insert(temp);

        }//else if
        else if(asset.getAssetType() == AssetManager::AssetType::CENTIPEDE){
            sf::Texture texture;
            texture.loadFromFile("Assets/Centipede.png");
            auto object = ObjectType::CENTIPEDE;
            auto temp = pair<ObjectType, sf::Texture>(object, texture);
            game_textures.insert(temp);

            //
            auto row = 0u; // Centipede Head
            populateSpriteSheets(object, row, sf::Vector2u{8,2}, switch_time, Direction::LEFT);
            row = 1u; // Centipede Body
            populateSpriteSheets(object, row, sf::Vector2u{8,2}, switch_time, Direction::LEFT);

        }//else if

    }//for
}


void Presentation::renderWindow(vector<shared_ptr<IEntity>>& game_objects,
                                const int remaining_lives, const int player_score,
                                const int high_score)
{
    window_.clear();
    sf::Sprite gameObjectsSprite;
    auto half = 2;
    for(const auto& object : game_objects){
        if(object->getObjectType()==ObjectType::PLAYER){
            auto iter_map = game_textures.find(ObjectType::PLAYER);
            gameObjectsSprite.setTexture(iter_map->second);
            gameObjectsSprite.setOrigin((iter_map->second).getSize().x/half,
                                        (iter_map->second).getSize().y/half);

        }
        if(object->getObjectType()==ObjectType::PLAYER_LASER_BULLET){
            auto iter_map = game_textures.find(ObjectType::PLAYER_LASER_BULLET);
            gameObjectsSprite.setTexture(iter_map->second);
            gameObjectsSprite.setOrigin((iter_map->second).getSize().x/half,
                                        (iter_map->second).getSize().y/half);

        }


        gameObjectsSprite.setPosition(object->getPosition().getX_pos(), object->getPosition().getY_pos());
        window_.draw(gameObjectsSprite);
    }//for
    window_.display();
}


void Presentation::drawSplashScreen()
{
    SplashScreen splash_screen{};
    splash_screen.show(window_);
}

void Presentation::drawGameOverScreen(const int player_score, const int high_score)
{
    GameOverScreen gameOverScreen;
    gameOverScreen.show(window_, player_score, high_score);

}

void Presentation::drawGameWonScreen(const int player_score, const int high_score)
{
    GameWonScreen gameWonScreen;
    gameWonScreen.show(window_, player_score, high_score);
}

void Presentation::displayLives(const int remaining_lives, const int player_score, const int high_score)
{

}


Presentation::~Presentation()
{
    //dtor
}
