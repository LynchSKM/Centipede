#include "SplashScreen.h"
#include <string>
using namespace std::literals::string_literals;
SplashScreen::SplashScreen()
{
    // Load background image for splash screen:
    //splashScreenTexture_.loadFromFile("Assets/background.png"s);
    //ctor
}

void SplashScreen::show(sf::RenderWindow& render_window){
    // Load background texture:
    //sf::Sprite background_sprite;
    //background_sprite.setTexture(splashScreenTexture_);

    // Load Font:
    splashScreenFont_.loadFromFile("Assets/Font.ttf"s);
    auto half = 2.0f;
    auto game_title = "Centipede"s;
    sf::Text splash_screen_title(game_title, splashScreenFont_);

    splash_screen_title.setCharacterSize(58);
    splash_screen_title.setFillColor(sf::Color::Green);
    splash_screen_title.setStyle(sf::Text::Bold);
    sf::FloatRect titleRect = splash_screen_title.getLocalBounds();
    splash_screen_title.setOrigin(titleRect.left + titleRect.width/half,
    titleRect.top  + titleRect.height/half);
    splash_screen_title.setPosition(render_window.getSize().x/half, render_window.getSize().y/7);

    sf::Texture controls_texture;
    controls_texture.loadFromFile("Assets/Splash_Controls.png");
    controls_texture.setSmooth(true);
    sf::Sprite controls_sprite;
    controls_sprite.setTexture(controls_texture);
    controls_sprite.scale(sf::Vector2f{0.8, 0.8});
    controls_sprite.setOrigin(controls_texture.getSize().x/half, controls_texture.getSize().y/half);
    controls_sprite.setPosition(render_window.getSize().x/half, render_window.getSize().y/half+50);

    render_window.clear();
    //render_window.draw(background_sprite);
    render_window.draw(splash_screen_title);
    render_window.draw(controls_sprite);
    render_window.display();

    // Poll for keyboard event Spacebar pressed to start game:
    sf::Event event;
    while(true)
    {
        while(render_window.pollEvent(event)){
            if(event.key.code == sf::Keyboard::Enter){return;}
            if(event.type == sf::Event::Closed)
            {
                render_window.close();
                return;
            }
        }//while
    }//while

}//show

SplashScreen::~SplashScreen()
{
    //dtor
}
