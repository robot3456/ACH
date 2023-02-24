all: JeuHypermarche

JeuHypermarche: main.o caisse.o jeu.o
	g++ -o JeuHypermarche main.o caisse.o jeu.o

jeu.o: jeu.cpp jeu.hpp
	g++ -c jeu.cpp

caisse.o: caisse.cpp caisse.hpp
	g++ -c caisse.cpp

main.o: main.cpp
	g++ -c main.cpp