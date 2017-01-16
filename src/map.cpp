#include <string>
#include <fstream>      // std::ifstream
#include <iostream>
#include <sstream>
#include "map.hpp"
#include "objects.hpp"
#include "world.hpp"
#include "tilemap.hpp"

Map::Map(const char* filename, std::shared_ptr<World> w){
    
    world = w;
        std::vector<int> temprow = {}; //Vector for temporary row-storage
        
        std::ifstream ifs(filename, std::ifstream::in);
        if (!ifs.is_open()){
            std::string error = (std::string)"Error: "+ (std::string)filename +(std::string)" file not found";
            throw error;
        }
        std::string line;
    
    
        std::cout<<"Loading map from file: "<<name<<std::endl;
        
        while(std::getline(ifs, line)){
            
            if(!line.compare(std::string("NAME:"))){
                std::getline(ifs, line);
                name = line;
            }
            
            if(!line.compare(std::string("TILES:"))){
                while(std::getline(ifs, line)){
                    if(!line.compare(std::string(""))) break;
                    tiletypes.push_back(line);
                }
            }
        
            if(!line.compare(std::string("MAPMATRIX:"))){
                int wcntr = 0; //Width counter
                int hcntr = 0; //Height counter
                char c = ifs.get();
                //Getting characters until the end of file or a S-char
                while (ifs.good() && c!='S') { 
                    //transform character to hexadecimal
                    std::string s;
                    s.push_back(c);
                    int value = std::stoi(s,NULL,16);
                    temprow.push_back(value);
                    wcntr++; //Increment width counter
                    c = ifs.get();
                    if(c=='\n'){ //Newline encountered
                        mapmatrix.push_back(temprow); 
                        hcntr++; //Increment height counter
                        width = wcntr; //Assign width-value
                        wcntr = 0; //Reset width counter
                        temprow = {};
                        c = ifs.get();
                    }                
                }
                if (!temprow.empty()){
                    mapmatrix.push_back(temprow);
                    hcntr++;
                    temprow = {};
                }
                height = hcntr;
                std::cout<<"Mapmatrix created."<<name<<std::endl;
            }
            
            if(!line.compare(std::string("CHECKPOINT:"))) {
                int value; std::string comment;
                ifs >> value >> comment;
                int num = value;
                ifs >> value >> comment;
                int x = value*tilesize.x;
                ifs >> value >> comment;
                int y = value*tilesize.y;
                ifs >> value >> comment;
                Vector2d pos = Vector2d(x,y);
                int width = value*tilesize.x;
                ifs >> value >> comment;
                int height = value*tilesize.y;
                checkpoints.push_back(std::make_shared<CheckPoint>(CheckPoint(pos, num, width, height)));
                std::cout << "CheckPoint " << num << " created!" << std::endl;
                }
            if(!line.compare(std::string("MINE:"))) {
                int value; std::string comment;
                ifs >> value >> comment;
                int x = value*tilesize.x;
                ifs >> value >> comment;
                int y = value*tilesize.y;
                ifs >> value >> comment;
                int radius = value;
                Vector2d pos = Vector2d(x,y);
                mines.push_back(std::make_shared<Mine>(Mine(pos,radius)));
                std::cout << "Mine created! x " << x << " y " << y << std::endl;
            }
            if(!line.compare(std::string("VEHICLE:"))) {
                auto vi = std::make_shared<VehicleInfo>();
                double value; std::string comment;
                ifs >> value >> comment;
                double x = value*tilesize.x;
                ifs >> value >> comment;
                double y = value*tilesize.y;
                vi->position1 = Vector2d(x,y);
                ifs >> value >> comment;
                x = value*tilesize.x;
                ifs >> value >> comment;
                y = value*tilesize.y;
                vi->position2 = Vector2d(x,y);
                ifs >> value >> comment;
                vi->orientation = value;
                ifs >> value >> comment;
                vi->maxSp = value;
                ifs >> value >> comment;
                vi->maxF = value;
                ifs >> value >> comment;
                vi->mass = value;
                world->addVehicleInfo(vi);
            }
        }
        ifs.close();
        
        //The following checks if the reading has been done correctly
        
        std::cout<<"Name of the map: "<<name<<std::endl;
        std::cout<<"Width: "<<width<<std::endl;
        std::cout<<"Heigth of the map: "<<height<<std::endl;
        std::cout<<"Tiletypes: "<<std::endl;
        
        for(std::string tile:tiletypes){
            std::cout<<tile<<std::endl;
        }
        
        std::cout<<"Mapmatrix: "<<std::endl;;
        
        for(auto i: mapmatrix){
            for(auto c : i){
                std::cout<<c;
            }
            std::cout<<std::endl;
        }
    }
    
void Map::draw(Window &w){
    w.draw(tilemap);
}

bool Map::loadTileMap(){
    std::cout << "Loading tilemap:" << std::endl;
    return tilemap.load(tilesetPath,tilesize,mapmatrix,width,height);
     
}

void Map::createWalls(std::shared_ptr<World> w){
    for (int j = 0;j<height;j++){
        for (int i = 0;i<width;i++){
            int tileType = mapmatrix[j][i];
            //Walls are marked with 0 in map-file. Create a wall
            if (tileType == 0) {
                Vector2d pos = Vector2d(i*tilesize.x,j*tilesize.y);
                std::shared_ptr<Wall> wall = std::make_shared<Wall>(Wall(pos,32,32));
                w->addWall(wall);
            }
        }
    }
}
