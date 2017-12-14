#include "stdafx.h"

Room::Room(array<Door^> ^drs, array<DungeonObject^> ^objs, String ^desc, String ^n) {
	description = desc;
	name = n;
	doors = drs;
	for (int i = 0; i < doors->Length; i++) {
		if (doors[i]->roomTo == nullptr) {
			doors[i]->roomTo = this;
		} else {
			doors[i]->roomFrom = this;
		}
	}

	objects = gcnew List<DungeonObject^>();
	for (int i = 0; i < objs->Length; i++) {
		objects->Add(objs[i]);
	}
}

String^ makeDescription(String ^dcrpt, array<Door^> ^drs, array<DungeonObject^> ^objs) {
	dcrpt = dcrpt->Insert(0, "\n\n");
	for (int i = 0; i < objs->Length; i++) {
		if (i == 0) {
			if (objs->Length > 1) {
				dcrpt = dcrpt->Insert(0, "and a " + objs[i]->Name + ". ");
			} else {
				dcrpt = dcrpt->Insert(0, "a " + objs[i]->Name + ". ");
			}
		} else {
			dcrpt = dcrpt->Insert(0, "a " + objs[i]->Name + ", ");
		}
	}
	if (objs->Length == 1)
		dcrpt = dcrpt->Insert(0, "Also you see on top of a pedestal ");
	else if (objs->Length > 0)
		dcrpt = dcrpt->Insert(0, "Also in the ground you see ");
	for (int i = 0; i < drs->Length; i++) {
		if (i == 0) {
			if (drs->Length > 1) {
				dcrpt = dcrpt->Insert(0, "and a " + drs[i]->name + ". ");
			} else {
				dcrpt = dcrpt->Insert(0, "a " + drs[i]->name + ". ");
			}
		} else {
			dcrpt = dcrpt->Insert(0, "a " + drs[i]->name + ", ");
		}
	}
	dcrpt = dcrpt->Insert(0, "A room with ");
	return dcrpt;
}

Room::Room() { description = "An empty room"; name = "&EMPTY"; }

void Room::PrintDescription() {
	Writter::WriteCenteredAt("&w:::: YOU SEE YOURSEF IN ::::&x",
		int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
	Writter::WriteCenteredAt(makeDescription(description, doors, objects->ToArray()), int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F),
		int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
}

Room::~Room() {
}
