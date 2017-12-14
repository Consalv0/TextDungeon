#pragma once

ref class DungeonObject {
public:
	/*** Constructors ***/
	DungeonObject();
	~DungeonObject();

	/*** Variables ***/

	/*** Methods ***/
	String^ name;
	virtual property String^ Name {
		String^ get(); void set(String^ x);
	}
};

