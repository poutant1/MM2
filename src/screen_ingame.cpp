#include "screen_ingame.hpp"
#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "playerinput.hpp"
#include "vehicle.hpp"
#include <vector>
#include <iostream>
#include <memory>


int ScreenInGame::Run(sf::RenderWindow &window) {
    
    std::cout << "In game screen started!" << std::endl;
    
    std::string VEHICLE_PATH1 = "./resources/graphics/vehicle/circleVehicle1.png";
    std::string VEHICLE_PATH2 = "./resources/graphics/vehicle/circleVehicle2.png";
    std::string AMMO_PATH = "./resources/graphics/particle/projectile.png"; 
    //std::string MAP_TILE_PATH = "./resources/maps/tileset.png";
    std::string MAP_TILE_PATH = get_infoptr()->get_tilemap_path();
    
    //Create a world.
    std::shared_ptr<World> world = std::make_shared<World>();
    std::cout << "World created: " << std::endl;

    //create font
    std::string FONT_PATH = "./resources/G_I_R.otf";
    std::shared_ptr<sf::Font> f = std::make_shared<sf::Font>();
    f->loadFromFile(FONT_PATH);
    world->setFont(f);

    //create map
    std::shared_ptr<Map> testmap;
    try{
        testmap = std::make_shared<Map>(Map((get_infoptr()->get_map_path()).c_str(),world));
    }
    catch(std::string e){
        std::cerr << e << std::endl;
        return -1;
    }
    std::cout << "Map created: " << std::endl;
    
    testmap->setTilesetPath(MAP_TILE_PATH);
    if (!testmap->loadTileMap())
        return -1;
    
    //load walls
    testmap->createWalls(world);
    
    //load checkpoints
    world->addCheckPoints(testmap->getCheckPoints());
    
    //load obstacles
    world->addMines(testmap->getMines());
    
    //Create mine texture
    std::string MINE_PATH = "./resources/graphics/particle/mine.png";
    sf::Texture mineTex; mineTex.loadFromFile(MINE_PATH);
    for (auto& o : world->getMines()) {
        (*o).setTexture(mineTex);
    }

    //Add the map to the world.
    world->addMap(testmap);
    
    //Create a player.
    std::shared_ptr<PlayerInput> p1 = std::make_shared<PlayerInput>();
    p1->setKeyUp(get_infoptr()->getPlayerInput(0)->getKeyUp());
    p1->setKeyDown(get_infoptr()->getPlayerInput(0)->getKeyDown());
    p1->setKeyLeft(get_infoptr()->getPlayerInput(0)->getKeyLeft());
    p1->setKeyRight(get_infoptr()->getPlayerInput(0)->getKeyRight());
    p1->setKeyShoot(get_infoptr()->getPlayerInput(0)->getKeyShoot());
    
    //Find starting positions for vehicles
    auto cp = world->getCheckPoints().end(); cp--;
    Vector2d pos1 = (*cp)->getPosition(); pos1.y += (*cp)->getHeight()/4;
    Vector2d pos2 = pos1; pos2.y += (*cp)->getHeight()/2;
    //Create a vehicle.
    std::shared_ptr<VehicleInfo> vi = world->getVehicleInfo();
    std::shared_ptr<Vehicle> v1 = std::make_shared<Vehicle>(
                        Vehicle(vi->position1, vi->orientation,
                        vi->maxSp, vi->maxF, vi->mass, p1,world));
    v1->setTexture(VEHICLE_PATH1);
    v1->setAmmoTexture(AMMO_PATH);
    //Add the vehicle to the world.
    world->addVehicle(v1);
    
    //Create another player.
    std::shared_ptr<PlayerInput> p2 = std::make_shared<PlayerInput>();
    p2->setKeyUp(get_infoptr()->getPlayerInput(1)->getKeyUp());
    p2->setKeyDown(get_infoptr()->getPlayerInput(1)->getKeyDown());
    p2->setKeyLeft(get_infoptr()->getPlayerInput(1)->getKeyLeft());
    p2->setKeyRight(get_infoptr()->getPlayerInput(1)->getKeyRight());
    p2->setKeyShoot(get_infoptr()->getPlayerInput(1)->getKeyShoot());
    
    //Create another vehicle.
    std::shared_ptr<Vehicle> v2 = std::make_shared<Vehicle>(Vehicle(vi->position2,
                    vi->orientation, vi->maxSp, vi->maxF, vi->mass, p2,world));
    v2->setTexture(VEHICLE_PATH2);
    v2->setAmmoTexture(AMMO_PATH);
    //Add the second vehicle to the world.
    world->addVehicle(v2);
    
    //create clock for graphics
    sf::Clock fpstimer;
    float graphicsTime = 0.0166f;
    sf::Time frametime = sf::seconds(graphicsTime);

    //create clock for physics
    sf::Clock phystimer;
    float physicsTime = graphicsTime/5;
    sf::Time phystime = sf::seconds(physicsTime);
    
    double timeStep = physicsTime/graphicsTime;
    
    // Loop for drawing while window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last
        // iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
                std::cout << "In game screen exited!" << std::endl;
                return 2;
            }
            
            // The escape key was pressed
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)) {
                std::cout << "Returning to menu" << std::endl;
                return 0;
            }
        }
        
        for (auto& v : world->getVehicles()) {
            if (v->getLap() == world->getLapTotal()) return 2;
        }
        
        //if it's time to draw things
        if (fpstimer.getElapsedTime() >= frametime){
            //reset timer
            fpstimer.restart();
            // Clear old drawings
            window.clear();
            
            
            //Draw the world. Will ultimately make call 'window.draw(spriteOfObject)' on each object and the map's draw function.
            world->draw(window);
            
            // Copy buffer to window
            window.display();
        }
        //if it's time to update the state of the world
        if (phystimer.getElapsedTime() >= phystime) {
            //reset timer
            phystimer.restart();
            //update world's state
            world->updateState(timeStep);
        }
    }
    return 0;
    
    
    
}
