#pragma once

ref class Player {
public:
	Player(Room ^initial, array<DungeonObject^> ^items);
	Player();
	~Player();

	List<DungeonObject^> ^inventory;
	Room^ room;

	void PrintScreenInfo();
	void ParseCommand(String ^command);
	void PrintInventory();
};

