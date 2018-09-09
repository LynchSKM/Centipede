#include "SpriteSheet.h"
#include <cmath>
SpriteSheet::SpriteSheet(ObjectType objectType, sf::Texture* gameObjectTexture,
                         sf::Vector2u imageCount, const float switchTime,
                         unsigned int row, Direction direction):
object_type_{objectType},
image_count_{imageCount},
switch_time_{switchTime},
total_time_{0},
row_{row}, default_direction_{direction}, currentImage_{0, row}
{
    uv_rect_.width  = gameObjectTexture->getSize().x/static_cast<float>(imageCount.x);
    uv_rect_.height = gameObjectTexture->getSize().y/static_cast<float>(imageCount.y);
}

void SpriteSheet::createRect(Direction direction)
{
    // Set offset of uv rect of the texture image:
    uv_rect_.top = currentImage_.y*uv_rect_.height;

    if(direction==default_direction_ || direction==Direction::DOWN || direction==Direction::UP){
        uv_rect_.left  = currentImage_.x*uv_rect_.width;
        uv_rect_.width = std::abs(uv_rect_.width);
    }//if
    else{
        uv_rect_.left  = (currentImage_.x+1)*std::abs(uv_rect_.width);
        uv_rect_.width = -std::abs(uv_rect_.width);
    }//else
}


sf::IntRect SpriteSheet::getTextureRect(Direction direction)
{
    createRect(direction);
    return uv_rect_;
}

sf::IntRect SpriteSheet::getTextureRect(int col)
{
    currentImage_.x = col;
    createRect(default_direction_);
    return uv_rect_;
}

void SpriteSheet::update(const float deltaTime)
{
    // Set total time:
    total_time_+=deltaTime;

    // Check time:
    if(total_time_>=switch_time_){
        total_time_-=switch_time_;
        ++currentImage_.x;

        if(currentImage_.x>=image_count_.x) currentImage_.x = 0;
    }//if
}

SpriteSheet::~SpriteSheet()
{
    //dtor
}


