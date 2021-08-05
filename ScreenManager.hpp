#pragma once
#include <string>
#include "Piece.hpp"

class ScreenManager {
	public:
		static void renderScreen();

		static bool setCurrentScreen(std::string newCurrentScreen);
		static std::string getCurrentScreen();

	private:
		static std::string currentScreen;
		static const std::string VALID_SCREEN_NAMES[];
};