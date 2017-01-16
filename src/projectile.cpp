#include <iostream>
#include "projectile.hpp"
#include "vector2help.hpp"


Projectile::Projectile(Vector2d pos, Vector2d sp, double m, sf::Texture &tex,
                       std::shared_ptr<World> w) {
	position = pos;
	spawnPos = Vector2d(pos);
	speed = sp;
	mass = m;
	texture = tex;
	sprite.setTexture(tex);
	sprite.setPosition(pos.x, pos.y);
	sprite.setScale(1, 1);
    world = w;
}

void Projectile::updateState(double dt) {
    updatePosition(dt);
	updateSprite();
    for(auto w : world->getWalls()) {
        if(collides(*w)) {
            setHit();
        }
    }
}

void Projectile::updatePosition(double dt) {
	position += (dt*speed);
}

void Projectile::updateSprite() {
	sprite.setOrigin(texture.getSize().x/2, texture.getSize().y/2);
	sprite.setPosition(position.x, position.y);
	sprite.setRotation(angle);
}

void Projectile::collide(Object& o) {
    (void) o;
    setHit();
}

bool Projectile::maxDistanceSurpassed() {
    return length(spawnPos - getPosition()) > maxDistance;
}
