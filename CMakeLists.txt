cmake_minimum_required(VERSION 3.20)

project(DungeonCrawlerGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(DungeonCrawler
        DungeonCrawler/main.cpp

        DungeonCrawler/Game/CharacterController.cpp
        DungeonCrawler/Game/Checker.cpp
        DungeonCrawler/Game/Game.cpp
        DungeonCrawler/Game/MapData.cpp
        DungeonCrawler/Game/Player.cpp

        DungeonCrawler/InputSystem/InputSystem.cpp

        DungeonCrawler/Render/MapRenderer.cpp

        DungeonCrawler/Utils/ConsoleControl.cpp
)