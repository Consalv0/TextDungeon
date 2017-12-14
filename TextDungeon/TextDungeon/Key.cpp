#include "stdafx.h"

Key::Key(String ^name) {
	this->name = name;
}

Key::Key() {
	name = "&yKEY&x";
}

Key::~Key() {
}

String^ Key::Name::get() {
	return name;
}

void Key::Name::set(String^ x) {
	name = x;
}

void Key::Use() {
	Writter::WriteCenteredAt(Name,
		int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
	Writter::WriteCenteredAt("Needed to open doors", int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F),
		int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
}
