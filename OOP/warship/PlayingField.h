#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <iostream>
#include <vector>
#include <utility>
#include "Warship.h"


class PlayingField {

private:
	std::vector <std::vector <char>> field_view;
	std::vector <std::vector <int>> field_value;
	int height;
	int width;

	void createField();

	void printField();

	void printFieldDop();

	bool checkNeighbors(int length, int y, int x, bool orientation);

	bool checkCorrect(int length, int y, int x, bool orientation);

public:
	PlayingField(int height, int width);

	PlayingField();

	std::pair <int,int> getSize();

	bool setShip(Warship ship, int y, int x, bool orientation, int value, bool flag);

	void cellAtack(int y, int x);

	void printFieldDopPublic();
};

#endif