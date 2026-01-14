// CPlusProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <stdexcept>
#include <cstdlib>
#include "Character.h"
#include "Utils.h"
#include <utility>
#include <map>
#include <vector>
#include "Vector2.h"
#include "CharacterA.h"
#include "Meteor.h"

Character* character = nullptr;

/// <summary>
/// Прототип, функція нижче, не дуже зручно у плюсах, 
/// але через читання файлу він не бачить функцію реалізовану нижче
/// </summary>
/// <returns></returns>
int menu();
int menu2();
int menu3(Character* players, int count);
int menu4();
int menu5();
int menu6();

Character createCharacter();

void main()
{
    //while (menu());
    //while (menu2());
	//while (menu4());
	//while (menu5());
    while (menu6());
}

void homework2() {
    int playersCount = 0;
    std::cout << "Players count:" << std::endl;
    std::cin >> playersCount;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for players count. Please enter a valid number.");
    }
    Character* players = new Character[playersCount];
    for(int i = 0; i < playersCount; i++) {
        players[i] = createCharacter();
        system("cls");
    }
    float damage = 0;
	std::cout << "Enter damage to apply to all characters: ";
	std::cin >> damage;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for damage value. Please enter a valid number.");
    }
    for (int i = 0; i < playersCount; ++i) {
        players[i].takeDamage(damage);
    }

	while (menu3(players, playersCount));

    delete[] players;
    players = nullptr;
}

void homework3Task1() {
    int counter = 0;
    std::cout << "Counter:" << std::endl;
    std::cin >> counter;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for counter. Please enter a valid number.");
    }
    std::map<int, int> units;
    int type = 0;
    int value = 0;
    for (int i = 0; i < counter; i++) {
		std::cout << "Unit type (int):" << std::endl;
		std::cin >> type;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for unit type. Please enter a valid number.");
        }
        std::cout << "Units count (int):" << std::endl;
        std::cin >> value;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for unit count. Please enter a valid number.");
        }

        if(units.find(type) != units.end()) {
            units[type] += value;
        } else {
            units[type] = value;
        }
        system("cls");
    }

    if (units.empty()) {
        std::cout << "No units entered." << std::endl;
        return;
    }
    
    auto value_comparer = [](const auto& p1, const auto& p2) {
        return p1.second < p2.second;
    };

    Utils::SetConsoleColor(11, 0);
    
    auto minValue = std::min_element(units.begin(), units.end(), value_comparer);
    std::cout << "Min (unit type): " << minValue->first << ", (unit count): " << minValue->second << std::endl;

    auto maxValue = std::max_element(units.begin(), units.end(), value_comparer);
    std::cout << "Max (unit type): " << maxValue->first << ", (unit count): " << maxValue->second << std::endl;

    Utils::ResetConsoleColor();
}
void homework3Task2() {
    int counter = 0;
    std::cout << "Steps counter:" << std::endl;
    std::cin >> counter;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for counter. Please enter a valid number.");
    }

    std::vector<std::string> path;
    std::string direction;
	//awailable directions
	std::vector<std::string> directions = { "left", "right", "top", "down" };

    system("cls");

    for (int i = 0; i < counter; i++) {
        std::cout << "Current path: ";
        for(int j = 0; j < path.size(); j++) {
			std::cout << path[j] + " ";
		}
        std::cout << std::endl;
        std::cout << "Enter direction (left,right,top,down):" << std::endl;
        std::cin >> direction;
        if (std::find(directions.begin(), directions.end(), direction) != directions.end()) {
			path.push_back(direction);
        }
        else {
            i--;
        }
        system("cls");
    }

    int x = 0;
	int y = 0;

    std::cout << "Player coordinate X:" << std::endl;
    std::cin >> x;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for coordinate X. Please enter a valid number.");
    }
    std::cout << "Player coordinate Y:" << std::endl;
    std::cin >> y;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for coordinate Y. Please enter a valid number.");
    }

    std::pair<int, int> coords(x, y);

    for (const auto& dir : path) {
        if (dir == "left") {
            coords.first--;
        } else if (dir == "right") {
            coords.first++;
        } else if (dir == "top") {
            coords.second++;
        } else if (dir == "down") {
            coords.second--;
        }
    }
    
    system("cls");

    Utils::SetConsoleColor(11, 0);

    std::cout << "Final coordinates: (" << coords.first << ", " << coords.second << ")" << std::endl;

    Utils::ResetConsoleColor();
}

