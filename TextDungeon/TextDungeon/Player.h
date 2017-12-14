#pragma once

ref class Player {
protected:
	int health;
	int initialhealth;
public:
	Player(Room ^initial, array<DungeonObject^> ^items, int health);
	Player();
	
	bool isDead;
	List<DungeonObject^> ^inventory;
	virtual property int Health {
		int get(); void set(int h);
	}
	Room^ room;
	Enemy^ enemy;

	void PrintScreenInfo();
	void ParseCommand(String ^command);
	void PrintInventory();
	void DropObject(DungeonObject ^object);
	void ReciveDamage(int dmg);
	DungeonObject^ FindInInventory(String^ command);
};

