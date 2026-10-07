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

