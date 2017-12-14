#pragma once

ref class Door;

ref class Room {
public:
	/**  Constructors  **/
	Room(array<Door^> ^doors, array<DungeonObject^> ^objects, String ^desc, String ^name);
	Room();

	/**  Variables  **/
	array<Door^> ^doors;
	List<DungeonObject^> ^objects;
	String ^description;
	String ^name;

	/** Methods **/
	void PrintDescription();

	~Room();
};