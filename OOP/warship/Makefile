all: Warship.o ShipManager.o PlayingField.o GameOperation.o main.o
	g++ Warship.o ShipManager.o PlayingField.o GameOperation.o main.o -o war

Warship.o: Warship.cpp Warship.h
	g++ -c Warship.cpp

PlayingField.o: PlayingField.cpp PlayingField.h Warship.h
	g++ -c PlayingField.cpp

ShipManager.o: ShipManager.cpp ShipManager.h Warship.h
	g++ -c ShipManager.cpp

GameOperation.o: GameOperation.cpp GameOperation.h ShipManager.h PlayingField.h
	g++ -c GameOperation.cpp

main.o: main.cpp GameOperation.h
	g++ -c main.cpp

clean:
	rm *.o