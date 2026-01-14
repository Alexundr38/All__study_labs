#include "PlayingField.h"

void PlayingField::createField() {
	field_view.resize(height, std::vector <char>(width, '*'));
	field_value.resize(height, std::vector <int>(width, 0));
	printField();
}

void PlayingField::printField() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << field_view[i][j] << " ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

void PlayingField::printFieldDop() {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			std::cout << field_value[i][j] << " ";
		}
		std::cout << '\n';
	}
	std::cout << '\n';
}

bool PlayingField::checkNeighbors(int length, int y, int x, bool orientation) {
	if (orientation == true) {
		for (int i = std::max(0, y - 1); i < std::min(y + 2, height); i++) {
			for (int j = std::max(0, x - 1); j - x <= std::min(int(length), width); j++) {
				if (field_value[i][j] != 0) {
					return false;
				}
			}
		}
	}
	else {
		for (int i = std::max(0, y - 1); i - y <= std::min(int(length), height); i++) {
			for (int j = std::max(0, x - 1); j < std::min(x + 2, width); j++) {
				if (field_value[i][j] != 0) {
					return false;
				}
			}
		}
	}
	return true;
}

bool PlayingField::checkCorrect(int length, int y, int x, bool orientation) {
	if (x < 0 || y < 0 || x > width || y > height) {
		return false;
	}
	int count = 0;
	if (orientation == true) {
		for (int j = x; j < x + length && j < width; j++) {
			count++;
		}
	}
	else {
		for (int i = y; i < y + length && i < height; i++) {
			count++;
		}
	}
	if (count != length) {
		return false;
	}
	return true;
}

PlayingField::PlayingField(int height, int width) {
	this->height = height;
	this->width = width;
	createField();
}

PlayingField::PlayingField() = default;

std::pair <int, int> PlayingField::getSize() {
	std::pair <int, int> sizes(height, width);
	return sizes;
}

bool PlayingField::setShip(Warship ship, int y, int x, bool orientation, int value, bool flag) {
	x--;
	y--;
	int length = ship.shipLength();																		//заменить flag на нормальную обработку
	if (checkCorrect(length, y, x, orientation) == false) {
		if (flag == true) {
			std::cout << "Корабль не может быть расположен в указанном месте.\n";
		}																					//error
		return false;
	}
	if (checkNeighbors(length, y, x, orientation) == false) {
		if (flag == true) {
			std::cout << "Корабль не может быть расположне в указанном месте.\n";
		}																					//error
		return false;
	}

	if (orientation == true) {
		for (int j = x; j < x + length; j++) {
			field_value[y][j] = value;
		}
	}
	else {
		for (int i = y; i < y + length; i++) {
			field_value[i][x] = value;
		}
	}
	if (flag == true) {
		printFieldDop();
	}
	return true;
}

void PlayingField::cellAtack(int y, int x) {
	x--;
	y--;
	if (field_value[y][x] == 0) {
		field_view[y][x] == '0';
	}
	else {
		field_view[y][x] == 'X';
	}
}

void PlayingField::printFieldDopPublic() {
	printFieldDop();
}