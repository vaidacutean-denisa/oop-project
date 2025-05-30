#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

#include <string>
#include <map>

class MessageManager {
	std::map<int, std::string> levelMessages;
	std::map<std::string, std::string> eventMessages;

public:
	// constructor
	MessageManager();

	// methods
	[[nodiscard]] std::string getLevelMessage(int level) const;
	[[nodiscard]] std::string getEventMessage(const std::string& eventKey) const;
};

#endif //MESSAGEMANAGER_H
