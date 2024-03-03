#include <array>
#include <chrono>
#include <mutex>
#include <optional>
#include <queue>
#include <sstream>
#include <thread>

#include "bear.h"
#include "elf_.h"
#include "npc.h"
#include "rogue.h"
#include "factory.h"

using namespace std::chrono_literals;



std::atomic_bool quit = false;
// Text Observer




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
std::ostream &operator<<(std::ostream &os, const set_t &array) {
    for (auto &n : array) n->print();
    return os;
}

struct FightEvent {
    std::shared_ptr<NPC> attacker;
    std::shared_ptr<NPC> defender;
};

class FightManager {
   private:
    std::queue<FightEvent> events;
    std::shared_mutex mtx;

    FightManager() {}

   public:
    static FightManager &get() {
        static FightManager instance;
        return instance;
    }

    void add_event(FightEvent &&event) {
        std::lock_guard<std::shared_mutex> lock(mtx);
        events.push(event);
    }

    void operator()() {
        while (true) {
            if (quit) break;
            std::optional<FightEvent> event;

            {
                std::lock_guard<std::shared_mutex> lock(mtx);
                if (!events.empty()) {
                    event = events.back();
                    events.pop();
                }
            }

            if (event) {
                if (event->attacker->is_alive())
                    if (event->defender->is_alive())
                        if (event->defender->accept(event->attacker)) {
                            int attacker_roll = std::rand() % 6 + 1;
                            int defender_roll = std::rand() % 6 + 1;
                            print()
                                << "attack: " << attacker_roll
                                << " defence: " << defender_roll << std::endl;
                            if (attacker_roll > defender_roll) {
                                event->defender->must_die();
                            }
                        }
            } else
                std::this_thread::sleep_for(100ms);
        }
    }
};

int main() {
    set_t array;  // монстры

    const int MAX_X{100};
    const int MAX_Y{100};
    const int DISTANCE{40};

    // Гененрируем начальное распределение монстров
    std::cout << "Generating ..." << std::endl;
    for (size_t i = 0; i < 50; ++i)
        array.insert(factory(NpcType(std::rand() % 3 + 1), std::rand() % MAX_X,
                             std::rand() % MAX_Y));

    std::cout << "Starting list:" << std::endl << array << std::endl;

    std::thread fight_thread(std::ref(FightManager::get()));

    std::thread move_thread([&array, MAX_X, MAX_Y, DISTANCE]() {
        while (true) {
            if (quit) break;
            // move phase
            for (std::shared_ptr<NPC> npc : array) {
                if (npc->is_alive()) {
                    int shift_x = std::rand() % 20 - 10;
                    int shift_y = std::rand() % 20 - 10;
                    npc->move(shift_x, shift_y, MAX_X, MAX_Y);
                }
            }
            // lets fight
            for (std::shared_ptr<NPC> npc : array)
                for (std::shared_ptr<NPC> other : array)
                    if (other != npc)
                        if (npc->is_alive())
                            if (other->is_alive())
                                if (npc->is_close(other))
                                    FightManager::get().add_event({npc, other});

            std::this_thread::sleep_for(50ms);
        }
    });

    for (int i = 0; i < 2; i++) {
        const int grid{20}, step_x{MAX_X / grid}, step_y{MAX_Y / grid};
        {
            std::array<char, grid * grid> fields{0};
            for (std::shared_ptr<NPC> npc : array) {
                auto [x, y] = npc->position();
                int i = x / step_x;
                int j = y / step_y;

                if (npc->is_alive()) {
                    switch (npc->get_type()) {
                        case NpcType::ElfType:
                            fields[i + grid * j] = 'E';
                            break;
                        case NpcType::RogueType:
                            fields[i + grid * j] = 'R';
                            break;
                        case NpcType::BearType:
                            fields[i + grid * j] = 'B';
                            break;

                        default:
                            break;
                    }
                } else
                    fields[i + grid * j] = '.';
            }
            print print{};

            for (int j = 0; j < grid; ++j) {
                for (int i = 0; i < grid; ++i) {
                    char c = fields[i + j * grid];
                    if (c != 0)
                        print << "[" << c << "]";
                    else
                        print << "[ ]";
                }
                print << std::endl;
            }
            print << std::endl;
        }
        std::this_thread::sleep_for(1s);
    };
    quit = true;
    move_thread.join();
    fight_thread.join();
    std::cout << "\nSurvivors:\n";
    for (auto npc : array) {
        npc->print();
    }
    return 0;
}