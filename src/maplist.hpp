#ifndef MM2_MAPLIST_HPP
#define MM2_MAPLIST_HPP

#include <fstream>
#include <string>
#include "map.hpp"

typedef std::vector<std::string> Maplist;

Maplist createMaplist(std::string const& f);
std::string getMapPath(Maplist& mlist, int map_id);
std::string getTileMapPath(Maplist& mlist, int map_id);
#endif
