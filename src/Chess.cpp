#include "Chess.hpp"  
	
Chess::Chess(Window* l_window)
    : m_window(l_window)
{
    tilesColors = std::make_pair(sf::Color::Red, sf::Color::Blue);
    TilesSetUp(); 
}
	
Chess::~Chess()
{
	
}

void Chess::Render(Window* l_window) {
   /* //make this work later or smth, kept getting a squiggle i didnt understand. 
    for(const auto curTile : Tiles ){
        l_window->Draw(curTile); 
    }
    */
   for(int i = 0; i<Tiles.size(); i++){ // itterates through the tiles and draws em. 
       l_window->Draw(Tiles.at(i)); 
   }

}

void Chess::TilesSetUp() {
    
    sf::Vector2f tileDemensions(m_window->GetWindowSize()->x/8, m_window->GetWindowSize()->y/8);
    //later instead of using window size make it such that the riles depend on a "room" length and width of the maximium size square that can fit within the window. 
    for(int coloumns = 0; coloumns<8;coloumns++){
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
            Tiles.push_back(tempRec);
        }
    }
}
