#pragma once

class Room {
public:
	/**  Constructors  **/
	Room(Door doors[], DungeonObject objects[], String^ desc);
	Room();

	/**  Variables  **/
	Door *doors;
	DungeonObject *objects;
	gcroot<String^> description;

	/** Methods **/
	void printDescription();

	~Room();
};