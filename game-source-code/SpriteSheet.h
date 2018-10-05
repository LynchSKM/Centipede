#ifndef SPRITESHEET_H
#define SPRITESHEET_H

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include "Direction.h"
#include "ObjectType.h"

/** \class SpriteSheet
 *  \brief A class that crops the texture to the correct image for game objects
 *  to be drawn on the screen. Some of the textures loaded contain more than picture
 *  of an object in the image. This class is used to crop the texture to get the
 *  desired image. This helps with the animation of game objects on the screen.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *  \version 3.0
 */

class SpriteSheet
{
    public:
        /**\brief Parameterized SpriteSheet constructor. Creates a SpriteSheet object.
         *
         * \param objectType is of type enum class ObjectType.
         * \param gameObjectTexture is a pointer to an sf::Texture.
         * \param imageCount is sf::Vector2u and contains the number of rows and columns in the texture.
         * \param switchTime is a float that the the time delay between images.
         * \param row is an unsigned int containing the row where the image can be located.
         * \param direction is of type enum class direction and contains the default
         *	direction the game object faces in the texture.
         */
        SpriteSheet(ObjectType objectType, sf::Texture* gameObjectTexture,
                    sf::Vector2u imageCount, const float switchTime,
                    unsigned int row, Direction direction);

        /**\brief Increments the image currently being looked at in the texture
         * to animate movement.
         * \param deltaTime is a const float that will be used to determine whether current
         * image should be incremented after some delay.
         */
        void update(const float deltaTime);

        /**\brief This function will create a rect shape in the texture so that
         * the correct image is taken from the sprite sheet. It takes in a direction
         * and compares it with the default direction in the texture.
         * \param direction is of type Direction enum class.
         * \return sf::IntRect
         */
        sf::IntRect getTextureRect(Direction direction);

        /**\brief This function will create a rect shape in the texture using an
         * sf::IntRect so that the correct image is taken from the spritesheet.
         * It takes in a int that represents a column in the texture for those
         * that have more than one image and are stationary objects.
         * \param col is an integer containing the column of interest in the texture.
         * \return sf::IntRect
         */
        sf::IntRect getTextureRect(int col);

        /**\brief This function will return the object type.
         * \return ObjectType which is of enum class ObjectType.
         */
        ObjectType getObjectType() const {return object_type_;};

        /** \brief Default Destructor. Destroys a SpriteSheet object.
         */
        ~SpriteSheet();
    private:
        sf::Vector2u image_count_;
        sf::Vector2u currentImage_;
        sf::IntRect uv_rect_;

        float total_time_;
        float switch_time_;
        unsigned int row_;
        Direction default_direction_;
        ObjectType object_type_;

        // Private functions:
        /** \brief This function creates the sf::IntRect around the texture.
         *  \param direction is of type enum class Direction. Contains the direction
         *  the game object is facing.
         */
        void createRect(Direction direction);
};

#endif // SPRITESHEET_H
