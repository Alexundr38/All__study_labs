#ifndef GAMEOPERATION_H
#define GAMEOPERATION_H

#include <iostream>
#include <vector>
#include <math.h>
#include <random>
#include <ctime>
#include "PlayingField.h"
#include "ShipManager.h"

class GameOperation {
private:

	ShipManager player_manager;
	PlayingField player_field;
	ShipManager bot_manager;
	PlayingField bot_field;

	void inputSizes();

	void inputAnswer();

	void inputCoordinates();

	void randomCoordinates(bool flag);

	void setManager();

	void infoManager(int number, std::vector <int> lengths);

	std::vector <int> countShip(int height, int width);

public:
	GameOperation();
};

#endif