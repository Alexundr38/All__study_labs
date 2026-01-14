#include "Warship.h"

Warship::Warship(int length) {
	this->length = length;
	damage_ship.resize(length);
	for (int i = 0; i < length; i++) {
		damage_ship[i] = whole;
	}
}

Warship::Warship() = default;

void Warship::causeDamage(int index) {
	switch (damage_ship[index]){
		case whole:
			damage_ship[index] = damaged;
			break;
		case damaged:
			damage_ship[index] = destroyed;
			break;
	}
}

void Warship::setOrientation(bool orientation) {
	this->orientation = orientation;
}

bool Warship::isDestroyed() {
	for (int i = 0; i < length; i++) {
		int count = 0;
		if (damage_ship[i] != destroyed) {
			return false;
		}
	}
	return true;
}

int Warship::shipLength() {
	return length;
}