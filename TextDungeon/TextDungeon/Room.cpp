#include "stdafx.h"

Room::Room(array<Door^> ^drs, array<DungeonObject^> ^objs, String ^desc) {
	description = desc;
	doors = drs;
	objects = objs;

	description = description->Insert(0, "\n\n");
	for (int i = 0; i < objs->Length; i++) {
		if (i == 0) {
			if (objs->Length > 1) {
				description = description->Insert(0, "and a " + objs[i]->name + ". ");
			} else {
				description = description->Insert(0, "a " + objs[i]->name + ". ");
			}
		} else {
			description = description->Insert(0, "a " + objs[i]->name + ", ");
		}
	}
	if (objs->Length == 1)
		description = description->Insert(0, "Also you see on top of a pedestal ");
	else if (objs->Length > 0)
		description = description->Insert(0, "Also in the ground you see ");
	for (int i = 0; i < drs->Length; i++) {
		if (i == 0) {
			if (drs->Length > 1) {
				description = description->Insert(0, "and a " + drs[i]->name + ". ");
			} else {
				description = description->Insert(0, "a " + drs[i]->name + ". ");
			}
		} else {
			description = description->Insert(0, "a " + drs[i]->name + ", ");
		}
	}
	description = description->Insert(0, "A room with ");
}

Room::Room() { description = ""; }

void Room::printDescription() {
	Writter::WriteCenteredAt("&w:::: YOU SEE YOURSEF IN ::::&x",
		Console::BufferWidth * .2F, Console::BufferHeight * .35F - 2, Console::BufferWidth * .6F, 3);
	Writter::WriteCenteredAt(description, Console::BufferWidth * .2F, Console::BufferHeight * .35F + 2,
		Console::BufferWidth * .6F, Console::BufferHeight * .3);
}

Room::~Room() {
}
