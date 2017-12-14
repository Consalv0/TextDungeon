#include "stdafx.h"

Player::Player(Room ^initial, array<DungeonObject^> ^items) {
	room = initial;
	inventory = gcnew List<DungeonObject^>();
	for (int i = 0; i < items->Length; i++) {
		inventory->Add(items[i]);
	}
}

Player::Player() {
	inventory = gcnew List<DungeonObject^>();
}


Player::~Player() {
}

void Player::PrintScreenInfo() {
	if (room) {
		room->PrintDescription();
	}
	PrintInventory();
}

void Player::PrintInventory() {
	String^ str = "";
	for (int i = 0; i < inventory->Count; i++) {
		str += inventory[i]->name;
		if (i < inventory->Count - 1) {
			str += ", ";
		}
	}

	Writter::WriteLeftAt(str,
		int(Console::BufferWidth * .7F), int(Console::BufferHeight * .7F), int(Console::BufferWidth * .3F), int(Console::BufferHeight * .3F));
}

void Player::ParseCommand(String ^command) {
	if (command->IndexOf("TAKE", StringComparison::OrdinalIgnoreCase) >= 0 ||
			command->IndexOf("USE", StringComparison::OrdinalIgnoreCase) >= 0) {
		DungeonObject^ object = Dungeon::UseObject(command, room);
		if (object == nullptr) { return; }
		Console::Clear();

		Writter::WriteCenteredAt(object->Name,
			int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
		inventory->Add(object);
		room->objects->Remove(object);
		Writter::ShowCursor(false);
		Console::ReadKey();
		Console::Clear();
		PrintScreenInfo();
	} else
	if (command->IndexOf("OPEN", StringComparison::OrdinalIgnoreCase) >= 0 ||
			command->IndexOf("PASS THROUGH", StringComparison::OrdinalIgnoreCase) >= 0) {
		Door^ door = Dungeon::GetDoor(command, room);
		if (door == nullptr) { return; }
		Console::Clear();

		bool canOpen = door->key == nullptr;
		for (int j = 0; j < inventory->Count; j++) {
			if (door->key == inventory[j]) { 
				inventory->RemoveAt(j);
				canOpen = true; break; 
			}
		}

		if (!canOpen) {
			Writter::WriteCenteredAt("&wYou need the key to open this door &rSEARCH IT&x!&x", int(Console::BufferWidth * .2), 0,
			int(Console::BufferWidth * .6F), Console::BufferHeight);
			Writter::ShowCursor(false);
			Console::ReadKey();
			Console::Clear();
			PrintScreenInfo();
			return;
		}

		if (door->roomTo->Equals(room)) {
			room = door->roomFrom;
		} else {
			room = door->roomTo;
		}

		door->name = door->name->Replace("&r", "&t");
		door->name = door->name->Replace("&g", "&h");

		Writter::WriteCenteredAt(door->name,
			int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
		Writter::WriteCenteredAt(room->name, int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F),
			int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
		Writter::ShowCursor(false);
		Console::ReadKey();
		Console::Clear();
		PrintScreenInfo();
	} else
	if (command->IndexOf("HELP", StringComparison::OrdinalIgnoreCase) >= 0) {
		Console::Clear();
		Writter::WriteCenteredAt("Humm, you keep typing. Nothing wrong could happen, &rwell... except that YOU can die&x!", int(Console::BufferWidth * .2), 0,
			int(Console::BufferWidth * .6F), Console::BufferHeight);
		Writter::ShowCursor(false);
		Console::ReadKey();
		Console::Clear();
		PrintScreenInfo();
	}
}
