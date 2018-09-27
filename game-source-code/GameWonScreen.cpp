#include "GameWonScreen.h"
using namespace std::literals::string_literals;

GameWonScreen::GameWonScreen()
{
    //ctor
    gameWonTexture_.loadFromFile("Assets/GameWon.png"s);
}

void GameWonScreen::show(sf::RenderWindow& render_window,
          const int& player_score, const int& high_score)
{
    //Load background texture:
    sf::Sprite background_sprite;
    gameWonTexture_.setSmooth(true);
    gameWonTexture_.setSmooth(true);
    gameWonTexture_.setSmooth(true);
    gameWonTexture_.setSmooth(true);
    background_sprite.setTexture(gameWonTexture_);
    background_sprite.setScale(sf::Vector2f(1.5f, 1.5f));
    sf::FloatRect backgroundRect = background_sprite.getLocalBounds();
    background_sprite.setOrigin(backgroundRect.left + backgroundRect.width/2.0f,
    backgroundRect.top  + backgroundRect.height/2.0f);
    background_sprite.setPosition(sf::Vector2f(render_window.getSize().x/2.0f,
                                               render_window.getSize().y/2.0f));

    //Load font:
    font_.loadFromFile("Assets/Font.otf"s);

    auto game_won_title = "\t\t Awesome! \n You defeated us."s;
    sf::Text title(game_won_title, font_);
    title.setCharacterSize(48);
    sf::FloatRect titleRect = title.getLocalBounds();
    title.setOrigin(titleRect.left + titleRect.width/2.0f,
    titleRect.top  + titleRect.height/2.0f);
    //title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Green);
    title.setPosition(sf::Vector2f(render_window.getSize().x/2.0f,
                                   render_window.getSize().y/2.0f - 260));


    // Player score:
    auto score_text = "\t You scored: "s+std::to_string(player_score);
    sf::Text score(score_text, font_);
    score.setCharacterSize(30);
    sf::FloatRect scoreRect = score.getLocalBounds();
    score.setOrigin(scoreRect.left + scoreRect.width/2.0f,
    scoreRect.top  + scoreRect.height/2.0f);
    score.setFillColor(sf::Color(255, 165, 0));
    score.setPosition(sf::Vector2f(render_window.getSize().x/2.0f,
                                   render_window.getSize().y/2.0f+ 230));

    // Highscore:
    auto high_score_text = "\t Highscore: "s+std::to_string(high_score);
    sf::Text game_high_score(high_score_text, font_);
    sf::FloatRect highRect = game_high_score.getLocalBounds();
    game_high_score.setOrigin(highRect.left + highRect.width/2.0f,
    highRect.top  + highRect.height/2.0f);
    game_high_score.setFillColor(sf::Color(255, 165, 0));
    game_high_score.setPosition(sf::Vector2f(render_window.getSize().x/2.0f,
                                             render_window.getSize().y/2.0f +260));


    auto game_won_controls = "Exit -> Press Enter"s;
    sf::Text controls(game_won_controls, font_);
    sf::FloatRect textRect = controls.getLocalBounds();
    controls.setOrigin(textRect.left + textRect.width/2.0f,
                        textRect.top  + textRect.height/2.0f);
    controls.setFillColor(sf::Color::Red);
    controls.setPosition(sf::Vector2f(render_window.getSize().x/2.0f,
                                      render_window.getSize().y/2.0f + 300));


    //Draw:

    // Poll for keyboard event:
    auto changecolour = true;
    auto counter = 0;
    sf::Event event;
    while(true)
    {
        render_window.clear(sf::Color(0,0,0));
        render_window.draw(background_sprite);
        if(changecolour && counter%4 == 0)
        {
            controls.setFillColor(sf::Color::Green);
            title.setFillColor(sf::Color::Red);
            changecolour = !changecolour;
        }else{
            controls.setFillColor(sf::Color::Red);
            title.setFillColor(sf::Color::Green);
            changecolour = !changecolour;
        }
        ++counter;
        render_window.draw(title);
        render_window.draw(controls);
        render_window.draw(score);
        render_window.draw(game_high_score);
        render_window.display();

        while(render_window.pollEvent(event)){
            if(event.key.code == sf::Keyboard::Enter || event.type == sf::Event::Closed){
                render_window.close();
                return;
            }//if
        }//while
    }//while

}//show


GameWonScreen::~GameWonScreen()
{
    //dtor
}
