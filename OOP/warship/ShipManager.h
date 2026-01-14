#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H

#include <iostream>
#include <vector>
#include "Warship.h"

class ShipManager {
private:
	std::vector <int> lengths;
	std::vector <Warship> ships;
	int number;

	void createShip();


public:
	ShipManager(int number, std::vector <int> lenghts);
	ShipManager();

	std::vector <int> getLengths();

	Warship getWarship(int index);

	void setOrientation(int index, bool orientation);
};

#endif