#pragma once
#include <string>
#include "CharacterClass.h"
#include <iostream>

class Character
{

private:
	std::string name;
	float health;
	CharacterClass characterClass;

public:
	Character(std::string name, CharacterClass characterClass, float health) {
		this->name = name;
		this->characterClass = characterClass;
		this->health = health;
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

