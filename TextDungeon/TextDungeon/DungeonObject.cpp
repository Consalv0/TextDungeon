#include "stdafx.h"

DungeonObject::DungeonObject(String^ name, String^ description) {
	this->name = name;
	this->usageDescription = description;
}

DungeonObject::DungeonObject() {
	name = "&rDUNGEON OBJECT&x";
	usageDescription = "";
}

DungeonObject::~DungeonObject()
{
}

String^ DungeonObject::Name::get() {
	return name;
}

void DungeonObject::Name::set(String^ x) {
	name = x;
}

void DungeonObject::Use() {
	Writter::WriteCenteredAt(name,
		int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
	Writter::WriteCenteredAt(usageDescription, int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F),
		int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
}