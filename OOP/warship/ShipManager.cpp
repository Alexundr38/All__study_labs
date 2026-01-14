#include "ShipManager.h"

void ShipManager::createShip() {
	for (int i = 0; i < number; i++) {
		Warship ship(lengths[i]);
		ships.push_back(ship);
	}
}

ShipManager::ShipManager(int number, std::vector <int> lengths) {
	this->number = number;
	this->lengths = lengths;
	createShip();
}

ShipManager::ShipManager() = default;

std::vector <int> ShipManager::getLengths() {
	return lengths;
}

Warship ShipManager::getWarship(int index) {
	return ships[index];
}

void ShipManager::setOrientation(int index, bool orientation) {
	ships[index].setOrientation(orientation);
}