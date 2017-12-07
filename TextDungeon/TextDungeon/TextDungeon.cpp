// TextDungeon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int args, char *argv) {
	Writter::origRow = Console::CursorTop;
	Writter::origCol = Console::CursorLeft;
	Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight);
	Console::SetWindowSize(Console::BufferWidth, Console::BufferHeight);
	Writter::ShowCursor(true);

	// Audio::MainTheme(); // Play song
	// Console::ForegroundColor = (ConsoleColor)Int32::Parse(str); // Change text color

	// String ^str = Console::ReadLine(); // Ask for commands
	// Console::Write(str);

	Room ^d = gcnew Room(gcnew array<Door^>{ gcnew Door(), gcnew Door(), gcnew Door() }, gcnew array<DungeonObject^>{ gcnew Key() }, "A skull in one corner near the second door, and then a red glow under that another door is increasing and then disapears with a tail of smoke. &rWhat would you do next?&x");
	
	/***  Main Loop  ***/
	while (true) {
		d->printDescription();

		System::Threading::Thread::Sleep(1000);
		/***  Reset Screen  ***/
		// Console::Beep((int)Audio::Tone::A, (int)Audio::Duration::QUARTER); // Sound
		Writter::ShowCursor(false);
		Console::Clear();
		Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight);
		Console::SetWindowSize(Console::BufferWidth, Console::BufferHeight);
	}

	system("PAUSE");
	return 0;
}


