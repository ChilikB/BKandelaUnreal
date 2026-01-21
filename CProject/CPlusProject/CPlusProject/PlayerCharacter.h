#pragma once
#include <memory>
#include <vector>

#include "Item.h"
#include "Vector2.h"
#include "PlayerAttributes.h"
#include "PlayerStats.h"
#include "PlayerCharacterObserver.h"

class Item;
class WeaponItem;

class PlayerCharacter
{

public:
	PlayerCharacter();
	~PlayerCharacter();
	void addObserver(Observer* observer);
	bool equip(int id);
	bool unequip(int id);
	void move(int x, int y);
	void showCharacterInfo();
	void showInventory();

public:
	std::vector<Observer*> observers;
	Vector2 position;
	PlayerAttributes attributes;
	PlayerStats stats;
	std::unique_ptr<WeaponItem> equippedWeapon;
	std::vector<std::unique_ptr<Item>> inventory;
	std::vector<std::unique_ptr<Item>> equippedItems;

private:
	void NotifyObservers();
};

