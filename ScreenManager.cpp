#include "ScreenManager.hpp"
#include "ChessScreen.hpp"

std::string ScreenManager::currentScreen = "N/A";
const std::string ScreenManager::VALID_SCREEN_NAMES[] = {
	"ChessScreen",
	"MenuScreen"
};

void ScreenManager::renderScreen() {
	if (ScreenManager::currentScreen == "MenuScreen") {
		
	}
	else if (ScreenManager::currentScreen == "ChessScreen") {
		ChessScreen::render();
		Piece::render(); 
	}
}

bool ScreenManager::setCurrentScreen(std::string newCurrentScreen) {
	for (std::string thisScreenName : ScreenManager::VALID_SCREEN_NAMES) {
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