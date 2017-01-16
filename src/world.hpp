#ifndef MM2_WORLD_HPP
#define MM2_WORLD_HPP

#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

class Vehicle;
class Projectile;
class Object;
class Map;
class Wall;
class CheckPoint;
class Mine;
struct VehicleInfo;

typedef sf::RenderWindow Window;

typedef std::shared_ptr<Vehicle> VehiclePtr;
typedef std::shared_ptr<Projectile> ProjectilePtr;
typedef std::shared_ptr<Wall> WallPtr;
typedef std::shared_ptr<CheckPoint> CpPtr;
typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<Mine> MinePtr;


/**
A class that contains the game world and everything in it.
Is responsible for updating the game logic as well as drawing the game world. 
*/

class World {
public :
    void addVehicle(VehiclePtr v);
    void addProjectile(ProjectilePtr p);
    void addWall(WallPtr w);
    void addCheckPoints(std::vector<CpPtr> c);
    void addMines(std::vector<MinePtr> m);
    void addMap(MapPtr m);
    void addVehicleInfo(std::shared_ptr<VehicleInfo>);
    std::vector<VehiclePtr> getVehicles() const;
    std::vector<ProjectilePtr> getProjectiles() const;
    MapPtr getMap() const;
    std::shared_ptr<VehicleInfo> getVehicleInfo() const;
    std::vector<WallPtr> getWalls() const;
    std::vector<CpPtr> getCheckPoints() const;
    std::vector<MinePtr> getMines() const;
    /**
    Returns the total amount of laps in the race.
    */
    int getLapTotal() const { return laptotal; }
    std::vector<sf::View> setViews(Window& w) const;
    void setFont(std::shared_ptr<sf::Font> f);
    
	//Calls every object's updateState-function
	void updateState(double dt);
	//Calls every object's draw-function
	void draw(Window &w);
private :
    std::shared_ptr<struct VehicleInfo> vehicleInfo;
    std::vector<VehiclePtr> vehicles;
    std::vector<ProjectilePtr> projectiles;
    std::vector<WallPtr> walls;
    std::vector<CpPtr> checkpoints;
    std::vector<MinePtr> mines;
    std::shared_ptr<sf::Font> font;
    MapPtr map;
    int laptotal=3;
};


#endif
