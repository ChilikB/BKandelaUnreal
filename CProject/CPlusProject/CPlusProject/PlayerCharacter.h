#pragma once
#include <memory>
#include <vector>

#include "Item.h"
#include "Vector2.h"
#include "PlayerAttributes.h"
#include "PlayerStats.h"

class Item;
class WeaponItem;

class PlayerCharacter
{

public:
	PlayerCharacter();
	~PlayerCharacter();
	void equipWeapon(std::unique_ptr<WeaponItem> weapon);
	void equip(std::unique_ptr<Item> item);
	void unequipWeapon();
	void unequip(int id);
	void move(int x, int y);
	void showCharacterInfo();

public:
	Vector2 position;
	PlayerAttributes attributes;
	PlayerStats stats;
	std::unique_ptr<WeaponItem> equippedWeapon;
	std::vector<std::unique_ptr<Item>> inventory;
	std::vector<std::unique_ptr<Item>> equippedItems;
	
};

