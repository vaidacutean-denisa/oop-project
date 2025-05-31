#include "../headers/LevelManager.h"

#include <iostream>

LevelManager::LevelManager()
    : currentLevel(1), levelTimer(0.f), levelDuration(10.f) {}

void LevelManager::updateLevel(const float deltaTime) {
	if (currentLevel > 4)
		return;

	levelTimer += deltaTime;

    if (levelTimer >= levelDuration) {
        currentLevel++;
        levelTimer = 0.f;
    }
}

void LevelManager::resetLevel() {
	currentLevel = 1;
	levelTimer = 0.f;
}

int LevelManager::getCurrentLevel() const {
    return currentLevel;
}