void homework4Task1() {

    int counter = 0;
    std::cout << "Counter:" << std::endl;
    std::cin >> counter;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for counter. Please enter a valid number.");
    }

	std::vector<CharacterA> units;

    std::string name = "default";
    int health = 0;
    Vector2 position = {0, 0};

    for (int i = 0; i < counter; i++) {
        std::cout << "Name:" << std::endl;
        std::cin >> name;
        std::cout << "Health:" << std::endl;
        std::cin >> health;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for health. Please enter a valid number.");
        }
        std::cout << "Position X:" << std::endl;
        std::cin >> position.x;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for position X. Please enter a valid number.");
		}
		std::cout << "Position Y:" << std::endl;
		std::cin >> position.y;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for position Y. Please enter a valid number.");
		}
		units.push_back(CharacterA(name, health, position));
        system("cls");
    }

    Meteor meteor;

    std::cout << "Meteor strength:" << std::endl;
    std::cin >> meteor.strength;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for strength. Please enter a valid number.");
    }

    std::cout << "Meteor damage:" << std::endl;
    std::cin >> meteor.damage;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for damage. Please enter a valid number.");
    }

    std::cout << "Meteor X position:" << std::endl;
    std::cin >> meteor.position.x;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for meteor position X. Please enter a valid number.");
    }

    std::cout << "Meteor Y position:" << std::endl;
    std::cin >> meteor.position.y;
    if (std::cin.fail()) {
        throw std::invalid_argument("Invalid input for meteor position Y. Please enter a valid number.");
    }

    system("cls");

    if (units.empty()) {
        std::cout << "No units entered." << std::endl;
        return;
    }

    for (auto& unit : units) {
        if (meteor.isHit(unit)) {
            Utils::SetConsoleColor(11, 0);
            std::cout << "--------" << std::endl;
            std::cout << "Meteor hit character: " + unit.name << std::endl;
            std::cout << "Applying damage: " << meteor.damage << std::endl;
            unit.takeDamage(meteor.damage);
            if (unit.isDead()) {
                std::cout << "Character " + unit.name + " is dead." << std::endl;
            }
            else
            {
                std::cout << "Character " + unit.name + " survived." << std::endl;
                std::cout << "Health left: " << unit.health << std::endl;

            }
            std::cout << "--------" << std::endl;
        }
        else {
			Utils::SetConsoleColor(4, 0);
            std::cout << "--------" << std::endl;
            std::cout << "Meteor missed character: " + unit.name << std::endl;
            std::cout << "--------" << std::endl;
        }
        Utils::ResetConsoleColor();
    }
}

