#include "stdafx.h"
#include "Writter.h"

void Writter::WriteAt(String^ s, int x, int y) {
	x %= Console::BufferWidth - s->Length;
	y %= Console::BufferHeight;
	Console::SetCursorPosition(origCol + x, origRow + y);
	Console::Write(s);
}

void Writter::WriteCenteredAt(String^ s, int y) {
	y %= Console::BufferHeight;
	Console::SetCursorPosition(origRow + (Console::BufferWidth - s->Length) * 0.5, origCol + y);
	Console::Write(s);
}
