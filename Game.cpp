#include "Game.h"
#include <iostream>
#include <vector>

Game::Game() {
	tableau = std::vector<std::vector<cases>>(7, std::vector<cases>(7, Vide));
}
void Game::afficheJeu() {
	for (auto line : tableau) {
		for (auto cel : line) {
			switch (cel) {
				case(Vide) :
					std::cout << " . ";
					break;
				case(Jaune) :
					std::cout << " X ";
					break;
				case(Rouge) :
					std::cout << " O ";
					break;
			}
		}
		std::cout << "\n";
	}
}
void Game::jouer(int joueur, int ligne, int colonne) {
	if (joueur) tableau[ligne][colonne] = Jaune;
	else tableau[ligne][colonne] = Rouge;
}