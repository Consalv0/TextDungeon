#pragma once

ref class Door {
public:
	/*** Constructors ***/
	Door(Room ^to, Room ^from, DungeonObject ^key, String^ name);
	Door();
	~Door();

	/*** Variables ***/
	DungeonObject ^key;
	String^ name;
	Room ^roomTo, ^roomFrom;

	/*** Methods ***/
	
};

