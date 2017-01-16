#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <memory>
#include "screen_menu.hpp"
#include "maplist.hpp"

enum menuChoices{
    START_GAME,
    CHOOSE_MAP,
    CHANGE_KEYS,
    QUIT_GAME
    };

/**
A structure for holding the menu state in.
*/
typedef struct Menu{
    int main_op=0,map_choice=0, player_choice=0,key=0,chosen_map = 0;
    bool in_main=true, in_map=false, in_keys=false,in_p = false; 
}Menu;

void drawmenu(Menu& m, sf::RenderWindow& w, sf::Sprite & menup, sf::Font & f, Maplist& ml);
void drawmain(Menu& m, sf::RenderWindow& w, sf::Sprite& menup, sf::Font& f);
void drawmap(Menu& m, sf::RenderWindow& w, sf::Sprite& menup, sf::Font& f, Maplist& ml);
void drawkeys(Menu& m, sf::RenderWindow& w, sf::Sprite& menup, sf::Font& f);
void drawplayer(Menu& m, sf::RenderWindow& w, sf::Sprite& menup, sf::Font& f);


int ScreenMenu::Run(sf::RenderWindow& window) {
    
    // Set up menu screen for drawing
    std::string menupointerpath = "./resources/graphics/menu/menupointer.png";
    //load font
    std::string fontpath = "./resources/G_I_R.otf"; 
    sf::Font font;
    if (!font.loadFromFile(fontpath))
        return EXIT_FAILURE;
    
    std::string maplistpath = "./resources/maps/maplist.txt";
    Maplist maplist;
    try{
        maplist = createMaplist(maplistpath);
    }
    catch (char const* s){
        std::cerr << s << std::endl;
        return -1;
    }
    sf::View view = window.getDefaultView();
    window.setView(view);
    
    sf::Texture menuPointerTex;
    if(!menuPointerTex.loadFromFile(menupointerpath))
        return -1;
    sf::Sprite menupointer(menuPointerTex); 
    //set default keys
    PlayerInput p1;
    p1.setKeyUp(sf::Keyboard::Up);
    p1.setKeyDown(sf::Keyboard::Down);
    p1.setKeyLeft(sf::Keyboard::Left);
    p1.setKeyRight(sf::Keyboard::Right);
    p1.setKeyShoot(sf::Keyboard::Space);
    PlayerInput p2;
    p2.setKeyUp(sf::Keyboard::W);
    p2.setKeyDown(sf::Keyboard::S);
    p2.setKeyLeft(sf::Keyboard::A);
    p2.setKeyRight(sf::Keyboard::D);
    p2.setKeyShoot(sf::Keyboard::Tab);
    
    Menu menu_st;
    get_infoptr()->set_map_path(getMapPath(maplist,menu_st.chosen_map));
    get_infoptr()->set_tilemap_path(getTileMapPath(maplist,menu_st.chosen_map));
    
    
    
    bool Running = true;
    sf::Event event;
    while (Running) {
        while (window.pollEvent(event)) {
            
            // Request for closing the window
            if (event.type == sf::Event::Closed) {
                window.close();
                return (-1);
            }
            
            
            if (event.type == sf::Event::KeyReleased){
                //if in main
                if(menu_st.in_main){
                    switch(event.key.code){
                        case(sf::Keyboard::Up):{
                            //raise position if not 0
                            if(menu_st.main_op > START_GAME)
                                menu_st.main_op -=1; 
                            break;
                        }
                        case(sf::Keyboard::Down):{
                            //lower position if not 3
                            if(menu_st.main_op < QUIT_GAME)
                                menu_st.main_op +=1; 
                            break;
                        }
                        
                        case(sf::Keyboard::Right):{
                            //move to right menu or start the game
                            if (menu_st.main_op == START_GAME){
                                get_infoptr()->setPlayerInput(p1,0);
                                get_infoptr()->setPlayerInput(p2,1);
                                return 1;
                            }
                            else if (menu_st.main_op == CHOOSE_MAP){
                                menu_st.in_main = false;
                                menu_st.in_map = true;
                            }
                            else if (menu_st.main_op == CHANGE_KEYS){
                                menu_st.in_main = false;
                                menu_st.in_keys = true;
                                //when we still don't have that menu, we don't make that choice
                                //menu_st.in_main = true;
                                //menu_st.in_keys = false;
                            }
                            else if (menu_st.main_op == QUIT_GAME){
                                return (-1);
                            }
                            break;
                        }
                        default:break;
                    }
                    
                }
                //else: we're in map selection
                else if (menu_st.in_map){
                    switch(event.key.code){
                        case (sf::Keyboard::Up):{
                            if(menu_st.map_choice > 0)
                                menu_st.map_choice = (menu_st.map_choice-1);
                            break;
                        }
                        case (sf::Keyboard::Down):{
                            if ((unsigned)menu_st.map_choice < maplist.size()-1)
                                menu_st.map_choice = (menu_st.map_choice+1);
                            break;
                        }
                        case (sf::Keyboard::Right):{
                            menu_st.chosen_map = menu_st.map_choice;
                            get_infoptr()->set_map_path(getMapPath(maplist,menu_st.chosen_map));
                            get_infoptr()->set_tilemap_path(getTileMapPath(maplist,menu_st.chosen_map));
                            break;
                        }
                        case (sf::Keyboard::Left):{
                            menu_st.in_main = true;
                            menu_st.in_map=false;
                            break;
                        }
                            
                        default:break;
                    }
                }
                //else: we're in change keys
                else if (menu_st.in_keys){
                    switch(event.key.code){
                        case (sf::Keyboard::Up):{
                            if(menu_st.player_choice > 0)
                                menu_st.player_choice-=1;
                            break;
                        }
                        case (sf::Keyboard::Down):{
                            if(menu_st.player_choice < 1)
                                menu_st.player_choice +=1;
                            break;
                        }
                        case(sf::Keyboard::Left):{
                            menu_st.in_main = true;
                            menu_st.in_keys=false;
                            break;
                        }
                        
                        case (sf::Keyboard::Right):{
                                menu_st.in_keys = false;
                                menu_st.in_p = true;
                            break;
                        }
                        default:break;
                    }
                }
                //else:we're in key setup
                else if (menu_st.in_p){
                    PlayerInput * p_ptr = &p1;
                    if (menu_st.player_choice != 0)
                        p_ptr = &p2;
                    switch(menu_st.key){
                        case 0:{//Up
                            p_ptr->setKeyUp(event.key.code);
                            menu_st.key +=1;
                            break;
                        }
                        case 1:{//Down
                            p_ptr->setKeyDown(event.key.code);
                            menu_st.key +=1;
                            break;
                        }
                        case 2:{//Left
                            p_ptr->setKeyLeft(event.key.code);
                            menu_st.key +=1;
                            break;
                        }
                        case 3:{//Right
                            p_ptr->setKeyRight(event.key.code);
                            menu_st.key +=1;
                            break;
                        }
                        case 4:{//Shoot
                            p_ptr->setKeyShoot(event.key.code);
                            menu_st.key =0;
                            menu_st.player_choice=0;
                            menu_st.in_p = false;
                            menu_st.in_keys = true;
                            break;
                        }
                        default:break;
                    }
                    
                }
                std::cout << "in main menu option " << menu_st.main_op << std::endl;
                std::cout << "main: " << menu_st.in_main << " map: " << menu_st.in_map << "keys: " << menu_st.in_keys << std::endl;
            }
            
        }
        
        window.clear();
        
        // Copy buffer to window
        drawmenu(menu_st,window,menupointer,font,maplist);
        window.display();

    }
    return -1;
}

