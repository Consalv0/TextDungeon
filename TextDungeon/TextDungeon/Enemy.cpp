#include "stdafx.h"

Enemy::Enemy(int health, array<DungeonObject^> ^loot, String ^name, String^ description) {
	initialHealth = health;
	Health = health;
	this->loot = loot;
	this->name = name;
	this->description = description;
	isDead = false;
}

Enemy::Enemy() {
	initialHealth = 0;
	Health = 0;
	this->loot = gcnew array<DungeonObject^>(0);
	this->name = "ENEMY";
	this->description = "";
	isDead = false;
}

int Enemy::Health::get() {
	return health;
}
void Enemy::Health::set(int x) {
	health = x;
	isDead = health <= 0;
}

String^ Enemy::BattleDescription() {
	String ^desc = "";
	if (Health > initialHealth * 0.8F) {
		desc += "&rThe monster is full of energy and power!&x";
	} else if (Health > initialHealth * 0.5F) {
		desc += "&yThe monster is angry and a little tired!&x";
	} else if (Health > 0) {
		desc += "&nThe monster is full of injuries!&x";
	} else {
		desc += "&gYou defeated the monster!&x";
	}
	return desc;
}

void Enemy::Fight(Player ^player) {
	Writter::WriteCenteredAt(name,
		int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
	Writter::WriteCenteredAt("&wYOU have entered in combat! Good Luck&x", int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F),
			int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
	Console::ReadKey();
	player->enemy = this;
	while (!isDead) {
		Writter::WriteCenteredAt(name,
			int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
		Writter::WriteCenteredAt(BattleDescription(), int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F),
			int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
		
		Writter::SetCursor(int(Console::WindowWidth * 0.1F), int(Console::WindowHeight * 0.9F), true);
		Console::Write(">> ");
		Writter::ShowCursor(true);
		player->ParseCommand(Console::ReadLine());
		player->ReciveDamage(int((initialHealth + health) * 0.1F));
		Console::Clear();
	}
	Writter::WriteCenteredAt(name,
		int(Console::BufferWidth * .2F), int(Console::BufferHeight * .1F), int(Console::BufferWidth * .6F), 3);
	Writter::WriteCenteredAt(BattleDescription(), int(Console::BufferWidth * .2F), int(Console::BufferHeight * .15F),
		int(Console::BufferWidth * .6F), int(Console::BufferHeight * .8F));
	Writter::ShowCursor(false);
	
	String^ str = "";
	for (int i = 0; i < loot->Length; i++) {
		str += loot[i]->Name;
		if (i < loot->Length - 1) {
			str += ", ";
		}
		player->inventory->Add(loot[i]);
	}
	Writter::WriteLeftAt(str,
		int(Console::BufferWidth * .7F), int(Console::BufferHeight * .7F), int(Console::BufferWidth * .3F), int(Console::BufferHeight * .3F));
	Console::ReadKey();
	player->enemy = nullptr;
}
