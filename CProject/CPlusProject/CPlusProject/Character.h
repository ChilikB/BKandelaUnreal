#pragma once
#include <string>
#include "CharacterClass.h"
#include <iostream>

class Character
{

public:
	float health;
	std::string name;
private:
	CharacterClass characterClass;

public:
	Character() {
		this->name = "Default";
		this->characterClass = CharacterClass::Warrior;
		this->health = 100.0f;
	}

public:
	Character(std::string name, CharacterClass characterClass, float health) {
		this->name = name;
		this->characterClass = characterClass;
		this->health = health;
	}

	void takeDamage(float damage) {
		health -= damage;
		if (health < 0) {
			health = 0;
		}
	}

	bool isDead() {
		return health <= 0;
	}

	void displayInfo() {
		std::string className;
		switch (characterClass) {
		case CharacterClass::Warrior:
			className = "Warrior";
			break;
		case CharacterClass::Mage:
			className = "Mage";
			break;
		case CharacterClass::Archer:
			className = "Archer";
			break;
		case CharacterClass::Thief:
			className = "Thief";
			break;
		default:
			className = "Unknown";
			break;
		}
		std::cout << "Character Name: " << name << std::endl;
		std::cout << "Character Class: " << className << std::endl;
		std::cout << "Character Health: " << health << std::endl;
	}
};