void drawmenu(Menu& m, sf::RenderWindow& w, sf::Sprite& menup, sf::Font& f, Maplist& ml){
    if (m.in_main)
        drawmain(m,w,menup,f);
    else if (m.in_map)
        drawmap(m,w,menup,f, ml);
    else if (m.in_keys)
        drawkeys(m,w,menup,f);
    else if (m.in_p)
        drawplayer(m,w,menup,f);
}

void drawmain(Menu& m, sf::RenderWindow& w, sf::Sprite& menup, sf::Font& f ){
    sf::Text header;
    header.setFont(f);
    header.setCharacterSize(48);
    header.setColor(sf::Color::White);
    header.setString("Main menu");
    
    sf::Text c1,c2,c3,c4;
    c1.setFont(f);
    c2.setFont(f);
    c3.setFont(f);
    c4.setFont(f);
    c1.setString("Start Game");
    c2.setString("Choose map");
    c3.setString("Set Player Keys");
    c4.setString("Quit Game");
    c1.setPosition(200, 100);
    c2.setPosition(200, 200);
    c3.setPosition(200, 300);
    c4.setPosition(200, 400);
    menup.setPosition(100,100+m.main_op*100);
    w.draw(header);
    w.draw(c1);
    w.draw(c2);
    w.draw(c3);
    w.draw(c4);
    w.draw(menup);
}

