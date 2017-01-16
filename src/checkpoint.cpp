#include "checkpoint.hpp"

void CheckPoint::collide(Object& o) { (void) o;}

CheckPoint::CheckPoint(Vector2d pos, int num, int w, int h) {
    position = pos; //The location of the checkpoint
    cpnum = num; //The order number of the checkpoint
    width = w;
    height = h;
    std::cout << "Checkpoint: x " << position.x << " y " << position.y << std::endl;
}


