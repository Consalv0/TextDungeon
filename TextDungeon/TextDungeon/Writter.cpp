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

String^ Writter::RemoveColorSyntax(String ^s) {
	if (s->Contains("&") >= 0) {
		array<String^> ^sections = s->Split(gcnew array<Char>{'&'}, StringSplitOptions::None);
		s = "";

		Collections::IEnumerator^ myEnum = sections->GetEnumerator();
		while (myEnum->MoveNext()) {
			String^ entry = safe_cast<String^>(myEnum->Current);
			if (entry->Length == 0) continue;
			entry = entry->Remove(0, 1);
			s = s->Insert(0, entry);
		}
		s = s->Insert(0, " ");
	}
	return s;
}

void Writter::WriteWithColors(String ^s) {
	if (s->Contains("&") >= 0) {
		array<String^> ^sections = s->Split(gcnew array<Char>{'&'}, StringSplitOptions::None);

		Collections::IEnumerator^ myEnum = sections->GetEnumerator();
		while (myEnum->MoveNext()) {
			String^ entry = safe_cast<String^>(myEnum->Current);
			if (entry->Length == 0) { Console::Write("&" + entry); continue; }
			if (entry->Substring(0, 1) == "r") { colors->Push(ConsoleColor::Red); } else
			if (entry->Substring(0, 1) == "g") { colors->Push(ConsoleColor::Green); } else
			if (entry->Substring(0, 1) == "b") { colors->Push(ConsoleColor::Cyan); } else
			if (entry->Substring(0, 1) == "y") { colors->Push(ConsoleColor::Yellow); } else
			if (entry->Substring(0, 1) == "m") { colors->Push(ConsoleColor::Magenta); } else
			if (entry->Substring(0, 1) == "n") { colors->Push(ConsoleColor::Gray); } else
			if (entry->Substring(0, 1) == "w") { colors->Push(ConsoleColor::White); } else
			if (entry->Substring(0, 1) == "x") { if (colors->Count > 0) colors->Pop(); } else
			if (entry->Substring(0, 1) == "!") { Console::ResetColor(); colors->Clear(); } else
			if (entry->Substring(0, 1) == " ") { Console::Write(entry); continue; } else
			if (entry->Substring(0, 1) == "&") { Console::Write("&" + entry); continue; } else { Console::Write("&" + entry); continue; }
			entry = entry->Remove(0, 1);
			if (colors->Count > 0) {
				Console::ForegroundColor = (ConsoleColor)colors->Peek();
			} else {
				Console::ResetColor();
			}
			Console::Write(entry);
		}
	} else {
		Console::Write(s);
	}
}

void Writter::WriteAt(String ^s, int x, int y) {
	x %= Console::BufferWidth - s->Length;
	y %= Console::BufferHeight;
	Console::SetCursorPosition(origCol + x, origRow + y);
	Writter::WriteWithColors(s);
}


void Writter::WriteCenteredAt(String^ s, int y) {
	y %= Console::BufferHeight;
	Writter::SetCursor(origRow + (Console::BufferWidth - Writter::RemoveColorSyntax(s)->Length) * 0.5, origCol + y, false);
	Writter::WriteWithColors(s);
}

void Writter::WriteCenteredAt(String^ s, int x, int y, int width, int height) {
	array<String^> ^words;
	String^ message = " ";
	words = s->Split(gcnew array<Char>{'\n', ' '}, StringSplitOptions::None);
	int i = 0;
	int rows = (s->Length / width + s->Split('\n')->Length) * 0.5;
	if (rows * 2 > height) { rows = height / 2; }

	Collections::IEnumerator^ myEnum = words->GetEnumerator();
	while (myEnum->MoveNext()) {
		if (i > height) return;
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->CompareTo("") == 0) {
			if (message->CompareTo("") != 0) {
				Writter::SetCursor(origRow + x + (width - Writter::RemoveColorSyntax(message)->Length) * 0.5,
					origCol + y + height * 0.5 + i - rows, true);
				Writter::WriteWithColors(message);
				message = "";
			}
			i++;
		}
		if (Writter::RemoveColorSyntax(message)->Length + entry->Length + 1 >= width) {
			Writter::SetCursor(origRow + x + (width - Writter::RemoveColorSyntax(message)->Length) * 0.5,
				origCol + y + height * 0.5 + i - rows, true);
			Writter::WriteWithColors(message);
			message = "";
			i++;
		}
		message = String::Concat(message + " ", entry);
	}

	Writter::SetCursor(origRow + x + (width - Writter::RemoveColorSyntax(message)->Length) * 0.5,
		origCol + y + height * 0.5 + i - rows, true);
	Writter::WriteWithColors(message);
}

void Writter::WriteLeftAt(String^ s, int x, int y, int width, int height) {
	array<String^> ^words;
	String^ message = " ";
	words = s->Split(gcnew array<Char>{'\n', ' '}, StringSplitOptions::None);
	int i = 0;
	int rows = (s->Length / width + s->Split('\n')->Length) * 0.5;
	if (rows * 2 > height) { rows = height / 2; }

	Collections::IEnumerator^ myEnum = words->GetEnumerator();
	while (myEnum->MoveNext()) {
		if (i > height) return;
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->CompareTo("") == 0) {
			if (message->CompareTo("") != 0) {
				Writter::SetCursor(origRow + x, origCol + y + height * 0.5 + i - rows, true);
				Writter::WriteWithColors(message);
				message = "";
			}
			i++;
		}
		if (message->Length + entry->Length + 1 >= width) {
			Writter::SetCursor(origRow + x, origCol + y + height * 0.5 + i - rows, true);
			Writter::WriteWithColors(message);
			message = "";
			i++;
		}
		message = String::Concat(message + " ", entry);
	}

	Writter::SetCursor(origRow + x, origCol + y + height * 0.5 + i - rows, true);
	Writter::WriteWithColors(message);
}

void Writter::WriteRightAt(String^ s, int x, int y, int width, int height) {
	array<String^> ^words;
	String^ message = "";
	words = s->Split(gcnew array<Char>{'\n', ' '}, StringSplitOptions::None);
	int i = 0;
	int rows = (s->Length / width + s->Split('\n')->Length) * 0.5;
	if (rows * 2 > height) { rows = height / 2; }

  Collections::IEnumerator^ myEnum = words->GetEnumerator();
	while (myEnum->MoveNext()) {
		if (i > height) return;
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->CompareTo("") == 0) {
			if (message->CompareTo("") != 0) {
				Writter::SetCursor(origRow + x + width - Writter::RemoveColorSyntax(message)->Length,
					origCol + y + height * 0.5 + i - rows, true);
				Writter::WriteWithColors(message);
				message = "";
			}
			i++;
		}
		if (message->Length + entry->Length + 1 >= width) {
			Writter::SetCursor(origRow + x + width - Writter::RemoveColorSyntax(message)->Length,
				origCol + y + height * 0.5 + i - rows, true);
			Writter::WriteWithColors(message);
			message = "";
			i++;
		}
		message = String::Concat(message + " ", entry);
	}

	Writter::SetCursor(origRow + x + width - Writter::RemoveColorSyntax(message)->Length,
		origCol + y + height * 0.5 + i - rows, true);
	Writter::WriteWithColors(message);
}