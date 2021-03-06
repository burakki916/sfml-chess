#include "ScreenManager.hpp"
#include "ChessScreen.hpp"
#include "MainMenu.hpp"
#include "MultiplayerMenu.hpp"

std::string ScreenManager::currentScreen = "N/A";

const std::string ScreenManager::VALID_SCREEN_NAMES[] = {
	"ChessScreen",
	"MenuScreen",
	"MultiplayerMenuScreen"
};

void ScreenManager::renderScreen() {
	if (ScreenManager::currentScreen == "MenuScreen") {
		MainMenu::render(); 
	}
	else if (ScreenManager::currentScreen == "ChessScreen") {
		ChessScreen::render();
		Piece::render(); 	
	}
	else if (ScreenManager::currentScreen == "MultiplayerMenuScreen") {
		MultiplayerMenu::render();
	}
}

bool ScreenManager::setCurrentScreen(std::string newCurrentScreen) {
	for (auto thisScreenName : ScreenManager::VALID_SCREEN_NAMES) {
		if (thisScreenName == newCurrentScreen) {
			ScreenManager::currentScreen = newCurrentScreen;
			return true;
		}
	}

	return false;
}

std::string ScreenManager::getCurrentScreen() { 
	return ScreenManager::currentScreen; 
}