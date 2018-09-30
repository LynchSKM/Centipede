#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H

#include <string>
#include <fstream>

using std::string;
using std::ios;
using std::fstream;

/** \class HighScoreManager
 *  \brief A class that reads and writes the high score to a textfile.
 *  \author 1043475 Lynch Mwaniki and 1076467 Madimetja Sethosa.
 *	\version 3.0
 */

class HighScoreManager
{
    public:

        /** \brief Default Constructor. Creates HighScoreManger object.
         */
        HighScoreManager();

        /** \brief Returns the high score of the game.
         *  \return int
         */
        int getHighScore();

        /** \brief Sets the high score of the game.
         *  \param score is of type int.
         *  \return void
         */
        void setHighScore(int score);

         /** \brief Default Destructor. Destroys HighScoreManger object.
          */
        ~HighScoreManager();

    private:
        int highScore_;		/**< An int variable that holds the high score.*/
        fstream file_; 		/**< A variable that holds the text file.*/
        string filePath_;	/**< A variable that holds the path to the text file.*/
};

#endif // HIGHSCOREMANAGER_H
