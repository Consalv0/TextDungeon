#include "stdafx.h"

Room::Room(Door drs[], DungeonObject objs[], String^ desc) {
	description = desc;
	objects = objs;
	doors = drs;
}

Room::Room() { description = ""; }

void Room::printDescription() {
	Writter::WriteCenteredAt(":::: YOU SEE YOURSEF IN ::::", Console::BufferWidth * .2, Console::BufferHeight * .35 - 1, Console::BufferWidth * .6, 2);
	Writter::WriteCenteredAt(description, Console::BufferWidth * .2, Console::BufferHeight * .35 + 2, Console::BufferWidth * .6, Console::BufferHeight * .3);
}

Room::~Room() {
}
