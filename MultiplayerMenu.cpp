#include <iostream>
#include "MultiplayerMenu.hpp"
#include "ScreenManager.hpp"

std::vector<MenuButton*> MultiplayerMenu::buttons;
MenuButton* MultiplayerMenu::hostButton;
MenuButton* MultiplayerMenu::joinButton;

void MultiplayerMenu::initialize() {
    hostButton = new MenuButton("Host", "Host Game");
    hostButton->setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.35));
    buttons.push_back(hostButton);
   
    joinButton = new MenuButton("Join", "Join Game");
    joinButton->setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.45));
    buttons.push_back(joinButton);
}

void MultiplayerMenu::render() {
    for (auto itr : MultiplayerMenu::buttons) {
        itr->render();
    }
}

MenuButton* MultiplayerMenu::clickedButton(sf::Vector2i screenPosition) {
    if (ScreenManager::getCurrentScreen() == "MenuScreen") {
        for (auto thisButton : MultiplayerMenu::buttons) {
            if (thisButton->contains(screenPosition)) {
                return thisButton;
            }
        }
    }

    return NULL;
}