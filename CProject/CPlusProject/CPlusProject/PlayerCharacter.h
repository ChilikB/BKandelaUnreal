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

private:
	std::vector<Observer*> observers;
	Vector2 position;
	PlayerAttributes attributes;
	PlayerStats stats;
	std::unique_ptr<WeaponItem> equippedWeapon;
	std::vector<std::unique_ptr<Item>> inventory;
	std::vector<std::unique_ptr<Item>> equippedItems;

protected:
	Vector2 GetPosition() const { return position; }
	PlayerAttributes GetAttributes() const { return attributes; }
	PlayerStats GetStats() const { return stats; }
	void SetHealth(float health) { attributes.health = health; }
	void SetSpeed(int speed) { attributes.speed = speed; }
	void SetStrength(float strength) { stats.strength = strength; }
	void SetIntelligence(float intelligence) { stats.intelligence = intelligence; }
	void SetAgility(float agility) { stats.agility = agility; }
	void AddItemToInventory(std::unique_ptr<Item> item) { inventory.emplace_back(std::move(item)); }

private:
	void NotifyObservers();
};

