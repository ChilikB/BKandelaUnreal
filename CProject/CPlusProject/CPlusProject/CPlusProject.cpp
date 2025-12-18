// CPlusProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <limits>
#include <stdexcept>
#include <cstdlib>
#include "Character.h"
#include "Utils.h"

Character* character = nullptr;

/// <summary>
/// Прототип, функція нижче, не дуже зручно у плюсах, 
/// але через читання файлу він не бачить функцію реалізовану нижче
/// </summary>
/// <returns></returns>
int menu();
int menu2();
int menu3(Character* players, int count);

Character createCharacter();

void main()
{
    //while (menu());
    while (menu2());
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
    
