#include <string>
#include <iostream>
#include "Repository.h"
#include "Service.h"
#include "UI.h"
#include "Test.h"

int main(int argc, char* argv[]) {
    // Run tests
    Test::runAllTests();
        if (argc > 1 && std::string(argv[1]) == "--test") return 0;
    Repository repository;
    Service service(repository);

    service.addTutorial("C++ Fundamentals", "John", 45, 30, 250, "https://www.learncpp.com/");
    service.addTutorial("Advanced C++", "Emily", 60, 15, 180, "https://www.learncpp.com/");
    service.addTutorial("Python", "Mike", 40, 0, 220, "https://www.w3schools.com/python/");
    service.addTutorial("Data Structures in Python", "Sarah", 55, 45, 190, "https://www.w3schools.com/python/");
    service.addTutorial("JavaScript Essentials", "David", 50, 20, 210, "https://www.w3schools.com/js/");
    service.addTutorial("Java Script", "Anna", 70, 10, 240, "https://www.w3schools.com/js/");
    service.addTutorial("Machine Learning", "Tom", 80, 0, 200, "https://www.w3schools.com/python/python_ml_getting_started.asp");
    service.addTutorial("Deep Learning", "Lisa", 90, 30, 175, "https://www.w3schools.com/python/python_ml_getting_started.asp");
    service.addTutorial("Web Development", "Chris", 60, 0, 230, "https://www.w3schools.com/whatis/");
    service.addTutorial("Web Security", "Rachel", 65, 45, 160, "http://tutorials.com/web2");

    UI ui(service);
    ui.run();

    return 0;
}