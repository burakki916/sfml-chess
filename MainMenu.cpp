#include "MainMenu.hpp"
sf::Vector2f MenuButton::buttonDem;
sf::Texture MenuButton::buttonTex;
sf::Font MenuButton::buttonFont;
std::vector<MenuButton> MainMenu::buttons; 
sf::Texture MainMenu::titleBarTexture;
sf::RectangleShape MainMenu::titleBar; 
MainMenu::MainMenu()
{
	
}
	
MainMenu::~MainMenu()
{
	
}
void MainMenu::init() {
    MenuButton::initButtonsInfo();
    if(!titleBarTexture.loadFromFile("resources/SFML-CHESS.png")){
        std::cout << "resources/SFML-CHESS.png NOT FOUND" << std::endl;
    }
    titleBar.setTexture(&titleBarTexture);
    titleBar.setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.15));
    titleBar.setFillColor(sf::Color::White);
    titleBar.setSize(sf::Vector2f(500,50));
    titleBar.setOrigin(titleBar.getSize().x/2,titleBar.getSize().y/2);
    {
        auto something = new MenuButton("Single Player");
        something->setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.30));
        buttons.push_back(*something);
    }
    {
        auto something = new MenuButton("Multiplayer");
        something->setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.40));
        buttons.push_back(*something);
    }
    {
        auto something = new MenuButton("Settings");
        something->setPosition(sf::Vector2f(Window::getSize().x/2,Window::getSize().y*0.50));
        buttons.push_back(*something);
    }
    
}
void MainMenu::render() {
    Window::draw(titleBar);
    for(auto itr : MainMenu::buttons){
        itr.render(); 
    }
}



