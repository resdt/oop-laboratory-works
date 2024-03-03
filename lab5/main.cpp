#include <chrono>
#include <iostream>
#include <list>

#include "allocator.h"
struct SomeStruct {
    char buffer[1024];
};


void test1() {
    auto begin = std::chrono::high_resolution_clock::now();
    std::list<SomeStruct> my_list;
    for (int i = 0; i < 500000; i++) my_list.push_back(SomeStruct());
    for (int i = 0; i < 500000; i++) my_list.erase(my_list.begin());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "test1: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       begin)
                     .count()
              << std::endl;
}

void test2() {
    auto begin = std::chrono::high_resolution_clock::now();
    std::list<SomeStruct, Allocator<SomeStruct>> my_list;
    for (int i = 0; i < 500000; i++) my_list.push_back(SomeStruct());
    for (int i = 0; i < 500000; i++) my_list.erase(my_list.begin());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "test2: "
              << std::chrono::duration_cast<std::chrono::microseconds>(end -
                                                                       begin)
                     .count()
              << std::endl;
}

int main() {
    test1();
    test2();
    return 0;
}