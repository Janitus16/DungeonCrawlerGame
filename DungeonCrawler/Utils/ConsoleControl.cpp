#include "ConsoleControl.h"

#include <iostream>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#endif

namespace
{
    std::mutex consoleMutex;

#ifdef _WIN32

    bool KeyAvailable()
    {
        return _kbhit() != 0;
    }

    int ReadKey()
    {
        return _getch();
    }

#else

    class TerminalRawMode
    {
    private:
        termios _originalSettings{};
        bool _enabled = false;

    public:
        TerminalRawMode()
        {
            if (tcgetattr(STDIN_FILENO, &_originalSettings) == 0)
            {
                termios raw = _originalSettings;

                raw.c_lflag &= ~(ICANON | ECHO);
                raw.c_cc[VMIN] = 0;
                raw.c_cc[VTIME] = 0;

                tcsetattr(STDIN_FILENO, TCSANOW, &raw);

                _enabled = true;
            }
        }

        ~TerminalRawMode()
        {
            if (_enabled)
            {
                tcsetattr(STDIN_FILENO, TCSANOW, &_originalSettings);
            }
        }
    };

    TerminalRawMode& GetTerminalRawMode()
    {
        static TerminalRawMode terminal;
        return terminal;
    }

    bool KeyAvailable()
    {
        GetTerminalRawMode();

        timeval timeout{};
        fd_set readSet;

        FD_ZERO(&readSet);
        FD_SET(STDIN_FILENO, &readSet);

        return select(STDIN_FILENO + 1, &readSet, nullptr, nullptr, &timeout) > 0;
    }

    int ReadKey()
    {
        GetTerminalRawMode();

        unsigned char character = 0;

        if (read(STDIN_FILENO, &character, 1) != 1)
        {
            return 0;
        }

        // Arrow keys arrive as:
        // UP    = ESC [ A
        // DOWN  = ESC [ B
        // RIGHT = ESC [ C
        // LEFT  = ESC [ D

        if (character == 27)
        {
            unsigned char sequence[2];

            if (read(STDIN_FILENO, &sequence[0], 1) == 1 &&
                read(STDIN_FILENO, &sequence[1], 1) == 1)
            {
                if (sequence[0] == '[')
                {
                    switch (sequence[1])
                    {
                    case 'A':
                        return 72; // K_UP

                    case 'B':
                        return 80; // K_DOWN

                    case 'C':
                        return 77; // K_RIGHT

                    case 'D':
                        return 75; // K_LEFT
                    }
                }
            }

            return 27; // ESC
        }

        return character;
    }

#endif

    int GetAnsiTextColor(ConsoleControl::ConsoleColor color)
    {
        if (color >= ConsoleControl::DARKGREY)
        {
            return 90 + (color - ConsoleControl::DARKGREY);
        }

        return 30 + color;
    }

    int GetAnsiBackgroundColor(ConsoleControl::ConsoleColor color)
    {
        if (color >= ConsoleControl::DARKGREY)
        {
            return 100 + (color - ConsoleControl::DARKGREY);
        }

        return 40 + color;
    }
}

void ConsoleControl::SetColor(
    ConsoleColor TextColor,
    ConsoleColor BackgroundColor)
{
    std::cout
        << "\033["
        << GetAnsiTextColor(TextColor)
        << ";"
        << GetAnsiBackgroundColor(BackgroundColor)
        << "m";
}

void ConsoleControl::SetPosition(short int x, short int y)
{
    std::cout
        << "\033["
        << (y + 1)
        << ";"
        << (x + 1)
        << "H";
}

void ConsoleControl::Clear()
{
    std::cout << "\033[2J\033[1;1H";
}

void ConsoleControl::FillWithCharacter(
    char character,
    ConsoleColor TextColor,
    ConsoleColor BackgroundColor)
{
    int width = 80;
    int height = 25;

#ifdef _WIN32
    // Keep a safe default on Windows.
    // The game already uses the console normally.
#else
    winsize terminalSize{};

    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &terminalSize) == 0)
    {
        width = terminalSize.ws_col;
        height = terminalSize.ws_row;
    }
#endif

    SetColor(TextColor, BackgroundColor);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            std::cout << character;
        }
    }

    SetColor(WHITE, BLACK);
    SetPosition(0, 0);
}

void ConsoleControl::ClearKeyBuffer()
{
    while (KeyAvailable())
    {
        ReadKey();
    }
}

int ConsoleControl::ReadNextKey()
{
    if (KeyAvailable())
    {
        return ReadKey();
    }

    return 0;
}

int ConsoleControl::WaithForReadNextKey()
{
    int key = 0;

    while (key == 0)
    {
        if (KeyAvailable())
        {
            key = ReadKey();
        }
    }

    return key;
}

char ConsoleControl::WaitForReadNextChar()
{
    return static_cast<char>(WaithForReadNextKey());
}

void ConsoleControl::Lock()
{
    consoleMutex.lock();
}

void ConsoleControl::Unlock()
{
    consoleMutex.unlock();
}