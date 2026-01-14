#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter()
{
	attributes.health = 100.0f;
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
}

PlayerCharacter::~PlayerCharacter() = default;

void PlayerCharacter::equipWeapon(std::unique_ptr<WeaponItem> weapon)
{
	equippedWeapon = std::move(weapon);
}

void PlayerCharacter::unequipWeapon()
{
	equippedWeapon.reset();
}

void PlayerCharacter::equip(std::unique_ptr<Item> item) {
	equippedItems.emplace_back(std::move(item));
}

void PlayerCharacter::unequip(int id) {
}

void PlayerCharacter::move(int x, int y)
{
	position.x += x;
	position.y += y;
}

void PlayerCharacter::showCharacterInfo()
{

}

