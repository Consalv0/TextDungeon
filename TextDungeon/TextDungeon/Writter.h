#pragma once
ref class Writter
{
public:
	static int origCol, origRow;
	static void WriteAt(String^ str, int x, int y);
	static void WriteCenteredAt(String^ str, int x);
};