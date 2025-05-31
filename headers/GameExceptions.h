#ifndef GAMEEXCEPTIONS_H
#define GAMEEXCEPTIONS_H

#include <exception>
#include <string>

class GameException : public std::exception {
protected:
	std::string message;

public:
	explicit GameException(const std::string& message_);
	const char* what() const noexcept override;
};

class ResourceLoadException : public GameException {
public:
	explicit ResourceLoadException(const std::string& resourcePath_);
};

class GameStateException : public GameException {
public:
	explicit GameStateException(const std::string& state_);
};

class PlayerException : public GameException {
public:
	explicit PlayerException(const std::string& details_);
};

#endif //GAMEEXCEPTIONS_H
