#pragma once

ref class Writter abstract sealed {
public:
	static int origCol, origRow;
	static void ShowCursor(bool showFlag);
	static void SetCursor(int x, int y, bool restrict);
	static String^ RemoveColorSyntax(String ^strg);
	static String^ RemoveSyntax(String ^strg);
	static int Contains(String ^str, array<String^> ^words);
	static bool Contains(String ^str, array<String^> ^words, int mistakes);
	static void WriteWithColors(String ^strg);
	static void WriteAt(String ^str, int x, int y);
	static void WriteCenteredAt(String ^str, int x);
	static void WriteCenteredAt(String ^s, int x, int y, int width, int height);
	static void WriteLeftAt(String ^s, int x, int y, int width, int height);
	static void WriteRightAt(String ^s, int x, int y, int width, int height);

	static Collections::Stack ^colors = gcnew Collections::Stack();
};