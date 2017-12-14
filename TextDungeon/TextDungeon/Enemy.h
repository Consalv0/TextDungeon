#pragma once

ref class Player;

ref class Enemy {
protected:
	int health;
	int initialHealth;
public:
	/** Constructors **/
	Enemy(int health, array<DungeonObject^> ^loot, String ^name, String^ description);
	Enemy();

	/** Variables **/
	bool isDead;
	String ^name;
	array<DungeonObject^> ^loot;
	String ^description;
	virtual property int Health {
		int get(); void set(int h);
	}
	
	/** Methods **/
	String^ BattleDescription();
	void Fight(Player^ player);
};

