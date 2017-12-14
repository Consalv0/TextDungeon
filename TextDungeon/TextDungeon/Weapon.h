#pragma once

ref class Weapon : public DungeonObject {
public:
	Weapon(String^ name, String^ description, int damage);
	Weapon();

	int damage;
};

