#pragma once

ref class Player {
public:
	Player(Room ^initial, array<DungeonObject^> ^items);
	Player();
	~Player();

	array<DungeonObject^> ^inventory;
	Room^ room;

	void printScreenInfo();
	void parseCommand(String ^command);
};

