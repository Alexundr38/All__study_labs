#ifndef WARSHIP_H
#define WARSHIP_H

#include <iostream>
#include <vector>

class Warship {
private:
	enum Damage {
		whole,
		damaged,
		destroyed
	};

	std::vector <Damage> damage_ship;

	bool orientation; // True == horizontal; False == vertical

	int length;

public:
	Warship(int length);

	Warship();

	void causeDamage(int index);

	void setOrientation(bool orientation);

	bool isDestroyed();

	int shipLength();
};

#endif