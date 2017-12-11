#include "stdafx.h"

Player::Player(Room ^initial, array<DungeonObject^> ^items) {
	room = initial;
	inventory = items;
}

Player::Player() {
}


Player::~Player() {
}

void Player::printScreenInfo() {
	if (room) {
		room->printDescription();
	}
}

void Player::parseCommand(String ^command) {
	if (command->IndexOf("OPEN", StringComparison::OrdinalIgnoreCase) >= 0 ||
			command->IndexOf("PASS THROUGH", StringComparison::OrdinalIgnoreCase) >= 0) {
		Door^ door = Dungeon::GetDoor(command, room);
		if (door == nullptr) { return; }
		Console::Clear();
		if (door->roomTo->Equals(room)) {
			room = door->roomFrom;
		} else {
			room = door->roomTo;
		}
		Writter::WriteCenteredAt(door->name, int(Console::BufferWidth * .2), 0, int(Console::BufferWidth * .6F), Console::BufferHeight);
		Writter::ShowCursor(false);
		Console::ReadKey();
		Console::Clear();
		printScreenInfo();
	} else
	if (command->IndexOf("HELP", StringComparison::OrdinalIgnoreCase) >= 0) {
		Console::Clear();
		Writter::WriteCenteredAt("Humm, you keep typing. Nothing wrong could happen, &rwell... except that YOU can die&x!", int(Console::BufferWidth * .2), 0,
			int(Console::BufferWidth * .6F), Console::BufferHeight);
		Writter::ShowCursor(false);
		Console::ReadKey();
		Console::Clear();
		printScreenInfo();
	}
}
