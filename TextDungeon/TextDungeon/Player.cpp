#include "stdafx.h"

Player::Player(Room ^initial, array<DungeonObject^> ^items) {
	room = initial;
	inventory = items;
}

Player::Player() {
}


Player::~Player() {
}

void Player::printScreenInfo() {
	if (room) {
		room->printDescription();
	}
}
