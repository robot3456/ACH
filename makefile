all: JeuHypermarche

JeuHypermarche: main.o Caisse.o Jeu.o Score.o
	g++ -o JeuHypermarche main.o Caisse.o Jeu.o Score.o

Jeu.o: Jeu.cpp Jeu.hpp
	g++ -c Jeu.cpp

Caisse.o: Caisse.cpp Caisse.hpp
	g++ -c Caisse.cpp

main.o: main.cpp
	g++ -c main.cpp

Score.co: Score.cpp Score.hpp
	g++ -c Score.cpp
