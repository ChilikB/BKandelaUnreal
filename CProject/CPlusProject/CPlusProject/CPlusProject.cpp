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
Character createCharacter();

int main()
{
    int result = 1;
    do {
		result = menu();
	} while (result != 0);
    return 0;
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
    
