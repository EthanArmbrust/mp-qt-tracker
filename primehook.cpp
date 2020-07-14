#include "primehook.h"

#include <string>
#include <stdexcept>

#include "MemoryWatch/MemWatchEntry.h"
#include "DolphinProcess/DolphinAccessor.h"
#include "Common/CommonUtils.h"

#include <iostream>

#define MEM_START 0x80000000
#define INVENTORY_START 0x804578CC




PrimeHook::PrimeHook()
{
    DolphinComm::DolphinAccessor::init();
    DolphinComm::DolphinAccessor::hook();
    DolphinComm::DolphinAccessor::updateRAMCache();
    init_watches();
    init_items();
    artifact_list = init_artifacts();
}

PrimeHook::~PrimeHook(){
    delete igt_entry;
}

std::vector<std::vector<int>> PrimeHook::item_values(){
    //DolphinComm::DolphinAccessor::updateRAMCache();
    std::vector<std::vector<int>> item_vals;

    for(unsigned i = 0; i < item_grid.size(); i++){
        std::vector<int> line;
        for(unsigned j = 0; j < item_grid[i].size(); j++){
            if(item_grid[i][j].entry->readMemoryFromRAM() == Common::MemOperationReturnCode::justK){
                line.push_back(stoi(item_grid[i][j].entry->getStringFromMemory()));
            }
        }
        item_vals.push_back(line);
    }
    return item_vals;
}

void PrimeHook::init_watches(){
    igt_entry = new MemWatchEntry;
    igt_entry->setTypeAndLength(Common::MemType::type_double, sizeof(double));
    igt_entry->setConsoleAddress(0x804578CC);
    igt_entry->setBoundToPointer(true);
    igt_entry->addOffset(0xA0);
}

prime_item PrimeHook::create_item(std::string name, u32 offset, bool isCounter)
{
    MemWatchEntry *item_entry = new MemWatchEntry;
    item_entry->setTypeAndLength(Common::MemType::type_word, sizeof(u16));
    item_entry->setConsoleAddress(INVENTORY_START);
    item_entry->setBoundToPointer(true);
    item_entry->addOffset(offset);

    prime_item item = {name, offset, isCounter, 0, item_entry};
    return item;
}


void PrimeHook::init_items(){
    std::vector<prime_item> first_row = {
      create_item("Missiles", 0x2EC, true),
      create_item("Energy Tanks", 0x38C, true),
      create_item("Wave Beam", 0x2DC, false),
      create_item("Ice Beam", 0x2D4, false),
      create_item("Plasma Beam", 0x2E4, false),
      create_item("Scan Visor", 0x2F4, false)
    };
    std::vector<prime_item> second_row = {
        create_item("Morph Ball", 0x34C, false),
        create_item("Morph Ball Bombs", 0x2FC, false),
        create_item("Boost Ball", 0x35C, false),
        create_item("Spider Ball", 0x364, false),
        create_item("Power Bombs", 0x304, true),
        create_item("Thermal Visor", 0x314, false)
    };
    std::vector<prime_item> third_row = {
        create_item("Super Missiles", 0x324, false),
        create_item("Wavebuster", 0x3AC, false),
        create_item("Ice Spreader", 0x33C, false),
        create_item("Flamethrower", 0x30C, false),
        create_item("Space Jump Boots", 0x340, false),
        create_item("X-Ray Visor", 0x334, false)
    };
    std::vector<prime_item> fourth_row = {
        create_item("Varia Suit", 0x37C, false),
        create_item("Gravity Suit", 0x374, false),
        create_item("Phazon Suit", 0x384, false),
        create_item("Charge Beam", 0x318, false),
        create_item("Grapple Beam", 0x32C, false)
    };
    item_grid = {first_row, second_row, third_row, fourth_row};
}

