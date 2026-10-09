//
// Created by Cezar on 26.03.2025.
//

#include "Test.h"
#include "Tutorial.h"
#include "DynamicArray.h"
#include "Repository.h"
#include "Service.h"
#include "Watchlist.h"
#include "UI.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <sstream>

void Test::runAllTests() {
    testTutorial();
    testDynamicArray();
    testRepository();
    testService();
    testWatchList();
    std::cout << "All tests passed successfully!" << std::endl;
}

void Test::testTutorial() {
    // Test constructor and getters
    Tutorial t1("C++", "John", 45, 30, 100, "http://example.com");
    assert(t1.getTitle() == "C++");
    assert(t1.getPresenter() == "John");
    assert(t1.getMinutes() == 45);
    assert(t1.getSeconds() == 30);
    assert(t1.getLikes() == 100);
    assert(t1.getLink() == "http://example.com");

    // Test default constructor
    Tutorial t2;
    assert(t2.getMinutes() == 0);
    assert(t2.getSeconds() == 0);
    assert(t2.getLikes() == 0);

    // Test setters
    t2.setTitle("Python");
    t2.setPresenter("Jane");
    t2.setDuration(30, 15);
    t2.setLikes(50);
    t2.setLink("http://python.org");

    assert(t2.getTitle() == "Python");
    assert(t2.getPresenter() == "Jane");
    assert(t2.getMinutes() == 30);
    assert(t2.getSeconds() == 15);
    assert(t2.getLikes() == 50);
    assert(t2.getLink() == "http://python.org");

    // Test equality operators
    Tutorial t3("Python", "Jane", 25, 10, 40, "http://different-link.com");
    assert(t2 == t3); // Same title and presenter

    Tutorial t4("JavaScript", "Jane", 30, 15, 50, "http://python.org");
    assert(t2 != t4); // Different title

    // Test toString method
    std::string expectedString = "Tutorial: C++ | Presenter: John | Duration: 45m 30s | Likes: 100 | Link: http://example.com";
    assert(t1.toString() == expectedString);
}

void Test::testDynamicArray() {
    // Test default constructor and add
    DynamicArray<int> arr1;
    assert(arr1.getSize() == 0);
    assert(arr1.getCapacity() == 0);
    assert(arr1.isEmpty());

    arr1.add(10);
    arr1.add(20);
    assert(arr1.getSize() == 2);
    assert(!arr1.isEmpty());
    assert(arr1[0] == 10);
    assert(arr1[1] == 20);

    // Test initialCapacity constructor
    DynamicArray<int> arr2(5);
    assert(arr2.getSize() == 0);
    assert(arr2.getCapacity() == 5);

    // Test copy constructor
    DynamicArray<int> arr3 = arr1;
    assert(arr3.getSize() == 2);
    assert(arr3[0] == 10);
    assert(arr3[1] == 20);

    // Test assignment operator
    DynamicArray<int> arr4;
    arr4 = arr1;
    assert(arr4.getSize() == 2);
    assert(arr4[0] == 10);
    assert(arr4[1] == 20);

    // Test remove
    arr1.remove(0);
    assert(arr1.getSize() == 1);
    assert(arr1[0] == 20);

    // Test clear
    arr1.clear();
    assert(arr1.getSize() == 0);
    assert(arr1.isEmpty());

    // Test resize (through add) and large array
    DynamicArray<int> arr5;
    for (int i = 0; i < 20; i++) {
        arr5.add(i);
    }
    assert(arr5.getSize() == 20);
    assert(arr5.getCapacity() >= 20);

    // Test begin and end iterators
    DynamicArray<int> arr6;
    arr6.add(1);
    arr6.add(2);
    arr6.add(3);

    int sum = 0;
    for (auto it = arr6.begin(); it != arr6.end(); ++it) {
        sum += *it;
    }
    assert(sum == 6);

    // Test const begin and end iterators
    const DynamicArray<int>& arr6const = arr6;
    sum = 0;
    for (auto it = arr6const.begin(); it != arr6const.end(); ++it) {
        sum += *it;
    }
    assert(sum == 6);

    // Test out of range exception
    try {
        int val = arr6[10]; // This should throw
        assert(false);      // Should not reach here
    } catch (const std::out_of_range&) {
        // Expected exception
    }

    try {
        const DynamicArray<int>& arr6const = arr6;
        int val = arr6const[10]; // This should throw for const version
        assert(false);           // Should not reach here
    } catch (const std::out_of_range&) {
        // Expected exception
    }

    // Test remove out of range
    try {
        arr6.remove(10); // This should throw
        assert(false);   // Should not reach here
    } catch (const std::out_of_range&) {
        // Expected exception
    }

    // Test auto resizing down when removing elements
    DynamicArray<int> arr7(16);
    for (int i = 0; i < 16; i++) {
        arr7.add(i);
    }

    int originalCapacity = arr7.getCapacity();

    // Remove items to trigger resize
    for (int i = 0; i < 13; i++) {
        arr7.remove(0);
    }

    // Check if capacity was reduced
    assert(arr7.getCapacity() < originalCapacity);
}

