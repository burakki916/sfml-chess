#include <iostream>
#include "Window.hpp"
#include <math.h>
class MenuButton{
	private:
		static sf::Vector2f buttonDem;
		static sf::Texture buttonTex; 
		static sf::Font buttonFont;
		sf::Vector2i location;
		sf::RectangleShape buttonDrawable;
		sf::Text buttonText;
		sf::Text dropShadow;
		void makeDropShadow(){
			dropShadow = buttonText; 
			dropShadow.setFillColor(sf::Color(sf::Color(40,40,40)));
			dropShadow.setPosition(sf::Vector2f(buttonText.getPosition().x+2, buttonText.getPosition().y+3));
		}
	public:
		static void initButtonsInfo(){
			buttonDem = sf::Vector2f(
				Window::getSize().x*0.40 , Window::getSize().y*0.05
			);
			if(!buttonFont.loadFromFile("resources/mcFont.ttf")){
				std::cout << "failed to load font!" << std::endl; 
			}
			if(!buttonTex.loadFromFile("resources/stone.png")){
				std::cout << "failed to load stone.png!" << std::endl; 
			}
			buttonTex.setRepeated(true); 
		}
		MenuButton(std::string text){
			buttonText.setFont(MenuButton::buttonFont);
			buttonText.setString(text);
			buttonText.setFillColor(sf::Color::White);
			buttonText.setCharacterSize(MenuButton::buttonDem.y*0.50);
			buttonText.setOrigin(buttonText.getLocalBounds().width/2,buttonText.getLocalBounds().height/2);
			buttonDrawable.setTexture(&MenuButton::buttonTex);
			buttonDrawable.setTextureRect(sf::IntRect(0,0,MenuButton::buttonDem.x/4,MenuButton::buttonDem.y/4));
			buttonDrawable.setSize(buttonDem);
			buttonDrawable.setOrigin(MenuButton::buttonDem.x/2,MenuButton::buttonDem.y/2); 
			buttonDrawable.setOutlineThickness(3);
			buttonDrawable.setOutlineColor(sf::Color::Black);
			makeDropShadow(); 
		}
		void render(){
			Window::draw(buttonDrawable);
			Window::draw(dropShadow);
			Window::draw(buttonText);
		}
		void setPosition(sf::Vector2f newPosition){
			buttonText.setPosition(newPosition);
			buttonDrawable.setPosition(newPosition); 
			makeDropShadow(); 
		}  
		void setSize(sf::Vector2f newSize){
			buttonDrawable.setSize(newSize);
			buttonText.setCharacterSize(newSize.y*0.80);
		} 
};
