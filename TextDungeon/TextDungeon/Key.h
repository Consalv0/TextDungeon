#pragma once

ref class Door;

ref class Key : public DungeonObject {
public:
	Key(Door ^door, String ^name);
	Key();
	~Key();
};

