#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	attributes.health = 120.0f;
	attributes.speed = 1;
	stats.strength = 10.0f;
	stats.intelligence = 10.0f;
	stats.agility = 10.0f;

	inventory.emplace_back(
		std::make_unique<PlayerStatsModifierItem>(
			1, "Strength modifier", "strenght_mod.png", PlayerStats{2, 0, 0}
		)
	);

	inventory.emplace_back(
		std::make_unique<WeaponItem>(
			2, "Sword", "sword.png", WeaponStats{ 10, 5 }
		)
	);

	inventory.emplace_back(
		std::make_unique<WeaponModifierItem>(
			3, "Sword modifier", "sword_mod.png", WeaponStats{ 5, 5 }
		)
	);

	inventory.emplace_back(
		std::make_unique<PlayerAttributeModifierItem>(
			4, "Boots Abibas", "boots.png", PlayerAttributes{ 0, 1 }
		)
	);

	inventory.emplace_back(
		std::make_unique<PlayerAttributeModifierItem>(
			5, "Health Amulet", "amulet.png", PlayerAttributes{ 20, 0 }
		)
	);
}

PlayerCharacter::~PlayerCharacter() = default;

bool PlayerCharacter::equip(int id)
{
	for (auto it = inventory.begin(); it != inventory.end(); ++it)
	{
		if (!(*it)) continue;

		if ((*it)->id != id)
			continue;

		if (auto* weaponPtr = dynamic_cast<WeaponItem*>(it->get()))
		{
			if (equippedWeapon)
				inventory.emplace_back(std::move(equippedWeapon));

			equippedWeapon.reset(static_cast<WeaponItem*>((*it).release()));

			inventory.erase(it);
			return true;
		}

		equippedItems.emplace_back(std::move(*it));
		inventory.erase(it);
		return true;
	}

	return false;
}

bool PlayerCharacter::unequip(int id) {
	if (equippedWeapon && equippedWeapon->id == id)
	{
		inventory.emplace_back(std::move(equippedWeapon));
		return true;
	}

	for (auto it = equippedItems.begin(); it != equippedItems.end(); ++it)
	{
		if (!(*it)) continue;

		if ((*it)->id == id)
		{
			inventory.emplace_back(std::move(*it));
			equippedItems.erase(it);
			return true;
		}
	}

	return false;
}

void PlayerCharacter::move(int x, int y)
{
	auto speed = attributes.speed;
	for (auto& item : equippedItems) {
		if (auto attributesModItem = dynamic_cast<PlayerAttributeModifierItem*>(item.get()))
		{
			speed += attributesModItem->attributesModifier.speed;
		}
	}
	position.x += x * speed;
	position.y += y * speed;

	NotifyObservers();
}

void PlayerCharacter::showCharacterInfo()
{
	auto strength = stats.strength;
	auto intelligence = stats.intelligence;
	auto agility = stats.agility;
	auto speed = attributes.speed;
	auto health = attributes.health;
	auto damage = equippedWeapon ? equippedWeapon->stats.damage : 0.0f;
	auto cooldown = equippedWeapon ? equippedWeapon->stats.cooldown : 0.0f;
	for (auto& item : equippedItems) {
		if (auto statModItem = dynamic_cast<PlayerStatsModifierItem*>(item.get())) {
			strength += statModItem->statsModifier.strength;
			intelligence += statModItem->statsModifier.intelligence;
			agility += statModItem->statsModifier.agility;
		}
		else if (auto weaponModItem = dynamic_cast<WeaponModifierItem*>(item.get())) {
			if (equippedWeapon) {
				damage += weaponModItem->statsModifier.damage;
				cooldown += weaponModItem->statsModifier.cooldown;
			}
		}
		else if (auto attributesModItem = dynamic_cast<PlayerAttributeModifierItem*>(item.get()))
		{
			health += attributesModItem->attributesModifier.health;
			speed += attributesModItem->attributesModifier.speed;
		}
	}
	printf("Player Character Info:\n");
	printf("Position: (%d, %d)\n", position.x, position.y);
	printf("Health: %.2f\n", health);
	printf("Speed: %d\n", speed);
	printf("Stats - Strength: %.2f, Intelligence: %.2f, Agility: %.2f\n", strength, intelligence, agility);
	
	if (equippedWeapon) {
		printf("Equipped Weapon: %s (Damage: %.2f, Cooldown: %.2f)\n",
			equippedWeapon->name.c_str(),
			damage,
			cooldown);
	} else {
		printf("No weapon equipped.\n");
	}
	printf("Equipped Items:\n");
	for (const auto& item : equippedItems) {
		printf("- (ID: %d) %s\n", item->id, item->name.c_str());
	}
}

void PlayerCharacter::showInventory()
{
	printf("Inventory:\n");
	for (const auto& item : inventory) {
		printf("- %s (ID: %d)\n", item->name.c_str(), item->id);
	}
}

void PlayerCharacter::addObserver(Observer* observer)
{
	observers.push_back(observer);
}

void PlayerCharacter::NotifyObservers()
{
	for (auto& observer : observers)
	{
		observer->PositionChanged(position);
	}
}