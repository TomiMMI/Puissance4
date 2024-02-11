#include "Plateau.h"
#include <iostream>
#include <vector>

Plateau::Plateau() {
	tableau = std::vector<std::vector<cases>>(7, std::vector<cases>(7, Vide));
}
void Plateau::afficheJeu() {
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
void Plateau::jouer(cases& cel,bool joueur) {
	if (joueur) cel = Jaune;
	else cel = Rouge;
}
std::vector<Plateau::cases*> Plateau::tourPossible() {
	std::vector<Plateau::cases*> possible;
	for ( int colonne = 0; colonne < (int)tableau[0].size(); colonne++) {
		cases* point = celPossible(colonne);
		if (point != nullptr) {
			possible.emplace_back(point);
		}
	}
	return possible;
}
Plateau::cases* Plateau::celPossible(int colonne) {
	for (auto ligne = tableau[0].size() - 1; (int)ligne >= 0; ligne--) {
		if (tableau[ligne][colonne] == Vide) {
			cases* pointe = &tableau[ligne][colonne];
			return pointe;
		}
	} return nullptr;
}
bool Plateau::isEnded() {
	if (tourPossible().size() == 0) {
		return true;
	}
	for ()
		// Compléter les 4 en ligne avec les colonnes, les lignes, les diagonales droite et gauche
		//Afficher le joueur qui gagne
		// Mettre en place une boucle de jeu pour 2j;

}