#pragma once
#include "WeaponStats.h"
#include "PlayerStats.h"
#include <string>

class Item
{
	public:
		int id{};
		std::string name;
		std::string srcImage;

		Item() = default;

		Item(int id, std::string name, std::string srcImage)
			: id(id), name(std::move(name)), srcImage(std::move(srcImage)) {
		}

	virtual ~Item() = default;
};

class WeaponModifierItem : public Item {
	public:
		WeaponStats statsModifier;
		
	public:
		WeaponModifierItem(int id, std::string name, std::string srcImage, const WeaponStats& stats) : Item(id, name, srcImage), statsModifier(stats)
		{
		}
};

class PlayerStatsModifierItem : public Item {
	public:
		PlayerStats statsModifier;
		
	public:
		PlayerStatsModifierItem(int id, std::string name, std::string srcImage, const PlayerStats& stats) : Item(id, name, srcImage), statsModifier(stats)
		{
		}
};

class WeaponItem : public Item
{
	public:
		WeaponStats stats;
		
	public:
		WeaponItem(int id, std::string name, std::string srcImage, const WeaponStats& stats) : Item(id, name, srcImage), stats(stats)
		{
		}
};