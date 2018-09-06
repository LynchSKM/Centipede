#include "Presentation.h"

Presentation::Presentation(const unsigned int screen_width, const unsigned int screen_height):
    window_(sf::VideoMode(screen_width, screen_height), "Centipede LM", sf::Style::Close),
    background_(sf::Color(0,0,0))
{
    //ctor
}

void Presentation::processInputEvents()
{
    sf::Event event;
    while(window_.pollEvent(event)){
        switch(event.type){

        case sf::Event::Closed:
            window_.close();
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

}

void Presentation::drawGameWonScreen(const int player_score, const int high_score)
{

}

void Presentation::displayLives(const int remaining_lives, const int player_score, const int high_score)
{

}


Presentation::~Presentation()
{
    //dtor
}
