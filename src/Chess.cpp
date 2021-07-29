#include "Chess.hpp"  
#include "cmath"
Chess::Chess(Window* l_window)
    : m_window(l_window)
{
    tilesColors = std::make_pair(sf::Color(130,73,11), sf::Color(212, 187, 0));
    m_window->GetEventManager()->AddCallback("MousePos",&Chess::highlightBox,this);
    if(!woodTexture.loadFromFile("src/mcWood.jpg")){
        woodTexture.loadFromFile("src/mcWood.jpg");
        std::cout << "ERROR: Can't find texture : \"mcWood.jpg\""<<std::endl;
    }
    TilesSetUp(); 
}
	
Chess::~Chess()
{
	
}

void Chess::Render(Window* l_window) {
    //make this work later or smth, kept getting a squiggle i didnt understand. 
    for(const auto cur : Tiles ){
        for(auto curTile : cur )
        l_window->Draw(curTile); 
    } // a
    l_window->Draw(highlightedCube);
}

void Chess::TilesSetUp() {
    
    sf::Vector2f tileDemensions(m_window->GetWindowSize()->x/8, m_window->GetWindowSize()->y/8);
    //later instead of using window size make it such that the riles depend on a "room" length and width of the maximium size square that can fit within the window. 
    for(int coloumns = 0; coloumns<8;coloumns++){
        std::vector<sf::RectangleShape> tempRow; 
        for(int rows = 0; rows<8; rows++){
            sf::RectangleShape tempRec;
            int position = coloumns*7 + rows;
            if(position %2 ==1){
                tempRec.setFillColor(tilesColors.first);
            } else {
                tempRec.setFillColor(tilesColors.second);
            }
            tempRec.setSize(tileDemensions);
            tempRec.setPosition(rows*tileDemensions.x,coloumns*tileDemensions.y);
            tempRec.setTexture(&woodTexture);
            tempRow.push_back(tempRec);
        }
        Tiles.push_back(tempRow); 
    }
}

void Chess::highlightBox(EventDetails* l_details) {
        sf::Vector2f tileDemensions(m_window->GetWindowSize()->x/8, m_window->GetWindowSize()->y/8);
        sf::Vector2f highLightPos; 
        highLightPos.x = (ceil(((float)l_details->m_mouse.x / (float)m_window->GetWindowSize()->x)*8)-1) * tileDemensions.x;
        highLightPos.y = (ceil(((float)l_details->m_mouse.y / (float)m_window->GetWindowSize()->y)*8)-1) * tileDemensions.y;
        std::cout << "x: " <<highLightPos.x  << std::endl; 
        std::cout << "y: " << highLightPos.y << std::endl; 
        highlightedCube.setSize(tileDemensions);
        highlightedCube.setFillColor(sf::Color::Black);
        highlightedCube.setPosition(highLightPos);
        //std::cout << "ran !" << std::endl;

}
