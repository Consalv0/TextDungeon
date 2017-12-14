#pragma once

ref class DungeonObject {
protected:
	String ^name;
public:
	/*** Constructors ***/
	DungeonObject(String^ name, String^ description);
	DungeonObject();
	~DungeonObject();

	/*** Variables ***/
	String ^usageDescription;
	virtual property String^ Name {
		String^ get(); void set(String^ x);
	}

	/*** Methods ***/
	virtual void Use();
};

