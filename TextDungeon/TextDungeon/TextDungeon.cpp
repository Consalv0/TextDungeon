// TextDungeon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int args, char *argv) {
	Writter::origRow = Console::CursorTop;
	Writter::origCol = Console::CursorLeft;
	Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight);
	Console::SetWindowSize(Console::BufferWidth, Console::BufferHeight);
	Writter::ShowCursor(true);

	// Console::Beep((int)Audio::Tone::F, (int)Audio::Duration::QUARTER); // Sounds
	// Audio::MainTheme(); // Play song
	// Console::ForegroundColor = (ConsoleColor)Int32::Parse(str); // Change text color

	// String ^str = Console::ReadLine(); // Ask for commands
	// Console::Write(str);

	Room d = Room(new Door[1]{ Door() }, new DungeonObject[2]{ DungeonObject() }, "A room full of doors, you notice a skull in one corner near the second door, and then a red glow under that another door is increasing and then disapears with a tail of smoke. \n What would you do?");
	
	/***  Main Loop  ***/
	while (true) {
		d.printDescription();

		System::Threading::Thread::Sleep(1000);
		/***  Reset Screen  ***/
		Writter::ShowCursor(false);
		Console::Clear();
		Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight);
		Console::SetWindowSize(Console::BufferWidth, Console::BufferHeight);
	}

	system("PAUSE");
	return 0;
}


