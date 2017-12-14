#pragma once

ref class Player;

ref class Door {
protected:
	Room ^roomTo, ^roomFrom;
public:
	/*** Constructors ***/
	Door(Room ^%to, Room ^%from, DungeonObject ^%key, String^ name);
	Door(String^ name, DungeonObject ^%key);
	Door(String^ name);
	Door();
	~Door();

	/*** Variables ***/
	DungeonObject ^key;
	String^ name;
	virtual property Room^ RoomTo {
		Room^ get(); void set(Room^ r);
	}
	virtual property Room^ RoomFrom {
		Room^ get(); void set(Room^ r);
	}
	
	/*** Methods ***/
	void OpenDoor(Player^ player);
};

