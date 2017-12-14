#include "stdafx.h"

Door::Door(Room ^%to, Room ^%from, DungeonObject ^%key, String^ name) {
	roomTo = to;
	roomFrom = from;
	this->key = key;
	this->name = name;
}

Door::Door(String^ name, DungeonObject ^%key) {
	this->name = name;
	this->key = key;
}

Door::Door(String^ name) {
	this->name = name;
}

Door::Door() {
	name = "&gDOOR&x";
}


Door::~Door() {
}

Room^ Door::RoomTo::get() {
	return roomTo;
}

void Door::RoomTo::set(Room^ r) {
	roomTo = r;
}

Room^ Door::RoomFrom::get() {
	return roomFrom;
}

void Door::RoomFrom::set(Room^ r) {
	roomFrom = r;
}

void Door::OpenDoor(Player^ player) {
	if (RoomTo->Equals(player->room)) {
			player->room = RoomFrom;
	} else {
			player->room = RoomTo;
	}

	if (!player->room->discovered) {
		player->room->discovered = true;
		Writter::WriteCenteredAt(name,
			int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
		Writter::WriteCenteredAt(player->room->firstDescription, int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F),
			int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
		Writter::ShowCursor(false);
		Console::ReadKey();
		Console::Clear();

		if (player->room->enemy != nullptr) {
			player->room->enemy->Fight(player);
		}
	}

	name = name->Replace("&r", "&t");
	name = name->Replace("&g", "&h");
}


