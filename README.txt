Metroid Prime Autotracker

Source: https://github.com/EthanArmbrust/mp-qt-tracker

Automatically tracks your inventory and in game time while playing Metroid Prime randomizers on the Dolphin emulator. No user input to the tracker is required while playing.

Usage:
Run mp-qt-tracker.exe before or while dolphin is running Metroid Prime. Dolphin status is shown on the bottom of the tracker. If status is disconnected, click "Retry" to attempt to rehook into Dolphin. You may need to reopen the tracker if you have completely closed and reopened Dolphin while the tracker was running.

Building:
    Windows:
        Requires:
          Visual Studio C++ (MinGW may work but untested)
          Qt5
          CMake
        Generate .sln with cmake. Build within Visual Studio or with 'cmake --build'

    Linux:
        Requires:
          Qt5
          CMake
        Instructions:
          cd mp-qt-tracker
          mkdir build && cd build
          cmake ..
          make
        Set capabilities with 'sudo setcap cap_sys_ptrace=eip mp-qt-tracker'. This disables a kernel security feature that would prevent the tracker from reading Dolphin's memory.


Credits:
    All code in Common/, DolphinProcess/, and MemoryWatch/ is from DolphinMemoryEngine.
        Source: https://github.com/aldelaro5/Dolphin-memory-engine
    Layout inspiration and icons from Dyceron/Pwootage Prime tracker.
        Download: https://mega.nz/#!KuQ3ECSB!F0KvqUkeoBTYQiAFag7kZtHYWPg8D51q5JLGtwqRoRE

Changelog:

v1.1
    -Greatly improve performance and lower cpu usage
    -Move Charge Beam icon next to beam combos and move Space Jump Boots to bottom row
    -Added readme and license
v1.0
    -Initial Release
