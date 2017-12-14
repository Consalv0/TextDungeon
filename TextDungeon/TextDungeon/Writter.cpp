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
	if (s->Contains("&")) {
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

String^ Writter::RemoveSyntax(String ^s) {
	array<String^> ^sections = s->Split(gcnew array<Char>{' '}, StringSplitOptions::None);
	s = "";

	Collections::IEnumerator^ myEnum = sections->GetEnumerator();
	while (myEnum->MoveNext()) {
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->Length == 0) continue;
		if (entry->IndexOf("A", StringComparison::OrdinalIgnoreCase) == 0 ||
				entry->IndexOf("OR", StringComparison::OrdinalIgnoreCase) == 0 ||
				entry->IndexOf("OF", StringComparison::OrdinalIgnoreCase) == 0 ||
				entry->IndexOf("AND", StringComparison::OrdinalIgnoreCase) == 0 ||
				entry->IndexOf("THE", StringComparison::OrdinalIgnoreCase) == 0) continue;
		if (s->Length > 0) {
			s = s->Insert(s->Length, " " + entry );
		} else {
			s = s->Insert(0, " " + entry);
		}
	}
	return s;
}

int Writter::Contains(String ^str, array<String^> ^keys) {
	if (str->Length == 0 || keys->Length == 0) return 0;
	array<String^> ^strgP = str->Split(gcnew array<Char>{' '}, StringSplitOptions::RemoveEmptyEntries);
	Collections::IEnumerator^ strgE = strgP->GetEnumerator();
	Collections::IEnumerator^ keysE = keys->GetEnumerator();
	String ^entry, ^key;
	int count = 0;
	while (keysE->MoveNext()) {
		key = safe_cast<String^>(keysE->Current);
		// Console::Write(key + " :: ");
		while (strgE->MoveNext()) {
			entry = safe_cast<String^>(strgE->Current);

			// Console::Write(entry);
			// System::Threading::Thread::Sleep(200);
			if (entry->IndexOf(key, StringComparison::OrdinalIgnoreCase) == 0) {
				// Console::Write(" !FOUND");
				count += 1;
				break;
			}
		}
		strgE->Reset();
		// Console::WriteLine(" ");
	}
	// Console::WriteLine(count);
	// System::Threading::Thread::Sleep(800);
	return count;
}
bool Writter::Contains(String ^str, array<String^> ^keys, int mistakes) {
	mistakes = mistakes >= 0 ? mistakes : -mistakes;
	if (Writter::Contains(str, keys) >= ((keys->Length - mistakes) <= 0 ? 1 : keys->Length - mistakes)) {
		return true;
	}
	return false;
}

void Writter::WriteWithColors(String ^s) {
	if (s->Contains("&")) {
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
			if (entry->Substring(0, 1) == "t") { colors->Push(ConsoleColor::DarkRed); } else
			if (entry->Substring(0, 1) == "h") { colors->Push(ConsoleColor::DarkGreen); } else
			if (entry->Substring(0, 1) == "v") { colors->Push(ConsoleColor::DarkCyan); } else
			if (entry->Substring(0, 1) == "u") { colors->Push(ConsoleColor::DarkYellow); } else
			if (entry->Substring(0, 1) == ",") { colors->Push(ConsoleColor::DarkMagenta); } else
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
	Writter::SetCursor(origRow + (Console::BufferWidth - Writter::RemoveColorSyntax(s)->Length) / 2, origCol + y, false);
	Writter::WriteWithColors(s);
}

void Writter::WriteCenteredAt(String^ s, int x, int y, int width, int height) {
	array<String^> ^words;
	String^ message = " ";
	words = s->Split(gcnew array<Char>{'\n', ' '}, StringSplitOptions::None);
	int i = 0;
	int rows = (s->Length / width + s->Split('\n')->Length) / 2;
	if (rows * 2 > height) { rows = height / 2; }

	Collections::IEnumerator^ myEnum = words->GetEnumerator();
	while (myEnum->MoveNext()) {
		if (i > height) return;
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->CompareTo("") == 0) {
			if (message->CompareTo("") != 0) {
				Writter::SetCursor(origRow + x + (width - Writter::RemoveColorSyntax(message)->Length) / 2,
					origCol + y + height / 2 + i - rows, true);
				Writter::WriteWithColors(message);
				message = "";
			}
			i++;
		}
		if (Writter::RemoveColorSyntax(message)->Length + entry->Length + 1 >= width) {
			Writter::SetCursor(origRow + x + (width - Writter::RemoveColorSyntax(message)->Length) / 2,
				origCol + y + height / 2 + i - rows, true);
			Writter::WriteWithColors(message);
			message = "";
			i++;
		}
		message = String::Concat(message + " ", entry);
	}

	Writter::SetCursor(origRow + x + (width - Writter::RemoveColorSyntax(message)->Length) / 2,
		origCol + y + height / 2 + i - rows, true);
	Writter::WriteWithColors(message);
}

void Writter::WriteLeftAt(String^ s, int x, int y, int width, int height) {
	array<String^> ^words;
	String^ message = " ";
	words = s->Split(gcnew array<Char>{'\n', ' '}, StringSplitOptions::None);
	int i = 0;
	int rows = (s->Length / width + s->Split('\n')->Length) / 2;
	if (rows * 2 > height) { rows = height / 2; }

	Collections::IEnumerator^ myEnum = words->GetEnumerator();
	while (myEnum->MoveNext()) {
		if (i > height) return;
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->CompareTo("") == 0) {
			if (message->CompareTo("") != 0) {
				Writter::SetCursor(origRow + x, origCol + y + height / 2 + i - rows, true);
				Writter::WriteWithColors(message);
				message = "";
			}
			i++;
		}
		if (message->Length + entry->Length + 1 >= width) {
			Writter::SetCursor(origRow + x, origCol + y + height / 2 + i - rows, true);
			Writter::WriteWithColors(message);
			message = "";
			i++;
		}
		message = String::Concat(message + " ", entry);
	}

	Writter::SetCursor(origRow + x, origCol + y + height / 2 + i - rows, true);
	Writter::WriteWithColors(message);
}

void Writter::WriteRightAt(String^ s, int x, int y, int width, int height) {
	array<String^> ^words;
	String^ message = "";
	words = s->Split(gcnew array<Char>{'\n', ' '}, StringSplitOptions::None);
	int i = 0;
	int rows = (s->Length / width + s->Split('\n')->Length) / 2;
	if (rows * 2 > height) { rows = height / 2; }

  Collections::IEnumerator^ myEnum = words->GetEnumerator();
	while (myEnum->MoveNext()) {
		if (i > height) return;
		String^ entry = safe_cast<String^>(myEnum->Current);
		if (entry->CompareTo("") == 0) {
			if (message->CompareTo("") != 0) {
				Writter::SetCursor(origRow + x + width - Writter::RemoveColorSyntax(message)->Length,
					origCol + y + height / 2 + i - rows, true);
				Writter::WriteWithColors(message);
				message = "";
			}
			i++;
		}
		if (message->Length + entry->Length + 1 >= width) {
			Writter::SetCursor(origRow + x + width - Writter::RemoveColorSyntax(message)->Length,
				origCol + y + height / 2 + i - rows, true);
			Writter::WriteWithColors(message);
			message = "";
			i++;
		}
		message = String::Concat(message + " ", entry);
	}

	Writter::SetCursor(origRow + x + width - Writter::RemoveColorSyntax(message)->Length,
		origCol + y + height / 2 + i - rows, true);
	Writter::WriteWithColors(message);
}