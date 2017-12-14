#pragma once

ref class Door;

ref class Room {
public:
	/**  Constructors  **/
	Room(array<Door^> ^doors, array<DungeonObject^> ^objects, String ^desc, String ^name, Enemy^ enemy);
	Room(array<Door^> ^doors, array<DungeonObject^> ^objects, String ^desc, String ^name);
	Room();

	/**  Variables  **/
	bool discovered;
	array<Door^> ^doors;
	List<DungeonObject^> ^objects;
	String ^description;
	String ^firstDescription;
	Enemy ^enemy;

	/** Methods **/
	void PrintDescription();

	~Room();
};