#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <map>
#include "objects.hpp"
#include <iostream>

/**
A class to follow player's progress in game. CheckPoint-object is located in the
game area to work as an indicator, whether player has passed a certain point. A
integer numbers are set for checkpoints to determint orde in which they have to 
be visited.
 */


class CheckPoint: public Object{
public:
    /**
    Constructor
    */
    CheckPoint(){}
    /**
    Constructor
    */
    CheckPoint(Vector2d pos, int num, int width, int angle);
    /**
    Returns the order number of checkpoint.
    */
    
    /**
    Detects if player has passed the checkpoint.
    */
    void collide(Object& o);
    /**
    Returns width of checkpoint.
    */
    int getWidth() const {return width;}
    /**
    Returns height of checkpoint.
    */
    int getHeight() const {return height;}
    /**
    Returns number of checkpoint.
    */
    int getNumber() const {return cpnum;}
    
private:
    int cpnum;
    int width;
    int height;
};

#endif
