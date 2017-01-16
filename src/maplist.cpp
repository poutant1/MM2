
#include "maplist.hpp"


Maplist createMaplist(std::string const& fpath){
    
    //open file
    Maplist l;
    std::ifstream mfile;
    mfile.open(fpath);
    if (!mfile.is_open())
        throw "Error: maplist file not found";
    std::string mapname;
    //load rows
    while (mfile.good()){
        std::getline(mfile,mapname);
        if (!mapname.empty())
            l.push_back(mapname);
    }
    //close file
    mfile.close();
    //return maplist
    return l;
}


std::string getMapPath(Maplist& mlist, int map_id){
    std::string retval;
    retval = "./resources/maps/" + mlist[map_id]+"/" + mlist[map_id] + ".txt";
    return retval;
    
}

std::string getTileMapPath(Maplist& mlist, int map_id){
    std::string retval;
    retval = "./resources/maps/" + mlist[map_id]+ + "/tileset.png";
    return retval;
    
}
