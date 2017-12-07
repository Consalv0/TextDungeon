#include "stdafx.h"

void Writter::ShowCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // Set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}

void Writter::SetCursor(int x, int y, bool restrict) {
	if (x >= Console::BufferWidth) {
		if (restrict) return;
		x = Console::BufferWidth -1;
	}
	if (y >= Console::BufferHeight) {
		if (restrict) return;
		y = Console::BufferHeight -1;
	}
	if (x < 0) x = 0;
	if (y < 0) y = 0;
		
	Console::SetCursorPosition(x, y);
}

void Writter::WriteAt(String^ s, int x, int y) {
	x %= Console::BufferWidth - s->Length;
	y %= Console::BufferHeight;
	Console::SetCursorPosition(origCol + x, origRow + y);
	Console::Write(s);
}

void Writter::WriteCenteredAt(String^ s, int y) {
	y %= Console::BufferHeight;
	Writter::SetCursor(origRow + (Console::BufferWidth - s->Length) * 0.5, origCol + y, false);
	Console::Write(s);
}

array<String^>^ splitString(String^ strg) {
	array<String^> ^result;
	result = strg->Split(gcnew array<Char>{'\n', ' '}, StringSplitOptions::None);
	return result;
}

void Writter::WriteCenteredAt(String^ s, int x, int y, int width, int height) {
	array<String^> ^words;
	String^ message = " ";
	words = splitString(s);
	int i = 0;
	int rows = (s->Length / width + s->Split('\n')->Length) * 0.5;

	Collections::IEnumerator^ myEnum = words->GetEnumerator();
	while (myEnum->MoveNext()) {
		if (i > height) return;
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->CompareTo("") == 0) {
			if (message->CompareTo("") != 0) {
				Writter::SetCursor(origRow + x + (width - message->Length) * 0.5,
					origCol + y + height * 0.5 + i - rows, true);
				Console::Write(message);
				message = "";
			}
			i++;
		}
		if (message->Length + entry->Length + 1 >= width) {
			Writter::SetCursor(origRow + x + (width - message->Length) * 0.5,
				origCol + y + height * 0.5 + i - rows, true);
			Console::Write(message);
			message = "";
			i++;
		}
		message = String::Concat(message + " ", entry);
	}

	Writter::SetCursor(origRow + x + (width - message->Length) * 0.5,
		origCol + y + height * 0.5 + i - rows, true);
	Console::Write(message);
}

void Writter::WriteLeftAt(String^ s, int x, int y, int width, int height) {
	array<String^> ^words;
	String^ message = " ";
	words = splitString(s);
	int i = 0;
	int rows = (s->Length / width + s->Split('\n')->Length) * 0.5;

	Collections::IEnumerator^ myEnum = words->GetEnumerator();
	while (myEnum->MoveNext()) {
		if (i > height) return;
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->CompareTo("") == 0) {
			if (message->CompareTo("") != 0) {
				Writter::SetCursor(origRow + x, origCol + y + height * 0.5 + i - rows, true);
				Console::Write(message);
				message = "";
			}
			i++;
		}
		if (message->Length + entry->Length + 1 >= width) {
			Writter::SetCursor(origRow + x, origCol + y + height * 0.5 + i - rows, true);
			Console::Write(message);
			message = "";
			i++;
		}
		message = String::Concat(message + " ", entry);
	}

	Writter::SetCursor(origRow + x, origCol + y + height * 0.5 + i - rows, true);
	Console::Write(message);
}

void Writter::WriteRightAt(String^ s, int x, int y, int width, int height) {
	array<String^> ^words;
	String^ message = "";
	words = splitString(s);
	int i = 0;
	int rows = (s->Length / width + s->Split('\n')->Length) * 0.5;

  Collections::IEnumerator^ myEnum = words->GetEnumerator();
	while (myEnum->MoveNext()) {
		if (i > height) return;
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->CompareTo("") == 0) {
			if (message->CompareTo("") != 0) {
				Writter::SetCursor(origRow + x + width - message->Length,
					origCol + y + height * 0.5 + i - rows, true);
				Console::Write(message);
				message = "";
			}
			i++;
		}
		if (message->Length + entry->Length + 1 >= width) {
			Writter::SetCursor(origRow + x + width - message->Length,
				origCol + y + height * 0.5 + i - rows, true);
			Console::Write(message);
			message = "";
			i++;
		}
		message = String::Concat(message + " ", entry);
	}

	Writter::SetCursor(origRow + x + width - message->Length,
		origCol + y + height * 0.5 + i - rows, true);
	Console::Write(message);
}