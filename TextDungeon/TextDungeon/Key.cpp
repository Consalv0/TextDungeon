#include "stdafx.h"

Key::Key(String ^name) {
	this->name = name;
}

Key::Key() {
	name = "&yKEY&x";
}


Key::~Key() {
}
