# DungeonCrawlerGame

A turn-based dungeon crawler that runs in the terminal and is drawn with ASCII characters, written in C++.

> \*\*Status:\*\* early development. The project structure is in place and the game is being built phase by phase (see the \[Roadmap](#roadmap)).

<!-- TODO: add a screenshot or GIF here once something is playable -->

<!-- !\[Gameplay](docs/screenshot.png) -->

## Table of contents

* [About](#about)
* [Requirements](#requirements)
* [Building and running](#building-and-running)
* [Controls](#controls)
* [Project structure](#project-structure)
* [Design notes](#design-notes)
* [Roadmap](#roadmap)
* [License](#license)

## About

The goal of this project is to build a small, complete terminal game while practicing component-based and object-oriented C++. Input is handled by a callback-based key listener that runs on its own thread, and the game is split into small classes with a single responsibility each.

## Requirements

* **Windows.** The console layer uses `conio.h` and `Windows.h`, so the project does not build on Linux or macOS.
* **Visual Studio 2026** (the solution uses the `.slnx` format) with the *Desktop development with C++* workload.
* A terminal that supports ANSI escape sequences (Windows Terminal or a recent Windows console).

## Building and running

1. Clone the repository:

```
   git clone https://github.com/Janitus16/DungeonCrawlerGame.git
   ```

2. Open `DungeonCrawlerGame.slnx` in Visual Studio.
3. Select the `x64` platform and either `Debug` or `Release`.
4. Build and run with **Ctrl + F5** (run without debugging).

## Controls

|Key|Action|
|-|-|
|`W` / `A` / `S` / `D` (upper or lower case)|Move|
|`Esc`|Quit|

> More controls (menu, combat, inventory) will be added in later phases.

## Project structure

```
DungeonCrawlerGame/
├── LICENSE
├── README.md
└── DungeonCrawler/
    ├── main.cpp
    ├── Game/            Game state and rules
    │   ├── Game         Creates and connects all the pieces
    │   ├── MapData      Map tiles and dimensions
    │   ├── Player       Player data (position, and more later)
    │   ├── Checker      Rule checks (can the player step here?)
    │   └── CharacterController   Turns key presses into player actions
    ├── Render/
    │   └── MapRenderer  Draws the map and the player with ASCII
    ├── InputSystem/     Key-binding manager (callbacks per key)
    └── Utils/           Console helpers (keys, colors, cursor)
```

## Design notes

* **Input only changes state; rendering only draws it.** Nothing is drawn from inside a key callback.
* **Callbacks run on other threads.** Key callbacks are launched from a listener thread, so shared data and console output need to be protected with mutexes.
* **No global state.** The pieces of the game receive what they need through their constructors.

## Roadmap

* \[x] **Phase 0:** Input system warm-up (WASD in both cases, quit with `Esc`)
* \[ ] **Phase 1:** An `@` that moves around a 20x10 map
* \[ ] **Phase 2:** World with rules (walls, doors, keys, chests, collisions)
* \[ ] **Phase 3:** Game states (menu, exploration, combat, game over)
* \[ ] **Phase 4:** Enemies, turn-based combat and inventory
* \[ ] **Phase 5:** Extras (several rooms, colors, fog of war, saving, random dungeons)

## License

The game code in `DungeonCrawler/Game/`, `DungeonCrawler/Render/` and `DungeonCrawler/main.cpp` is licensed under the **GNU General Public License v3.0**. See the [LICENSE](LICENSE) file for the full text.

`DungeonCrawler/Utils/` and `DungeonCrawler/InputSystem/` are outside the scope of this license.

Copyright (C) 2026 Jan Garcialoredo Garcia

