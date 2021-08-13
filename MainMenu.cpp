#include "MainMenu.hpp"
#include "ScreenManager.hpp"

std::vector<MenuButton*> MainMenu::buttons; 
sf::Texture MainMenu::titleBarTexture;
sf::RectangleShape MainMenu::titleBar;

MenuButton* MainMenu::singlePlayerButton;
MenuButton* MainMenu::multiplayerButton;
MenuButton* MainMenu::settingsButton;

void MainMenu::initialize() {
    titleBarTexture.loadFromFile("resources/SFML-CHESS.png");
    
    titleBar.setTexture(&titleBarTexture);
    titleBar.setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.15));
    titleBar.setFillColor(sf::Color::White);
    titleBar.setSize(sf::Vector2f(500,50));
    titleBar.setOrigin(titleBar.getSize().x/2,titleBar.getSize().y/2);
    
    singlePlayerButton = new MenuButton("SinglePlayer", "Single Player");
    singlePlayerButton->setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.30));
    buttons.push_back(singlePlayerButton);
   
    multiplayerButton = new MenuButton("Multiplayer", "Multiplayer");
    multiplayerButton->setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.40));
    buttons.push_back(multiplayerButton);
  
    settingsButton = new MenuButton("Settings", "Settings");
    settingsButton->setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.50));
    //buttons.push_back(settingsButton);
}

void MainMenu::render() {
    Window::draw(titleBar);
    for (auto itr : MainMenu::buttons) {
        itr->render();
    }
}

MenuButton* MainMenu::clickedButton(sf::Vector2i screenPosition) {
    if (ScreenManager::getCurrentScreen() == "MenuScreen") {
        for (auto thisButton : MainMenu::buttons) {
            if (thisButton->contains(screenPosition)) {
                return thisButton;
            }
        }
    }

    return NULL;
}