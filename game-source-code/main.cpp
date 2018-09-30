#include "Logic.h"

/** \mainpage Centipede Game
 *  This project was aimed at the development of a 2D game based on Atari's Centipede.
 *  SFML version 2.5.0 was required to be used as the graphics library and C++17
 *  as the chosen standard for compilation.
 *  - The game has a Player that can be moved up, down, left or right in a fixed area
 *  near the bottom of the screen.
 *  - The game has Scorpions, Spiders and Centipedes that the Player can shoot to gain
 *  points and win the game. Each has a different movement when generated on the game
 *  screen adding some difficulty to the game.
 *  - Mushrooms are also generated and can be shot by the Player. These act as obstacles
 *  for the Centipede(s) in the game.
 *  - Mushrooms can be poisoned by Scorpion objects.
 *  - Centipede Segments that are shot turn into Mushroom objects.
 *  - Centipede(s) that touch poisoned Mushrooms dive down into the Player's area.
 */
int main()
{
    Logic centipede_game{};
    centipede_game.run();
    return 0;
}//main