void Test::testRepository() {
    Repository repo;
    Tutorial t1("Python", "Jane", 30, 15, 50, "http://python.com");
    Tutorial t2("C++", "John", 45, 30, 100, "http://cpp.com");
    Tutorial t3("JavaScript", "Mike", 40, 0, 75, "http://js.com");

    // Test addTutorial and getSize
    repo.addTutorial(t1);
    assert(repo.getSize() == 1);

    repo.addTutorial(t2);
    repo.addTutorial(t3);
    assert(repo.getSize() == 3);

    // Test tutorialExists
    assert(repo.tutorialExists(t1));
    assert(!repo.tutorialExists(Tutorial("Ruby", "Sam", 35, 20, 60, "http://ruby.com")));

    // Test addTutorial with duplicate (should throw exception)
    try {
        repo.addTutorial(t1);
        assert(false); // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    // Test findTutorial
    Tutorial found = repo.findTutorial("Python", "Jane");
    assert(found == t1);

    // Test findTutorial with non-existent tutorial
    try {
        repo.findTutorial("Ruby", "Sam");
        assert(false); // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    // Test getAllTutorials
    DynamicArray<Tutorial> allTutorials = repo.getAllTutorials();
    assert(allTutorials.getSize() == 3);

    // Test updateTutorial
    Tutorial updatedT1("Python", "Jane", 35, 20, 60, "http://python-updated.com");
    repo.updateTutorial(t1, updatedT1);

    Tutorial afterUpdate = repo.findTutorial("Python", "Jane");
    assert(afterUpdate.getMinutes() == 35);
    assert(afterUpdate.getSeconds() == 20);
    assert(afterUpdate.getLikes() == 60);
    assert(afterUpdate.getLink() == "http://python-updated.com");

    // Test updateTutorial with non-existent tutorial
    try {
        repo.updateTutorial(Tutorial("Ruby", "Sam", 35, 20, 60, "http://ruby.com"),
                           Tutorial("NewRuby", "Sam", 40, 25, 70, "http://newruby.com"));
        assert(false); // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    // Test removeTutorial
    repo.removeTutorial("C++", "John");
    assert(repo.getSize() == 2);

    // Test removeTutorial with non-existent tutorial
    try {
        repo.removeTutorial("Ruby", "Sam");
        assert(false); // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }
}

void Test::testService() {
    Repository repo;
    Service service(repo);

    // Test addTutorial
    service.addTutorial("JavaScript", "Mike", 40, 0, 75, "http://js.com");
    assert(repo.getSize() == 1);

    // Test addTutorial with invalid data
    try {
        service.addTutorial("", "Mike", 40, 0, 75, "http://js.com"); // Empty title
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    try {
        service.addTutorial("JavaScript", "", 40, 0, 75, "http://js.com"); // Empty presenter
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    try {
        service.addTutorial("JavaScript", "Mike", -5, 0, 75, "http://js.com"); // Negative minutes
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    try {
        service.addTutorial("JavaScript", "Mike", 40, -10, 75, "http://js.com"); // Negative seconds
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    try {
        service.addTutorial("JavaScript", "Mike", 40, 70, 75, "http://js.com"); // Seconds >= 60
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    try {
        service.addTutorial("JavaScript", "Mike", 40, 0, -5, "http://js.com"); // Negative likes
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    try {
        service.addTutorial("JavaScript", "Mike", 40, 0, 75, ""); // Empty link
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    try {
        service.addTutorial("JavaScript", "Mike", 40, 0, 75, "invalidlink"); // Invalid link (no http)
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    // Test getAllTutorials
    DynamicArray<Tutorial> tutorials = service.getAllTutorials();
    assert(tutorials.getSize() == 1);

    // Add more tutorials for testing
    service.addTutorial("Python", "Jane", 30, 15, 50, "http://python.com");
    service.addTutorial("C++", "John", 45, 30, 100, "http://cpp.com");
    service.addTutorial("Java", "Jane", 50, 45, 120, "http://java.com");

    // Test filterTutorialsByPresenter
    DynamicArray<Tutorial> janeTutorials = service.filterTutorialsByPresenter("Jane");
    assert(janeTutorials.getSize() == 2);

    // Test empty filter (should return all tutorials)
    DynamicArray<Tutorial> allTutorials = service.filterTutorialsByPresenter("");
    assert(allTutorials.getSize() == 4);

    // Test removeTutorial
    service.removeTutorial("JavaScript", "Mike");
    assert(repo.getSize() == 3);

    // Test removeTutorial with non-existent tutorial
    try {
        service.removeTutorial("Ruby", "Sam");
        assert(false); // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    // Test updateTutorial
    service.updateTutorial("Python", "Jane", "Python3", "Jane", 35, 20, 60, "http://python3.com");

    Tutorial updated = repo.findTutorial("Python3", "Jane");
    assert(updated.getMinutes() == 35);
    assert(updated.getSeconds() == 20);
    assert(updated.getLikes() == 60);
    assert(updated.getLink() == "http://python3.com");

    // Test updateTutorial with invalid data
    try {
        service.updateTutorial("C++", "John", "", "John", 45, 30, 100, "http://cpp.com"); // Empty title
        assert(false); // Should not reach here
    } catch (const std::invalid_argument&) {
        // Expected exception
    }

    // Test watchlist functionality
    // Test addToWatchList
    Tutorial cpp = repo.findTutorial("C++", "John");
    service.addToWatchList(cpp);

    DynamicArray<Tutorial> watchList = service.getWatchList();
    assert(watchList.getSize() == 1);
    assert(watchList[0] == cpp);

    // Test likeTutorial
    int originalLikes = cpp.getLikes();
    service.likeTutorial("C++", "John");

    Tutorial cppAfterLike = repo.findTutorial("C++", "John");
    assert(cppAfterLike.getLikes() == originalLikes + 1);

    // Test removeFromWatchList without like
    service.removeFromWatchList("C++", "John", false);
    watchList = service.getWatchList();
    assert(watchList.getSize() == 0);

    // Add tutorial again to watchlist
    service.addToWatchList(cppAfterLike);

    // Test removeFromWatchList with like
    originalLikes = cppAfterLike.getLikes();
    service.removeFromWatchList("C++", "John", true);

    watchList = service.getWatchList();
    assert(watchList.getSize() == 0);

    Tutorial cppAfterRemoveWithLike = repo.findTutorial("C++", "John");
    assert(cppAfterRemoveWithLike.getLikes() == originalLikes + 1);
}

void Test::testWatchList() {
    WatchList watchList;
    Tutorial t1("Python", "Jane", 30, 15, 50, "http://python.com");
    Tutorial t2("C++", "John", 45, 30, 100, "http://cpp.com");

    // Test initially empty
    assert(watchList.isEmpty());
    assert(watchList.getSize() == 0);

    // Test addTutorial
    watchList.addTutorial(t1);
    assert(!watchList.isEmpty());
    assert(watchList.getSize() == 1);

    // Test exists
    assert(watchList.exists(t1));
    assert(!watchList.exists(t2));

    // Test addTutorial with duplicate
    try {
        watchList.addTutorial(t1);
        assert(false); // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }

    // Test getAllTutorials
    DynamicArray<Tutorial> tutorials = watchList.getAllTutorials();
    assert(tutorials.getSize() == 1);
    assert(tutorials[0] == t1);

    // Test removeTutorial
    watchList.removeTutorial("Python", "Jane");
    assert(watchList.isEmpty());
    assert(watchList.getSize() == 0);

    // Test removeTutorial with non-existent tutorial
    try {
        watchList.removeTutorial("Python", "Jane");
        assert(false); // Should not reach here
    } catch (const std::runtime_error&) {
        // Expected exception
    }
}