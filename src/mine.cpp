#include <iostream>
#include "mine.hpp"

Mine::Mine(Vector2d pos, int rad) {
    position = pos;
    radius = rad;
    sprite.setPosition(pos.x,pos.y);
}

void Mine::setTexture(sf::Texture& tex) {
    sprite.setTexture(tex);
}

bool Mine::isVisible() {
    return visible;
}

void Mine::detonate() {
    visible = false;
    clock.restart();
}

void Mine::draw(Window& w) {
    if (visible) {
        w.draw(getSprite());
    }
}

void Mine::updateState() {
    if (clock.getElapsedTime() > timeInactive) {
        visible = true;
    }
}

void Mine::collide(Object& o) {
    (void) o;
}