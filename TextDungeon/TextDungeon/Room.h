#pragma once

ref class Door;

ref class Room {
public:
	/**  Constructors  **/
	Room(array<Door^> ^doors, array<DungeonObject^> ^objects, String ^desc);
	Room();

	/**  Variables  **/
	array<Door^> ^doors;
	array<DungeonObject^> ^objects;
	String ^description;

	/** Methods **/
	void printDescription();

	~Room();
};