#include <ctime>
#include <filesystem>

#include "bear.h"
#include "elf_.h"
#include "npc.h"
#include "rogue.h"
#include "factory.h"
#include "visitor.h"

std::string get_random_string(const std::size_t len) {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (std::size_t i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}


// save array to file
void save(const set_t &array, const std::string &filename) {
    std::ofstream fs(filename);
    fs << array.size() << std::endl;
    for (auto &n : array) n->save(fs);
    fs.flush();
    fs.close();
}

set_t load(const std::string &filename) {
    set_t result;
    std::ifstream is(filename);
    if (is.good() && is.is_open()) {
        int count;
        is >> count;
        for (int i = 0; i < count; ++i) result.insert(factory(is));
        is.close();
    } else
        std::cerr << "Error: " << std::strerror(errno) << std::endl;
    return result;
}

// print to screen


int main() {
    set_t array;  // монстры
    std::srand((unsigned)time(NULL) * getpid());
    // Гененрируем начальное распределение монстров
    if (!std::filesystem::exists("npc.txt")) {
        std::cout << "Generating ..." << std::endl;
        for (size_t i = 0; i < 10; ++i)
            array.insert(factory(NpcType(std::rand() % 3 + 1),
                                 std::rand() % 501, std::rand() % 501,
                                 get_random_string(6)));
        std::cout << "Saving ..." << std::endl;

        save(array, "npc.txt");
    }
    std::cout << "Loading ..." << std::endl;
    array = load("npc.txt");

    std::cout << "Fighting ..." << std::endl << array;

    for (size_t distance = 100; (distance <= 500) && !array.empty();
         distance += 100) {
        std::cout << std::endl << "Fight on dist " << distance << std::endl;
        auto dead_list = fight(array, distance);
        for (auto &d : dead_list) array.erase(d);
        std::cout << std::endl
                  << "Fight stats ----------" << std::endl
                  << "distance: " << distance << std::endl
                  << "killed: " << dead_list.size() << std::endl
                  << "----------------------" << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Survivors:\n" << array;

    return 0;
}