#include <SFML/Graphics.hpp>
#include "screen_end.hpp"
#include <iostream> // For testing

int ScreenEnd::Run(sf::RenderWindow& w) {
    std::cout << "End screen visited!" << std::endl; // Testing that rotation of screens works
    
    std::string TEX_PATH = "./resources/graphics/menu/end.png";
    sf::Texture endtex; endtex.loadFromFile(TEX_PATH);
    sf::Sprite sprite; sprite.setTexture(endtex);
    sf::View view = w.getDefaultView();
    w.setView(view);
    
    bool Running = true;
    sf::Event event;
    
    while(Running) {
        while (w.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                return -1;
            }
            if (event.type == sf::Event::KeyPressed) {
                return 0;
            }
        }
        
        w.clear();
        w.draw(sprite);
        w.display();
    }
    return -1;
}