int menu() {
    std::cout << (character == nullptr ? "1. Create new Character" : "1. Recreate Character") << std::endl;
    std::cout << "2. Display Character Info" << std::endl;
    std::cout << "3. Exit" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
    {
        try {
            delete character;
			character = nullptr;
            character = new Character(createCharacter());

            system("cls");
            Utils::SetConsoleColor(2, 0);
            std::cout << "Character created." << std::endl;
            Utils::ResetConsoleColor();
        }
        catch (std::invalid_argument& e) {
            system("cls");
            Utils::SetConsoleColor(4, 0);
            std::cout << e.what() << std::endl;
            Utils::ResetConsoleColor();
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    break;
    case 2:
    {
        if (character == nullptr) {
			system("cls");
			Utils::SetConsoleColor(4, 0);
            std::cout << "No character created yet." << std::endl;
			Utils::ResetConsoleColor();
            break;
        }
        system("cls");
		Utils::SetConsoleColor(3, 0);
		character->displayInfo();
		Utils::ResetConsoleColor();
    }
    break;
    case 3:
        delete character;
        character = nullptr;
		return 0;
    default:
        system("cls");
		Utils::SetConsoleColor(4, 0);
        std::cout << "Invalid choice. Please select again." << std::endl;
		Utils::ResetConsoleColor();
        break;
    }

    return 1;
}

int menu2() {
    std::cout << "1. Start" << std::endl;
    std::cout << "2. Exit" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
    {
        try {
            system("cls");
            homework2();
        }
        catch (std::invalid_argument& e) {
            system("cls");
            Utils::SetConsoleColor(4, 0);
            std::cout << e.what() << std::endl;
            Utils::ResetConsoleColor();
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    break;
    case 2:
        delete character;
        character = nullptr;
        return 0;
    default:
        system("cls");
        Utils::SetConsoleColor(4, 0);
        std::cout << "Invalid choice. Please select again." << std::endl;
        Utils::ResetConsoleColor();
        break;
    }

    return 1;
}

int menu3(Character* players, int count) {
    std::cout << "1. Show max health player" << std::endl;
    std::cout << "2. Show min health player" << std::endl;
    std::cout << "3. Show death player" << std::endl;
    std::cout << "4. Exit" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
    {
        Character selected = players[0];
        float maxHp = players[0].health;

        system("cls");
        for (int i = 1; i < count; i++) {
            if (selected.isDead()) {
                selected = players[i];
                maxHp = players[i].health;
            }
            else if (players[i].health > maxHp) {
                selected = players[i];
                maxHp = players[i].health;
            }
        }
        if (selected.isDead()) {
            std::cout << "All players dead" << std::endl;
        }
        else {
            selected.displayInfo();
            std::cout << "--------" << std::endl;
        }
    }
    break;
    case 2:
    {
        Character selected = players[0];
        float minHp = players[0].health;

        system("cls");
        for (int i = 1; i < count; i++) {

            if (selected.isDead()) {
                selected = players[i];
                minHp = players[i].health;
            }
            else if (!players[i].isDead() && players[i].health < minHp) {
                selected = players[i];
                minHp = players[i].health;
            }
        }
        if (selected.isDead()) {
            std::cout << "All players dead" << std::endl;
        }
        else {
            selected.displayInfo();
            std::cout << "--------" << std::endl;
        }
    }
    break;
    case 3:
    {
        system("cls");
        int deadCounter = 0;
        for (int i = 0; i < count; i++) {
            if (players[i].isDead()) {
                deadCounter++;
                players[i].displayInfo();
                std::cout << "--------" << std::endl;
            }
        }
        if (deadCounter == 0) {
            std::cout << "There is no dead players" << std::endl;
        }
    }
    break;
    case 4:
        delete character;
        character = nullptr;
        return 0;
    default:
        system("cls");
        Utils::SetConsoleColor(4, 0);
        std::cout << "Invalid choice. Please select again." << std::endl;
        Utils::ResetConsoleColor();
        break;
    }

    return 1;
}

int menu4() {
    std::cout << "1. Task 1" << std::endl;
	std::cout << "2. Task 2" << std::endl;
    std::cout << "3. Exit" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
    {
        try {
            system("cls");
            homework3Task1();
        }
        catch (std::invalid_argument& e) {
            system("cls");
            Utils::SetConsoleColor(4, 0);
            std::cout << e.what() << std::endl;
            Utils::ResetConsoleColor();
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    break;
    case 2:
    {
        try {
            system("cls");
            homework3Task2();
        }
        catch (std::invalid_argument& e) {
            system("cls");
            Utils::SetConsoleColor(4, 0);
            std::cout << e.what() << std::endl;
            Utils::ResetConsoleColor();
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    break;
    case 3:
        delete character;
        character = nullptr;
        return 0;
    default:
        system("cls");
        Utils::SetConsoleColor(4, 0);
        std::cout << "Invalid choice. Please select again." << std::endl;
        Utils::ResetConsoleColor();
        break;
    }

    return 1;
}

int menu6() {
    std::cout << "1. Show inventory" << std::endl;
    std::cout << "5. Exit" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
    {
        try {
            system("cls");
            homework4Task1();
        }
        catch (std::invalid_argument& e) {
            system("cls");
            Utils::SetConsoleColor(4, 0);
            std::cout << e.what() << std::endl;
            Utils::ResetConsoleColor();
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    break;
    case 5:
        delete character;
        character = nullptr;
        return 0;
    default:
        system("cls");
        Utils::SetConsoleColor(4, 0);
        std::cout << "Invalid choice. Please select again." << std::endl;
        Utils::ResetConsoleColor();
        break;
    }

    return 1;
}

int menu5() {
    std::cout << "1. Task 1" << std::endl;
    std::cout << "2. Exit" << std::endl;

    int choice;
    std::cin >> choice;

    switch (choice) {
    case 1:
    {
        try {
            system("cls");
            homework4Task1();
        }
        catch (std::invalid_argument& e) {
            system("cls");
            Utils::SetConsoleColor(4, 0);
            std::cout << e.what() << std::endl;
            Utils::ResetConsoleColor();
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        }
    }
    break;
    case 2:
        delete character;
        character = nullptr;
        return 0;
    default:
        system("cls");
        Utils::SetConsoleColor(4, 0);
        std::cout << "Invalid choice. Please select again." << std::endl;
        Utils::ResetConsoleColor();
        break;
    }

    return 1;
}

Character createCharacter() {
    std::string name;
    int classChoice;
    float health;
    system("cls");
    std::cout << "Enter character name: ";
    std::cin >> name;
    std::cout << "Enter character health: ";
	std::cin >> health;
    if (std::cin.fail()) {
		throw std::invalid_argument("Invalid input for health. Please enter a valid number.");
    }
    std::cout << "Select character class (Warrior by default): " << std::endl;
    std::cout << "1. Warrior" << std::endl;
    std::cout << "2. Mage" << std::endl;
    std::cout << "3. Archer" << std::endl;
    std::cout << "4. Thief" << std::endl;
    std::cin >> classChoice;
    
    CharacterClass characterClass;
    switch (classChoice) {
    case 1:
        characterClass = CharacterClass::Warrior;
        break;
    case 2:
        characterClass = CharacterClass::Mage;
        break;
    case 3:
        characterClass = CharacterClass::Archer;
        break;
    case 4:
        characterClass = CharacterClass::Thief;
        break;
    default:
		throw std::invalid_argument("Invalid class choice");
        break;
    }
    
    return Character(name, characterClass, health);
}
    
