#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

template <typename T>
class Singleton {
protected:
	Singleton() = default;
	~Singleton() = default;

	Singleton(const Singleton&) = delete;
	Singleton& operator=(const Singleton&) = delete;
	Singleton(Singleton&&) = delete;
	Singleton& operator=(Singleton&&) = delete;

public:
	static T& getInstance() {
		static T instance;
		return instance;
	}
};

class LevelManager : public Singleton<LevelManager> {
	friend class Singleton;

    int currentLevel;
    float levelTimer;
    float levelDuration;

	// constructor
	LevelManager() : currentLevel(1), levelTimer(0.f), levelDuration(35.f) {}

public:
    // methods
    void updateLevel(float deltaTime);
	void resetLevel();

    // getters & setters
    int getCurrentLevel() const;
};

#endif //LEVELMANAGER_H
