#include "stdafx.h"


DungeonObject::DungeonObject() {
	name = "&rDUNGEON OBJECT&x";
}

DungeonObject::~DungeonObject()
{
}

String^ DungeonObject::Name::get() {
	return name;
}

void DungeonObject::Name::set(String^ x) {
	name = x;
}