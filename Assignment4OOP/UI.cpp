//
// Created by Cezar on 26.03.2025.
//

#include "UI.h"
#include <iostream>
#include <stdexcept>
#include <cstdlib>

UI::UI(Service& serv) : service(serv) {}

void UI::run() {
    while (true) {
        std::cout << "1. Administrator Mode\n";
        std::cout << "2. User Mode\n";
        std::cout << "0. Exit\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1: adminMenu(); break;
            case 2: userMenu(); break;
            case 0: return;
            default: std::cout << "Invalid option!\n";
        }
    }
}

void UI::adminMenu() {
    while (true) {
        std::cout << "1. Add Tutorial\n";
        std::cout << "2. Remove Tutorial\n";
        std::cout << "3. Update Tutorial\n";
        std::cout << "4. List All Tutorials\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: {
                    Tutorial newTutorial = readTutorialInput();
                    service.addTutorial(
                        newTutorial.getTitle(),
                        newTutorial.getPresenter(),
                        newTutorial.getMinutes(),
                        newTutorial.getSeconds(),
                        newTutorial.getLikes(),
                        newTutorial.getLink()
                    );
                    std::cout << "Tutorial added successfully!\n";
                    break;
                }
                case 2: {
                    std::string title, presenter;
                    std::cout << "Enter tutorial title: ";
                    std::cin.ignore();
                    std::getline(std::cin, title);
                    std::cout << "Enter presenter name: ";
                    std::getline(std::cin, presenter);
                    service.removeTutorial(title, presenter);
                    std::cout << "Tutorial removed successfully!\n";
                    break;
                }
                case 3: {
                    std::string oldTitle, oldPresenter;
                    std::cout << "Enter existing tutorial title: ";
                    std::cin.ignore();
                    std::getline(std::cin, oldTitle);
                    std::cout << "Enter existing presenter name: ";
                    std::getline(std::cin, oldPresenter);

                    Tutorial newTutorial = readTutorialInput();
                    service.updateTutorial(
                        oldTitle, oldPresenter,
                        newTutorial.getTitle(),
                        newTutorial.getPresenter(),
                        newTutorial.getMinutes(),
                        newTutorial.getSeconds(),
                        newTutorial.getLikes(),
                        newTutorial.getLink()
                    );
                    std::cout << "Tutorial updated successfully!\n";
                    break;
                }
                case 4: printAllTutorials(); break;
                case 0: return;
                default: std::cout << "Invalid option!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}
Tutorial UI::readTutorialInput() {
    std::string title, presenter, link;
    int minutes, seconds, likes;

    std::cin.ignore();
    std::cout << "Enter tutorial title: ";
    std::getline(std::cin, title);

    std::cout << "Enter presenter name: ";
    std::getline(std::cin, presenter);

    std::cout << "Enter duration (minutes): ";
    std::cin >> minutes;

    std::cout << "Enter duration (seconds): ";
    std::cin >> seconds;

    std::cout << "Enter number of likes: ";
    std::cin >> likes;

    std::cin.ignore();
    std::cout << "Enter tutorial link: ";
    std::getline(std::cin, link);

    return Tutorial(title, presenter, minutes, seconds, likes, link);
}

void UI::printAllTutorials() {
    DynamicArray<Tutorial> tutorials = service.getAllTutorials();

    if (tutorials.getSize() == 0) {
        std::cout << "No tutorials available.\n";
        return;
    }

    std::cout << "\n--- All Tutorials ---\n";
    for (int i = 0; i < tutorials.getSize(); ++i) {
        std::cout << tutorials[i].toString() << std::endl;
    }
}

void UI::userMenu() {
    while (true) {
        std::cout << "\n----- User Menu -----\n";
        std::cout << "1. Browse tutorials\n";
        std::cout << "2. View watch list\n";
        std::cout << "0. Back to Main Menu\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        try {
            switch (choice) {
                case 1: browseMode(); break;
                case 2: showWatchList(); break;
                case 0: return;
                default: std::cout << "Invalid option!\n";
            }
        }
        catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        }
    }
}

void UI::browseMode() {
    std::cin.ignore();
    std::string presenter;
    std::cout << "Enter presenter name (or leave empty for all tutorials): ";
    std::getline(std::cin, presenter);

    DynamicArray<Tutorial> filteredTutorials = service.filterTutorialsByPresenter(presenter);

    if (filteredTutorials.getSize() == 0) {
        std::cout << "No tutorials found for this presenter.\n";
        return;
    }

    int currentIndex = 0;
    bool browsing = true;

    while (browsing) {
        Tutorial currentTutorial = filteredTutorials[currentIndex];

        std::cout << "\n----- Tutorial -----\n";
        std::cout << currentTutorial.toString() << "\n";

        // Play the tutorial in browser
        playTutorial(currentTutorial);

        std::cout << "\n1. Add to watch list\n";
        std::cout << "2. Next tutorial\n";
        std::cout << "0. Exit browsing\n";
        std::cout << "Choose an option: ";

        int choice;
        std::cin >> choice;

        switch (choice) {
            case 1:
                try {
                    service.addToWatchList(currentTutorial);
                    std::cout << "Tutorial added to watch list!\n";
                }
                catch (const std::exception& e) {
                    std::cout << "Error: " << e.what() << "\n";
                }
                // Move to next tutorial after adding
                currentIndex = (currentIndex + 1) % filteredTutorials.getSize();
                break;
            case 2:
                // Move to next tutorial
                currentIndex = (currentIndex + 1) % filteredTutorials.getSize();
                break;
            case 0:
                browsing = false;
                break;
            default:
                std::cout << "Invalid option!\n";
        }
    }
}

void UI::showWatchList() {
    DynamicArray<Tutorial> watchList = service.getWatchList();

    if (watchList.getSize() == 0) {
        std::cout << "Watch list is empty.\n";
        return;
    }

    std::cout << "\n----- Watch List -----\n";
    for (int i = 0; i < watchList.getSize(); ++i) {
        std::cout << i + 1 << ". " << watchList[i].toString() << "\n";
    }

    std::cout << "\n1. Remove a tutorial (after watching)\n";
    std::cout << "0. Back\n";
    std::cout << "Choose an option: ";

    int choice;
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Enter the number of the tutorial to remove: ";
        int index;
        std::cin >> index;

        if (index < 1 || index > watchList.getSize()) {
            std::cout << "Invalid tutorial number!\n";
            return;
        }

        Tutorial tutorialToRemove = watchList[index - 1];

        // Play the tutorial before removing
        playTutorial(tutorialToRemove);

        std::cout << "Did you like this tutorial? (1 - Yes, 0 - No): ";
        int liked;
        std::cin >> liked;

        bool like = (liked == 1);
        service.removeFromWatchList(tutorialToRemove.getTitle(), tutorialToRemove.getPresenter(), like);

        std::cout << "Tutorial removed from watch list";
        if (like) {
            std::cout << " and liked!";
        }
        std::cout << std::endl;
    }
}

void UI::playTutorial(const Tutorial& tutorial) {
    std::cout << "Playing tutorial: " << tutorial.getTitle() << "\n";
    std::cout << "Link: " << tutorial.getLink() << "\n";

    // Platform-specific code to open a URL in browser
    std::string link = tutorial.getLink();

    #ifdef _WIN32
        std::string command = "start " + link;
    #elif __APPLE__
        std::string command = "open " + link;
    #else
        std::string command = "xdg-open " + link;
    #endif

    // Uncomment the line below to actually open the browser
    // system(command.c_str());

    std::cout << "(Browser would open with the tutorial link)\n";
}
