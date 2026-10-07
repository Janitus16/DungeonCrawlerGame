/*
 * DungeonCrawlerGame - dungeon crawler por turnos en terminal
 * Copyright (C) 2026  Jan Garcialoredo Garcia
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <vector>
#include "InputSystem/InputsConsts.h"
#include "Utils/ConsoleControl.h"
#include "InputSystem/InputSystem.h"

// Functions

void W() {
    CC::Lock();
    std::cout << "Arriba." << std::endl;
    CC::Unlock();
}

void S() {
    CC::Lock();
    std::cout << "Abajo." << std::endl;
    CC::Unlock();
}

void A() {
    CC::Lock();
    std::cout << "Izquierda." << std::endl;
    CC::Unlock();
}

void D() {
    CC::Lock();
    std::cout << "Derecha." << std::endl;
    CC::Unlock();
}

// Main Code Funcion Calls

int main()
{
    bool Cargando = true;

    InputSystem* iS = new InputSystem();

    // Movimientos Cruzeta
	// Minusculas
    InputSystem::KeyBinding* kbw = iS->AddListener(K_w, W);
    InputSystem::KeyBinding* kbs = iS->AddListener(K_s, S);
    InputSystem::KeyBinding* kba = iS->AddListener(K_a, A);
    InputSystem::KeyBinding* kbd = iS->AddListener(K_d, D);

	//Mayusculas
    InputSystem::KeyBinding* kbW = iS->AddListener(K_W, W);
    InputSystem::KeyBinding* kbS = iS->AddListener(K_S, S);
    InputSystem::KeyBinding* kbA = iS->AddListener(K_A, A);
    InputSystem::KeyBinding* kbD = iS->AddListener(K_D, D);

    // Salida del Programa

    InputSystem::KeyBinding* kbESC = iS->AddListener(K_ESCAPE, [iS, &Cargando]() {CC::Lock(); std::cout << "Saliendo..." << std::endl; iS->StopListen(); Cargando = false; CC::Unlock();});


    iS->StartListen();

    while (Cargando) {

    }
    return 0;
}

