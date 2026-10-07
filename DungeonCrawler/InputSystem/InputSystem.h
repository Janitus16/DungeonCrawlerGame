#pragma once
#include "InputsConsts.h"
#include <list>
#include <map>
#include <thread>
#include <mutex>
#include <functional>

class InputSystem
{
public:
	// Definiciones de la herramienta

	class KeyBinding {

		friend class InputSystem;

	public:

		// Funcion movil como variable
		typedef std::function<void()> OnKeyPress;

	private:

		int _key;
		OnKeyPress _onKeyPress;

		// Constructor / Destructor Input System
		KeyBinding(int key, OnKeyPress onKeyPress);
		~KeyBinding();

	};

	typedef std::list<KeyBinding*> KeyBindingList;
	typedef std::map<int, KeyBindingList> KeyBindingMap;

public:
	// Funciones de la herramienta
	InputSystem();
	~InputSystem();

	KeyBinding* AddListener(int key, KeyBinding::OnKeyPress onKeyPress);
	void RemoveAndDeleteListener(KeyBinding* keyBinding);

	/// <summary>
	/// !!This function starts key listening on thread!!
	/// </summary>

	void StartListen();
	void StopListen();

private:
	// Configuración

	enum State
	{
		Starting = 0,
		Listening = 1,
		Stopping = 2,
		Stopped = 3
	};

	State _state = Stopped;

	std::mutex _classMutex;
	KeyBindingMap _keyBindingMap;

	void ListenLoop();

};

