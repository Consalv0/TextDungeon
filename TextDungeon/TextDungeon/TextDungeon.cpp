// TextDungeon.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int main(int args, char *argv) {
	Writter::origRow = Console::CursorTop;
	Writter::origCol = Console::CursorLeft;
	Console::SetBufferSize(Console::WindowWidth, Console::WindowHeight);
	Console::SetWindowSize(Console::BufferWidth, Console::BufferHeight);
	Console::Beep((int)Audio::Tone::F, (int)Audio::Duration::QUARTER);
	String^ str = Console::ReadLine();
	// Console::ForegroundColor = (ConsoleColor)Int32::Parse(str);
	Console::Write(str);
	// Audio::MainTheme();
	while (true) {
		Writter::WriteCenteredAt(Environment::TickCount % 5000 + "", 10);
	}
	system("PAUSE");
	return 0;
}

