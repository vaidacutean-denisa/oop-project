#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "../headers/MessageManager.h"

class LevelManager {
    int currentLevel;
    float levelTimer;
    float levelDuration;

public:
    // constructor
    explicit LevelManager();

    // methods
    void updateLevel(float deltaTime);
    // void displayLevelMessage() const;
    // void setLevelDuration(float newDuration);
	void resetLevel();

    // getters & setters
    int getCurrentLevel() const;
};

#endif //LEVELMANAGER_H