void drawmap(Menu& m, sf::RenderWindow& w, sf::Sprite& menup, sf::Font& f, Maplist& ml){
    sf::Text header;
    header.setFont(f);
    header.setCharacterSize(48);
    header.setColor(sf::Color::White);
    header.setString("Main menu -> Map selection");
    header.setColor(sf::Color::White);
    sf::Text mp;
    mp.setFont(f);
    mp.setColor(sf::Color::White);
    mp.setPosition(200,200);
    mp.setString(ml[m.map_choice]);
    menup.setPosition(100,200);
    w.draw(mp);
    w.draw(header);
    w.draw(menup);
    if (m.map_choice == m.chosen_map){
        menup.setPosition(100+mp.getGlobalBounds().width+180,200);
        w.draw(menup);
    }
}

void drawkeys(Menu& m, sf::RenderWindow& w, sf::Sprite& menup, sf::Font& f){
    sf::Text header;
    header.setFont(f);
    header.setCharacterSize(48);
    header.setColor(sf::Color::White);
    header.setString("Main menu -> Key setup");
    sf::Text p1,p2;
    p1.setFont(f);
    p2.setFont(f);
    p1.setString("Player 1");
    p2.setString("Player 2");
    p1.setPosition(200, 100);
    p2.setPosition(200, 200);
    menup.setPosition(100, 100+m.player_choice*100);
    
    
    w.draw(header);
    w.draw(p1);
    w.draw(p2);
    w.draw(menup);
}

void drawplayer(Menu& m, sf::RenderWindow& w, sf::Sprite& menup, sf::Font& f){
    sf::Text header;
    header.setFont(f);
    header.setCharacterSize(48);
    header.setColor(sf::Color::White);
    std::string p = "Player 1";
    if (m.player_choice != 0)
        p = "Player 2";
    std::string hs = "Main menu -> Key setup -> " + p;
    header.setString(hs);
    menup.setPosition(100,(1+m.key)*100);
    
    
    std::vector<std::shared_ptr<sf::Text>> v;
    for (int i=0;i<5;i++){
        std::shared_ptr<sf::Text> t = std::make_shared<sf::Text>();
        t->setPosition(200, 100+ 100*i);
        v.push_back(t);
    }
    for (auto t: v){
        t->setFont(f);
        t->setCharacterSize(48);
        t->setColor(sf::Color::White);
    }
    v[0]->setString("Up");
    v[1]->setString("Down");
    v[2]->setString("Left");
    v[3]->setString("Right");
    v[4]->setString("Shoot");
    for (auto t:v){
        w.draw(*t);
    }
    w.draw(menup);
    w.draw(header);
}
