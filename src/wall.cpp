#include "wall.hpp"

void Wall::collide(Object& o) {(void) o;}

const double& Wall::getWidth() const {return width;}
const double& Wall::getHeight() const {return height;}
