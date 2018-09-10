#include "Presentation.h"

Presentation::Presentation(const unsigned int screen_width, const unsigned int screen_height):
    window_(sf::VideoMode(screen_width, screen_height), "Centipede LM", sf::Style::Close),
    background_(sf::Color::Black),isLeftPressed_{false}, isRightPressed_{false},
    isUpPressed_{false}, isDownPressed_{false}, isSpacePressed_{false}
{

}
void Presentation::checkInput(const sf::Keyboard::Key key, const bool isPressed)
{
        if(key == sf::Keyboard::Left) isLeftPressed_ = isPressed;
        else if(key == sf::Keyboard::Right) isRightPressed_ = isPressed;
        else if(key == sf::Keyboard::Up) isUpPressed_ = isPressed;
        else if(key == sf::Keyboard::Down) isDownPressed_ = isPressed;
        else if(key == sf::Keyboard::Space)isSpacePressed_ = isPressed;
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
    auto switch_time = 0.3f;
    for(const auto& asset : game_assets){
        if(asset.getAssetType() == AssetManager::AssetType::FONT)
            font_.loadFromFile(game_assets.at(0).getAssetPath());

        else{
            sf::Texture texture;
            texture.loadFromFile(asset.getAssetPath());


            if(asset.getAssetType() == AssetManager::AssetType::PLAYER){
                texture.setSmooth(true);
                auto temp = pair<ObjectType, sf::Texture>(ObjectType::PLAYER, texture);
                game_textures.insert(temp);

            }// if
            else if(asset.getAssetType() == AssetManager::AssetType::BULLET){
                auto temp = pair<ObjectType, sf::Texture>(ObjectType::PLAYER_LASER_BULLET, texture);
                game_textures.insert(temp);

            }//else if
            else if(asset.getAssetType() == AssetManager::AssetType::CENTIPEDE){
                auto object = ObjectType::CENTIPEDE;
                auto temp = pair<ObjectType, sf::Texture>(object, texture);
                game_textures.insert(temp);

                //
                auto row = 0u; // CentipedeSegment Head
                populateSpriteSheets(object, row, sf::Vector2u{8,2}, switch_time, Direction::LEFT);
                row = 1u; // CentipedeSegment Body
                populateSpriteSheets(object, row, sf::Vector2u{8,2}, switch_time, Direction::LEFT);
            } //else if
        }//else

    }//for
}


void Presentation::renderWindow(vector<shared_ptr<IEntity>>& game_objects,
                                const int remaining_lives, const int player_score,
                                const int high_score)
{
    window_.clear();
    auto half = 2.0f;
    auto iter_map = game_textures.begin();
    for(const auto& object : game_objects){
         sf::Sprite gameObjectsSprite;
        if(object->getObjectType() == ObjectType::PLAYER ||
           object->getObjectType() == ObjectType::PLAYER_LASER_BULLET){
            iter_map = game_textures.find(object->getObjectType());

            // Set Origin:
            gameObjectsSprite.setOrigin((iter_map->second).getSize().x/half,
                                        (iter_map->second).getSize().y/half);
        }
        else{
             // Search for spritesheet:
             auto entity_type = object->getObjectType();
             auto iter_vec = find_if(sprite_sheets_.begin(), sprite_sheets_.end(),
                                        [&, entity_type](const SpriteSheet& sheet){
                           return (sheet.getObjectType()==entity_type);
                           });

            if(object->getObjectType()==ObjectType::CENTIPEDE){
                iter_map = game_textures.find(ObjectType::CENTIPEDE);

                auto centipede_segment = std::dynamic_pointer_cast<CentipedeSegment>(object);
                if(centipede_segment->getBodyType()==CentipedeSegment::BodyType::BODY)
                    ++iter_vec;

                auto rect = iter_vec->getTextureRect(centipede_segment->getDirection());
                gameObjectsSprite.setTextureRect(rect);
                // Set Origin:
                gameObjectsSprite.setOrigin(std::abs(rect.width)/half, rect.height/half);
            }//if
        }

        // Set Texture:
        gameObjectsSprite.setTexture(iter_map->second);

        // Set position:
        gameObjectsSprite.setPosition(object->getPosition().getX_pos(),
                                      object->getPosition().getY_pos());
        window_.draw(gameObjectsSprite);
    }//for
    window_.display();
    auto animation_speed = 0.02f;
    updateAnimations(animation_speed);

}

void Presentation::updateAnimations(float delta_time){
for(auto& sprite_image : sprite_sheets_){
        if(sprite_image.getObjectType()!=ObjectType::MUSHROOM)
            sprite_image.update(delta_time);
    }
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
