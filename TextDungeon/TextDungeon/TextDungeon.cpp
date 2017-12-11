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
	
	Random ^rand = gcnew Random();
	Player ^player = gcnew Player(Dungeon::rooms[0], gcnew array<DungeonObject^>{});

	/***  Main Loop  ***/
	while (true) {
		Writter::SetCursor(0, 0, true);
		player->printScreenInfo();

		Writter::SetCursor(int(Console::WindowWidth * 0.1F), int(Console::WindowHeight * 0.9F), true);
		Console::Write(">> ");
		Writter::ShowCursor(true);
		player->parseCommand(Console::ReadLine());
		/* Writter::ShowCursor(true);
		Dungeon::dungeonObjects[0]->name = Console::ReadLine();
		Writter::ShowCursor(false); */

		// System::Threading::Thread::Sleep(5000);
		/***  Reset Screen  ***/
		// Console::Beep((int)Audio::Tone::A, (int)Audio::Duration::QUARTER); // Sound
		Console::Clear();
		Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight);
		Console::SetWindowSize(Console::BufferWidth, Console::BufferHeight);
	}

	system("PAUSE");
	return 0;
}


