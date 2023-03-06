all: JeuHypermarche

JeuHypermarche: main.o Caisse.o Jeu.o Score.o Devis.o
	g++ -o JeuHypermarche main.o Caisse.o Jeu.o Score.o Devis.o

Jeu.o: Jeu.cpp Jeu.hpp
	g++ -c Jeu.cpp

Devis.o: Devis.cpp Devis.hpp
	g++ -c Devis.cpp

Caisse.o: Caisse.cpp Caisse.hpp
	g++ -c Caisse.cpp

main.o: main.cpp
	g++ -c main.cpp

Score.o: Score.cpp Score.hpp
	g++ -c Score.cpp
