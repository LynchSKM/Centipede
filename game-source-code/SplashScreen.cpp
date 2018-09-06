#include "SplashScreen.h"
#include <string>
using namespace std::literals::string_literals;
SplashScreen::SplashScreen()
{
    // Load background image for splash screen:
    //splashScreenTexture_.loadFromFile("Assets/Game.png"s);
    //ctor
}

void SplashScreen::show(sf::RenderWindow& render_window){
    // Load background texture:
    //sf::Sprite background_sprite;
    //background_sprite.setTexture(splashScreenTexture_);

    // Load Font:
    splashScreenFont_.loadFromFile("Assets/Font.otf"s);

    auto game_title = "Centipede"s;
    sf::Text splash_screen_title(game_title, splashScreenFont_);
    splash_screen_title.setPosition(render_window.getSize().x/3, render_window.getSize().y/3);
    splash_screen_title.setCharacterSize(60);
    splash_screen_title.setFillColor(sf::Color::Red);
    splash_screen_title.setStyle(sf::Text::Bold);

    auto game_controls = "Controls"
                         "\n ..."s;

    sf::Text splash_controls_text(game_controls, splashScreenFont_);
    splash_controls_text.setPosition(render_window.getSize().x/5,
                        render_window.getSize().y/3 - render_window.getSize().y/11);
    splash_controls_text.setFillColor(sf::Color::Red);
    splash_controls_text.setStyle(sf::Text::Bold);

    //render_window.draw(background_sprite);
    render_window.draw(sf::Color(0,0,0));
    render_window.draw(splash_screen_title);
    render_window.draw(splash_controls_text);
    render_window.display();

    // Poll for keyboard event Spacebar pressed to start game:
    sf::Event event;
    while(true){
        while(render_window.pollEvent(event)){
            if(event.key.code == sf::Keyboard::Space){return;}
        }//while
    }//while

}//show

SplashScreen::~SplashScreen()
{
    //dtor
}
