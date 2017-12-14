#include "stdafx.h"


Weapon::Weapon(String^ name, String^ description, int dmg) {
	this->name = name;
	this->usageDescription = description;
	damage = dmg;
}

Weapon::Weapon() {
	name = "&rDUNGEON OBJECT&x";
	usageDescription = "";
	damage = 0;
}