#include "GameOperation.h"


void GameOperation::inputSizes() {
	int height, width;
	std::cout << "Введите размер поля в формате: высота ширина.\n";
	std::cin >> height >> width;
	this->player_field = PlayingField{ height, width };
	this->bot_field = PlayingField{ height, width };
	setManager();
	inputAnswer();
}

void GameOperation::inputAnswer() {
	std::cout << "Если хотите расставить корабли вручную, введите 1.\nЕсли хотите, чтобы корабли были расставлены автоматически, введите 0.\n";
	int value;
	std::cin >> value;
	if (value == 1) {
		inputCoordinates();
	}
	else if (value == 0) {
		randomCoordinates(true);
	}
	else {
		std::cout << "Введено некорректное значение.\n";
		inputAnswer();
	}
	player_field.printFieldDopPublic();

	randomCoordinates(false);

	bot_field.printFieldDopPublic();
}

void GameOperation::inputCoordinates() {
	std::vector <int> lenghts = player_manager.getLengths();
	int i = 0;
	while (i < lenghts.size()) {
		std::cout << "Введите координаты корабля размера " << lenghts[i] << " и его ориентацию на поле в формате: y x orientation.\n";
		std::cout << "y и x - координаты левого верхнего угла коробля, orientation - его ориентация на поле, при этом 1 - горизонтально, 0 - вертикально.\n";
		int x, y, orient;
		std::cin >> y >> x >> orient;
		bool orientation;
		if (orient == 1) {
			orientation = true;
		}
		else if (orient == 0) {
			orientation = false;
		}
		else {
			std::cout << "Введены некорректные значения.\n";
			continue;
		}
		Warship ship = player_manager.getWarship(i);

		bool check;
		check = player_field.setShip(ship, y, x, orientation, i + 1, true);
		if (check == true) {
			player_manager.setOrientation(i, orientation);
			i++;
		}
	}
																		//запуск игры
}

void GameOperation::randomCoordinates(bool flag) {
	std::vector <int> lenghts = player_manager.getLengths();
	int i = 0;
	std::pair <int, int> sizes;
	sizes = player_field.getSize();

	while (i < lenghts.size()) {
		srand(time(0));

		int x, y, orient;
		orient = rand() % 2;
		x = rand() % (sizes.second + 1);
		y = rand() % (sizes.first + 1);
		bool orientation;

		if (orient == 1) {
			orientation = true;
		}
		else {
			orientation = false;
		}

		if (flag == true) {
			Warship ship = player_manager.getWarship(i);

			bool check;
			check = player_field.setShip(ship, y, x, orientation, i + 1, false);
			if (check == true) {
				i++;
				std::cout << i;
				player_manager.setOrientation(i, orientation);
			}
		}
		else {
			Warship ship = bot_manager.getWarship(i);

			bool check;
			check = bot_field.setShip(ship, y, x, orientation, i + 1, false);
			if (check == true) {
				i++;
				std::cout << i;
				bot_manager.setOrientation(i, orientation);
			}
		}
	}

	
	//запуск игры
}

void GameOperation::setManager() {
	std::vector <int> info;
	std::pair <int, int> sizes;
	sizes = player_field.getSize();
	info = countShip(sizes.first, sizes.second);
	int number = info[4];
	info.pop_back();
	std::vector <int> lenghts;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < info[i]; j++) {
			lenghts.push_back(4 - i);
		}
	}
	this->player_manager = ShipManager{ number, lenghts };
	this->bot_manager = ShipManager{ number, lenghts };
	infoManager(number, info);
}

void GameOperation::infoManager(int number, std::vector <int> lenghts) {
	std::cout << "В игре будет " << number << " кораблей.\n";
	for (int i = 0; i < 4; i++) {
		std::cout << lenghts[i] << " " << 4 - i << "-палубных кораблей;\n";
	}
	std::cout << "\n";
}

std::vector <int> GameOperation::countShip(int height, int width) {
	int area = height * width;
	int count = ceil(area * 0.2);
	std::vector <int> arr;
	int number;
	int first = 0, second = 0, third = 0, fourth = 0;
	if (area <= 100) {
		for (int f = 1; f < 5; f++) {
			for (int s = 0; s < ceil(count * 0.5 / 2); s++) {
				for (int t = 0; t < ceil(count * 0.45 / 3); t++) {
					for (int fr = 0; fr < ceil(count * 0.26 / 4); fr++) {
						if (f + s * 2 + t * 3 + fr * 4 == count) {
							if (fr <= t && t <= s && s <= f) {
								arr.push_back(fr);
								arr.push_back(t);
								arr.push_back(s);
								arr.push_back(f);
								number = fr + t + s + f;
							}
						}
					}
				}
			}
		}
	}
	else {
		for (int f = 1; f < ceil(count * 0.25); f++) {
			for (int s = 0; s < ceil(count * 0.4 / 2); s++) {
				for (int t = 0; t < ceil(count * 0.4 / 3); t++) {
					for (int fr = 0; fr < ceil(count * 0.31 / 4); fr++) {
						if (f + s * 2 + t * 3 + fr * 4 == count) {
							if (fr <= t && t <= s && s <= f) {
								arr.push_back(fr);
								arr.push_back(t);
								arr.push_back(s);
								arr.push_back(f);
								number = fr + t + s + f;
							}
						}
					}
				}
			}
		}
	}
	arr.push_back(number);
	return arr;
}

GameOperation::GameOperation() {
	std::cout << "Начало игры\n";
	inputSizes();
}