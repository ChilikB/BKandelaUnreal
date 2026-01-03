#pragma once
#include "Character.h"
#include "Vector2.h"

class CharacterA :
    public Character
{
public:
	Vector2 position;

    public:
		CharacterA(std::string name, float health, Vector2 position) : Character(name, CharacterClass::Archer, health)
        {
			this->position = position;
        }
};