std::vector<prime_item> PrimeHook::init_artifacts(){

    prime_item nature = create_item("Artifact of Nature", 0x3EB, false);
    prime_item sun = create_item("Artifact of Sun", 0x3F0, false);
    prime_item spirit = create_item("Artifact of Spirit", 0x400, false);
    prime_item elder = create_item("Artifact of Elder", 0x3C0, false);
    prime_item strength = create_item("Artifact of Strength", 0x3B8, false);
    prime_item lifegiver = create_item("Artifact of Lifegiver", 0x3D0, false);
    prime_item world = create_item("Artifact of World", 0x3F8, false);
    prime_item wild = create_item("Artifact of Wild", 0x3C8, false);
    prime_item chozo = create_item("Artifact of Chozo", 0x3E0, false);
    prime_item truth = create_item("Artifact of Truth", 0x3B0, false);
    prime_item newborn = create_item("Artifact of Newborn", 0x408, false);
    prime_item warrior = create_item("Artifact of Warrior", 0x3D8, false);
    return {nature, sun, spirit, elder, strength, lifegiver, world, wild, chozo, truth, newborn, warrior};
}

int PrimeHook::artifact_count(){
    int sum = 0;
    for(prime_item i : artifact_list){
        if(i.entry->readMemoryFromRAM() == Common::MemOperationReturnCode::justK){
            if(stoi(i.entry->getStringFromMemory())){
                sum++;
            }
        }
    }
    return sum;
}

std::string PrimeHook::format_IGT(std::string raw_IGT)
{
    double dIGT;
    try
    {
        dIGT = stod(raw_IGT);
    }
    catch (const std::invalid_argument &ia)
    {
        return "??:??:??.???";
    }
    int IGT = (int)dIGT;
    int hours = IGT / 3600;
    int minutes = (IGT - (hours * 3600)) / 60;
    int seconds = IGT - ((hours * 3600) + (minutes * 60));
    int milliseconds = (int)(dIGT * 1000) % 1000;
    char buffer[50];
    sprintf(buffer, "%02d:%02d:%02d.%03d", hours, minutes, seconds, milliseconds);
    return buffer;
}

std::string PrimeHook::get_IGT_value(){
    //DolphinComm::DolphinAccessor::hook();
    DolphinComm::DolphinAccessor::updateRAMCache();
    if(igt_entry != nullptr){
        if(igt_entry->readMemoryFromRAM() == Common::MemOperationReturnCode::justK){
            return format_IGT(igt_entry->getStringFromMemory());
        }
        return "not hooked";
    }
    return "nullptr here";
}

std::string PrimeHook::getStatus(){
    DolphinComm::DolphinAccessor::DolphinStatus status = DolphinComm::DolphinAccessor::getStatus();
    if(status == DolphinComm::DolphinAccessor::DolphinStatus::hooked){
        return "hooked";
    }
    if(status == DolphinComm::DolphinAccessor::DolphinStatus::unHooked){
        return "unhooked";
    }
    if(status == DolphinComm::DolphinAccessor::DolphinStatus::notRunning){
        return "not running";
    }
    if(status == DolphinComm::DolphinAccessor::DolphinStatus::noEmu){
        return "no emu";
    }
    return "status unknown";
}

bool PrimeHook::checkHook(){
    if(getGameID() == "GM8E01"){
        return true;
    }
    else{
        return false;
    }
}

bool PrimeHook::attemptHook(){
    DolphinComm::DolphinAccessor::hook();
    if(DolphinComm::DolphinAccessor::getStatus() == DolphinComm::DolphinAccessor::DolphinStatus::hooked){
        if(getGameID() == "GM8E01"){
            return true;
        }
    }
    return false;
}


std::string PrimeHook::getGameID(){
    //std::cout << "Checking game id" << std::endl;
    DolphinComm::DolphinAccessor::updateRAMCache();
    std::string game_id = DolphinComm::DolphinAccessor::getFormattedValueFromCache(Common::dolphinAddrToOffset(0x80000000), Common::MemType::type_string, sizeof(char) * 6, Common::MemBase::base_none, true);
    //std::cout << "Checked" << std::endl;
    return game_id;
}

