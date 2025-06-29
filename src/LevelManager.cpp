#include "../headers/LevelManager.h"

void LevelManager::updateLevel(const float deltaTime) {
	if (currentLevel > 5)
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