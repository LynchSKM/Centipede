#include "HighScoreManager.h"

HighScoreManager::HighScoreManager() : filePath_{"Assets/High_Score.txt"}{
    //ctor
}

int HighScoreManager::getHighScore(){
    file_.open(filePath_, ios::in);
    file_ >> highScore_;
    file_.close();
    return highScore_;
}

void HighScoreManager::setHighScore(int score){
    highScore_ = score;
    file_.open(filePath_, ios::out);
    file_ << highScore_;
    file_.close();
}

HighScoreManager::~HighScoreManager()
{
    //dtor
}
