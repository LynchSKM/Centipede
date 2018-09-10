#ifndef PRESENTATION_H
#define PRESENTATION_H

#include <SFML/Graphics.hpp>

#include <map>
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::map;
using std::pair;

#include "IEntity.h"
#include "IMovingEntity.h"
#include "CentipedeSegment.h"

#include "AssetManager.h"
#include "SplashScreen.h"
#include "GameWonScreen.h"
#include "GameOverScreen.h"
#include "SpriteSheet.h"

/** \class Presentation
 *  \brief Uses the SFML Graphics Library to draw all game objects on the screen.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 */

class Presentation
{
    public:
        /** \brief Parametrized Constructor. Creates a Presentation object.
         *  \param screen_width is the width of the screen.
         *  \param screen_height is the height of the screen.
         */
        Presentation(const unsigned int screen_width, const unsigned int screen_height);

        /** \brief Determines the keyboard keys pressed and acts accordingly.
         *  Polling is used by default.
         */
        void processInputEvents();

        /** \brief Checks which key was pressed/released and updates its status.
         * \param is a key of type Key from the sf keyboard
         * \param is a bool stating if there is a key that is pressed.
         */
        void checkInput(const sf::Keyboard::Key key, const bool isPressed);

        /** \brief Displays a Splashscreen at the beginning of the game.
         */
        void drawSplashScreen();

        /** \brief Displays a Game Over Screen at the end of the game.
         *  \param player_score is an int and contains the player's score.
         *  \param high_score is an int and contains the game's high score.
         */
        void drawGameOverScreen(const int player_score, const int high_score);

        /** \brief Displays a Game Won Screen at the end of the game.
         *  \param player_score is an int and contains the player's score.
         *  \param high_score is an int and contains the game's high score.
         */
        void drawGameWonScreen(const int player_score, const int high_score);

        /** \brief Displays the player's lives, current score and the high score
         * of the game.
         *  \param remaining_lives is an int representing the player's lives.
         *  \param player_score is an int that has the player's current score.
         *  \param high_score is an int that has the game's highest score.
         */
        void displayLives(const int remaining_lives, const int player_score,
                          const int high_score);

        /** \brief Draws all the game objects onto the screen. Including the player's
         *  score, lives and the game's highest score.
         * \param game_objects is a vector of IEntity containing all the game objects.
         * \param remaining_lives is an int and contains the number of lives.
         * \param player_score is an int that has the player's current score.
         * \param high_score is an int that has the game's highest score.
         */
        void renderWindow(vector<shared_ptr<IEntity>>& game_objects,
                          const int remaining_lives, const int player_score,
                          const int high_score);

        /** \brief Loads all the game's textures.
         *  \param game_assets is a vector of AssetManager
         */
        void loadTextures(vector<AssetManager> game_assets);

        /** \brief returns a bool indicating whether a key was pressed.
         *  \return a bool indicating key status.
         */
        bool isLeftPressed(){return isLeftPressed_;};

        /** \brief returns a bool indicating whether a key was pressed.
         *  \return a bool indicating key status.
         */
        bool isRightPressed(){return isRightPressed_;};

        /** \brief returns a bool indicating whether a key was pressed.
         *  \return a bool indicating key status.
         */
        bool isUpPressed(){return isUpPressed_;};

        /** \brief returns a bool indicating whether a key was pressed.
         *  \return a bool indicating key status.
         */
        bool isDownPressed(){return isDownPressed_;};

        /** \brief returns a bool indicating whether a key was pressed.
         *  \return a bool indicating key status.
         */
        bool isSpacePressed(){return isSpacePressed_;};

        bool isWindowOpen() const {return window_.isOpen();};

        /** \brief Default Destructor. Destroys a Presentation object.
         */
        ~Presentation();

    private:
        sf::Color background_;
        sf::RenderWindow window_;
        sf::Font font_;

        //
        map<ObjectType, sf::Texture> game_textures;
        vector<SpriteSheet> sprite_sheets_;

        //input keys
        bool isLeftPressed_;
        bool isRightPressed_;
        bool isUpPressed_;
        bool isDownPressed_;
        bool isSpacePressed_;

        /** \brief Generates SpriteSheet objects and saves them into the vector
         *  sprite_sheets_ for the different game objects.
         * \param object_type is of type enum class ObjectType.
         * \param row is an unsigned int indicating the row in the spritesheet to use.
         * \param imageCount is an sf::Vector2u and contains the number of columns and rows.
         * \param switchTime is a float and is the time delay used between images for movement animation.
         * \param direction is the direction the sprite faces in the image loaded as a texture.
         */
        void populateSpriteSheets(ObjectType object_type, unsigned int row,
                                  sf::Vector2u imageCount, float switchTime,
                                  Direction direction);

        /** \brief Updates the animations of game objects that have more than one
         * image to represent movement.
         * \param delta_time is a float that will have the time elapsed from the game loop.
         */
        void updateAnimations(float delta_time);



};

#endif // PRESENTATION_H
