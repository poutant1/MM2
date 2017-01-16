#include "world.hpp"
#include "object.hpp"
#include "vehicle.hpp"
#include "projectile.hpp"
#include "map.hpp"
#include <vector>

/**
Adds a vehicle smart pointer to world.
*/
void World::addVehicle(VehiclePtr v) {
	vehicles.push_back(std::move(v));
}

/**
Adds a projectile smart pointer to world.
*/
void World::addProjectile(ProjectilePtr p) {
	projectiles.push_back(std::move(p));
}
/**
Adds the game map to world.
*/
void World::addMap(MapPtr m) {
	map = m;
}
/**
Adds a wall smart pointer to world.
*/
void World::addWall(WallPtr w) {
    walls.push_back(std::move(w));
}
/**
Adds the map checkpoints to world.
*/
void World::addCheckPoints(std::vector<std::shared_ptr<CheckPoint>> c) {
    checkpoints = std::move(c);
}
/**
Adds mines to world.
*/
void World::addMines(std::vector<std::shared_ptr<Mine>> m) {
    mines = std::move(m);
}

/**
 Reads vehicle info from maps
 */
void World::addVehicleInfo(std::shared_ptr<struct VehicleInfo> vi) {
    vehicleInfo = std::move(vi);
}

/**
 A method to get the vehicles inside the world
 */
std::vector<VehiclePtr> World::getVehicles() const {
	return vehicles;
}

/**
A method to get the projectiles inside the world
*/
std::vector<ProjectilePtr> World::getProjectiles() const {
	return projectiles;
}
/**
Returns the game map
*/
MapPtr World::getMap() const {
	return map;
}
/**
Sets a font for world.
*/
void World::setFont(std::shared_ptr<sf::Font> f){
    font = f;
}
/**
gets the walls from world.
*/
std::vector<WallPtr> World::getWalls() const {
    return walls;
}
/**
gets the map checkpoints.
*/
std::vector<std::shared_ptr<CheckPoint>> World::getCheckPoints() const {
    return checkpoints;
}
/**
Gets a list of mines from world.
*/
std::vector<std::shared_ptr<Mine>> World::getMines() const {
    return mines;
}
/**
 A Method to fetch vehicle info from world.
*/
std::shared_ptr<VehicleInfo> World::getVehicleInfo() const {
    return vehicleInfo;
}

/**
 Updates the game state. This includes both the game physics as well as player input.
 */
void World::updateState(double dt) {
	for(auto v : vehicles) {
		v->updateState(dt);
	}
    if (projectiles.size() > 0) {
        if (projectiles[0]->maxDistanceSurpassed()) {
            projectiles.erase(projectiles.begin());
        }
    }
    for(auto i = projectiles.begin(); i != projectiles.end(); i++) {
        if ((*i)->isHit()) {
            projectiles.erase(i);
            i--;
        } else { (*i)->updateState(dt); }
	}
    for(auto m : getMines()) {
        m->updateState();
    }
}
/**
Draws the game world to a window.
*/
void World::draw(Window &w) {
    // Get views for split screen
    auto views = setViews(w);
    for (unsigned int i = 0; i < views.size(); i++) {
        // Set player view
        w.setView(views[i]);
        getMap()->draw(w);
        for(auto v : vehicles) {
            v->draw(w);
        }
        for(auto p : projectiles) {
            p->draw(w);
        }
        for(auto m : mines) {
            m->draw(w);
        }
    }
}
/**
Sets the split-screen view necessary for 2-player play and returns a list of the views.
*/
std::vector<sf::View> World::setViews(Window &w) const {
    std::vector<sf::View> views;
    
    // Get map parameters
    int mapw = map->getWidth()*map->getTileSize().x;
    int maph = map->getHeight()*map->getTileSize().y;
    
    // Create player 1 view
    sf::Vector2u wsize = w.getSize();
    sf::View player1View = w.getDefaultView();
    player1View.setSize(0.5*wsize.x, wsize.y);
    player1View.setViewport(sf::FloatRect(0,0, 0.5f, 1));
    double x = vehicles[0]->getPosition().x;
    double y = vehicles[0]->getPosition().y;
    
    // Check position to draw only until edges
    if (x < wsize.x/4) x = wsize.x/4; else if(x > mapw - wsize.x/4) x = mapw - wsize.x/4;
    if (y < wsize.y/2) y = wsize.y/2; else if(y > maph - wsize.y/2) y = maph - wsize.y/2;
    
    player1View.setCenter(x,y);
    
    // Create player 2 view
    sf::View player2View = w.getDefaultView();
    player2View.setSize(0.5*wsize.x, wsize.y);
    player2View.setViewport(sf::FloatRect(0.5f, 0, 0.5f, 1));
    x = vehicles[1]->getPosition().x;
    y = vehicles[1]->getPosition().y;
    
    // Check position
    if (x < wsize.x/4) x = wsize.x/4; else if(x > mapw - wsize.x/4) x = mapw - wsize.x/4;
    if (y < wsize.y/2) y = wsize.y/2; else if(y > maph - wsize.y/2) y = maph - wsize.y/2;

    player2View.setCenter(x,y);
    
    // Push views to an iterable
    views.push_back(player1View); views.push_back(player2View);
    return views;
}

