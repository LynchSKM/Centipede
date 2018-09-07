#include "Presentation.h"

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

void Presentation::renderWindow(vector<shared_ptr<IEntity>>& game_objects,
                                const int remaining_lives, const int player_score,
                                const int high_score)
{

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
