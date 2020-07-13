#ifndef PRIMEHOOK_H
#define PRIMEHOOK_H

#include "MemoryWatch/MemWatchEntry.h"

struct prime_item
{
    std::string name;
    u32 offset;
    bool isCounter;
    int counter;
    MemWatchEntry *entry;
};


class PrimeHook
{
public:
    PrimeHook();
    ~PrimeHook();
    std::string get_IGT_value();
    std::string getStatus();
    std::string getGameID();
    MemWatchEntry *igt_entry;
    std::vector<std::vector<int>> item_values();
    int artifact_count();
    bool checkHook();
    bool attemptHook();


private:
    std::vector<std::vector<prime_item>> item_grid;
    std::vector<prime_item> artifact_list;
    void init_watches();
    void init_items();
    std::string format_IGT(std::string rawIGT);
    prime_item create_item(std::string name, u32 offset, bool isCounter);
    std::vector<prime_item> init_artifacts();


};

#endif // PRIMEHOOK_H
