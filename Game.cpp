#pragma once
#include "Game.hpp"
#include "Window.hpp"
#include "ChessScreen.hpp"
#include "EventManager.hpp"

void Game::initialize() {
	Window::initialize();
	ChessScreen::initialize();
}

void Game::run() {
	EventManager::run();
	Game::render();
}

void Game::render() {
	Window::beginDraw();
	ChessScreen::render();
	Window::endDraw();
}