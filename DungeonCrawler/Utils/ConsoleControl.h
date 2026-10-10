#pragma once

#include <mutex>

class ConsoleControl
{
public:
	enum ConsoleColor
	{
		BLACK,
		DARKBLUE,
		DARKGREEN,
		DARKCYAN,
		DARKRED,
		DARKMAGENTA,
		DARKYELLOW,
		LIGHTGREY,
		DARKGREY,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		YELLOW,
		WHITE
	};

	static void SetColor(
		ConsoleColor TextColor = WHITE,
		ConsoleColor BackgroundColor = BLACK
	);

	static void SetPosition(short int x, short int y);

	static void Clear();

	static void FillWithCharacter(
		char character,
		ConsoleColor TextColor,
		ConsoleColor BackgroundColor
	);

	static void ClearKeyBuffer();

	static int ReadNextKey();

	static int WaithForReadNextKey();

	static char WaitForReadNextChar();

	static void Lock();

	static void Unlock();
};

using CC = ConsoleControl;
