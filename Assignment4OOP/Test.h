//
// Created by Cezar on 26.03.2025.
//

#ifndef TEST_H
#define TEST_H
#pragma once

class Test {
public:
    static void runAllTests();

private:
    static void testTutorial();
    static void testDynamicArray();
    static void testRepository();
    static void testService();
    static void testWatchList();
};
#endif //TEST_H