#include "stdafx.h"

Door::Door(Room ^%to, Room ^%from, DungeonObject ^%key, String^ name) {
	roomTo = to;
	roomFrom = from;
	this->key = key;
	this->name = name;
}

Door::Door(String^ name, DungeonObject ^%key) {
	this->name = name;
	this->key = key;
}

Door::Door(String^ name) {
	this->name = name;
}

Door::Door() {
	name = "&gDOOR&x";
}


Door::~Door() {
}


