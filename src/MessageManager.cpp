#include "../headers/MessageManager.h"
#include <iostream>

MessageManager::MessageManager() :
	levelMessages {
		{1, "Eyes open. First mistake's on you.\n"},
		{2, "You've barely scratched the surface. There's no room for error now.\n"},
		{3, "Every step forward is a mistake you're still alive to regret.\nNevertheless, you've lasted longer than most. That won't go unnoticed.\n"},
		{4, "You've run out of predictable problems.\n"},
		{5, "Final contact expected. Interpretation is up to you.\n"}
	},

	eventMessages {
		{"inventoryMsg", "Commanding Officer to Delta Force: prepare for engagement.\nSelect your weapon.\n"},
		{"emptyMag", "Empty magazine. You're on your own now.\n"},
		{"lowHP", "Vitals unstable. You're one decision away from silence.\n"},
		{"perk_lowHP", "Stabilization in progress. You're not dead yet, technically.\n"},
		{"perk_midHP", "Just enough to fake stability.\n"},
		{"perk_highHP", "Full health. Try doing something reckless.\n"},
		{"perk_speed", "Tactical sprint authorized. Still a bad idea to run in circles.\n"},
		{"perk_damage", "Firepower recalibrated. Precision still recommended.\n"},
		{"perk_regen", "Recovery loop initiated. Even machines envy this tech.\n"},
		{"perk_shield", "Shield activated. Protecting you from your own tactical genius.\n"},
		{"default", "Unrecorded anomaly detected. Orders pending... or missing.\n"},
		{"gameOver", "Mission terminated. File closed with questions pending.\nYou've proved one thing: limits still exist.\n"},
		{"gameWin", "Mission accomplished. You've succeeded where most would have failed. The victory's yours.\n"},
		{"epilogue", "But now that the dust settles, the next mission is already on the horizon.\nA different journey, one that won't be defined by past victories."
						"The ground shifts, and only the adaptable survive.\nUntil then, take this moment for yourself - the world can wait."},
		{"restart", "Press ENTER to restart the game.\n"},
		{"exit", "Abort mission? Press ESC. Those unwilling to follow through aren't fit to be part of this unit.\n"}
	} {}


std::string MessageManager::getLevelMessage(const int level) const {
	if (levelMessages.contains(level)) {
		return levelMessages.at(level);
	}
    return "Things won't get easier.\n";
}

std::string MessageManager::getEventMessage(const std::string& eventKey) const {
	if (eventMessages.contains(eventKey))
		return eventMessages.at(eventKey);

    return eventMessages.at("default");
}