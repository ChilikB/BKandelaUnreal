#pragma once

#include "Vector2.h"
#include "CharacterA.h"

struct Meteor {
	Vector2 position;
    int strength;
    int damage;
    Meteor(Vector2 initPosition, int initStrength, int initDamage) : position(initPosition), strength(initStrength), damage(initDamage) 
    {}
    Meteor() : position(0,0), strength(0), damage(0) {}

public:
    bool isHit(const CharacterA& c) {
		int radius = 3 * strength;
        long dx = (long)c.position.x - position.x;
        long dy = (long)c.position.y - position.y;
        long r2 = (long)radius * radius;
        return dx * dx + dy * dy <= r2;
    }
};