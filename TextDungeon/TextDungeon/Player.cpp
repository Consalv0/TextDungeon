#include "stdafx.h"

Player::Player(Room ^initial, array<DungeonObject^> ^items, int hp) {
	room = initial;
	inventory = gcnew List<DungeonObject^>();
	for (int i = 0; i < items->Length; i++) {
		inventory->Add(items[i]);
	}
	initialhealth = hp;
	health = hp;
}

Player::Player() {
	inventory = gcnew List<DungeonObject^>();
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
		str += inventory[i]->Name;
		if (i < inventory->Count - 1) {
			str += ", ";
		}
	}

	Writter::WriteLeftAt(str,
		int(Console::BufferWidth * .7F), int(Console::BufferHeight * .7F), int(Console::BufferWidth * .3F), int(Console::BufferHeight * .3F));
}

void Player::DropObject(DungeonObject ^object) {
	inventory->Remove(object);
	room->objects->Add(object);
}

int Player::Health::get() {
	return health;
}
void Player::Health::set(int x) {
	health = x;
	isDead = health <= 0;
}

void Player::ReciveDamage(int dmg) {
	if (dmg <= 0) return;
	Health -= dmg;
	Writter::WriteCenteredAt("&nYOU recive an attack and recived &r" + dmg + "&x of damage&x", int(Console::BufferWidth * .2), 0, int(Console::BufferWidth * .6F), Console::BufferHeight);
	Console::ReadKey();
}

DungeonObject^ Player::FindInInventory(String^ command) {
	if (room == nullptr) return nullptr;
	int count = 0;
	DungeonObject ^object;
	for (int i = 0; i < inventory->Count; i++) {
		array<String^> ^objectname = Writter::RemoveSyntax(Writter::RemoveColorSyntax(inventory[i]->Name))->Split(gcnew array<Char>{' '}, StringSplitOptions::RemoveEmptyEntries);
		if (Writter::Contains(command, objectname, 1)) {
			count++;
			object = inventory[i];
		}
	}
	if (count != 1) {
		Console::Clear();
		Writter::WriteCenteredAt("&nYour clunky bag does not contain that&x", int(Console::BufferWidth * .2), 0, int(Console::BufferWidth * .6F), Console::BufferHeight);
		Writter::ShowCursor(false);
		Console::ReadKey();
		Console::Clear();
		return nullptr;
	}
	return object;
}

void Player::ParseCommand(String ^command) {
	if (enemy != nullptr) {
		if (command->IndexOf("HIT", StringComparison::OrdinalIgnoreCase) >= 0 ||
				command->IndexOf("PUNCH", StringComparison::OrdinalIgnoreCase) >= 0 ||
				command->IndexOf("KICK", StringComparison::OrdinalIgnoreCase) >= 0) {
			enemy->Health -= 10;
			Console::Clear();
			Writter::WriteCenteredAt(enemy->name + "\n&r" + -10 + "&x", int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F),
				int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
			Console::ReadKey();
		} else
		if (command->IndexOf("USE", StringComparison::OrdinalIgnoreCase) >= 0 ||
				command->IndexOf("USING", StringComparison::OrdinalIgnoreCase) >= 0) {
			DungeonObject^ object = FindInInventory(command);
			if (dynamic_cast<Weapon^>(object) == nullptr) {
				Writter::WriteCenteredAt(enemy->name + " does not take any damage from the " + object->Name, int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F), int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
				Console::ReadKey();
				return;
			}
			Console::Clear();

			Writter::WriteCenteredAt(enemy->name + "\n&r-" + dynamic_cast<Weapon^>(object)->damage + "&x", int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F), int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
			enemy->Health -= dynamic_cast<Weapon^>(object)->damage;
			Writter::ShowCursor(false);
			Console::ReadKey();
			Console::Clear();
		}
		return;
	}
	if (command->IndexOf("DROP", StringComparison::OrdinalIgnoreCase) >= 0) {
		DungeonObject^ object = FindInInventory(command);
		if (object == nullptr) { return; }
		Console::Clear();
		DropObject(object);
		PrintScreenInfo();
	} else
	if (command->IndexOf("USE", StringComparison::OrdinalIgnoreCase) >= 0) {
		DungeonObject^ object = FindInInventory(command);
		if (object == nullptr) { return; }
		Console::Clear();

		Writter::WriteCenteredAt(object->Name,
			int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
		object->Use();
		Writter::ShowCursor(false);
		Console::ReadKey();
		Console::Clear();
		PrintScreenInfo();
	} else
	if (command->IndexOf("TAKE", StringComparison::OrdinalIgnoreCase) >= 0) {
		DungeonObject^ object = Dungeon::TakeObject(command, room);
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
				inventory->RemoveAt(j); // --- > Maybe Removing KEY
				door->key = nullptr;
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

		door->OpenDoor(this);
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
