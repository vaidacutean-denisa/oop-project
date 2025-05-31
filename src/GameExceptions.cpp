#include "../headers/GameExceptions.h"

#include <stdexcept>

GameException::GameException(const std::string& message_) : message(std::move(message_)) {}

const char* GameException::what() const noexcept {
    return message.c_str();
}

ResourceLoadException::ResourceLoadException(const std::string& resourcePath_)
				: GameException("Failed to load resource: " + resourcePath_) {}

GameStateException::GameStateException(const std::string& state_)
				: GameException("Invalid game state: " + state_) {}

PlayerException::PlayerException(const std::string& details_)
				: GameException("Player exception: " + details_) {}