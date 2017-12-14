#include "stdafx.h"

Key::Key(String ^name) {
	this->name = name;
}

Key::Key() {
	name = "&yKEY&x";
}

Key::~Key() {
}

String^ Key::Name::get() {
	return name;
}

void Key::Name::set(String^ x) {
	name = x;
}
