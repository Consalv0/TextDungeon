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
	
	Random ^rand = gcnew Random();
	Player ^player = gcnew Player(Dungeon::rooms[0], gcnew array<DungeonObject^>{}, 200);

	/***  Main Loop  ***/
	while (true) {
		Writter::SetCursor(0, 0, true);
		player->PrintScreenInfo();

		Writter::SetCursor(int(Console::WindowWidth * 0.1F), int(Console::WindowHeight * 0.9F), true);
		Console::Write(">> ");
		Writter::ShowCursor(true);
		player->ParseCommand(Console::ReadLine());

		// Console::Beep((int)Audio::Tone::A, (int)Audio::Duration::QUARTER); // Sound
		/***  Reset Screen  ***/
		Console::Clear();
		Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight);
		Console::SetWindowSize(Console::BufferWidth, Console::BufferHeight);
	}

	system("PAUSE");
	return 0;
}


