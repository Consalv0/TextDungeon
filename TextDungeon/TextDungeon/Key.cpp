#include "stdafx.h"

Key::Key(Door ^door, String ^name) {
	this->name = name;
}

Key::Key() {
	name = "&yKEY&x";
}


Key::~Key() {
}
