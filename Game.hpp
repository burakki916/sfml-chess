#pragma once

class Game {
	public:
		// Perform any initializations. Called by main.
		// This is the function that calls the initialization methods of all other classes.
		static void initialize();
		
		// Called every frame. Called by main
		// Call necessary run/update functions in other classes.
		static void run();

		// Handles renderings
		// Should hand control to other classes as much as possible.
		static void render();
};
