#pragma once
#include <memory>
#include <iostream>
#include <fstream>

struct NPC;

struct IFightObserver {
    virtual void on_fight(const std::shared_ptr<NPC> attacker,
                          const std::shared_ptr<NPC> defender, bool win) = 0;
    virtual ~IFightObserver() = default;
};

class TextObserver : public IFightObserver {
   private:
    TextObserver();

   public:
    static std::shared_ptr<IFightObserver> get();
    void on_fight(const std::shared_ptr<NPC> attacker,
                  const std::shared_ptr<NPC> defender, bool win) override;
};

class FileObserver : public IFightObserver {
   private:
    FileObserver(const std::string &filename);
    std::ofstream file;

   public:
    static std::shared_ptr<IFightObserver> get();
    void on_fight(const std::shared_ptr<NPC> attacker,
                  const std::shared_ptr<NPC> defender, bool win) override;
};
