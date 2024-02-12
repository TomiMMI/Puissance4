#include "Plateau.h"
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <sstream>

Plateau::Plateau(std::string J1, std::string J2){
	tableau = std::vector<std::vector<cases>>(6, std::vector<cases>(7, Vide));

	//Seedage pour fonction rand() afin d'avoir un joueur aléatoire qui débutes
	const void* adressePourSeed = static_cast<const void*>(this);
	std::stringstream seed;
	seed << adressePourSeed;
	srand(atoi(seed.str().c_str()));
	int indextab = rand() % 2;


	joueurs[indextab] = J1;
	joueurs[!indextab] = J2;
}
void Plateau::afficheJeu() const{
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
	std::cout << "\n\n";
}
void Plateau::jouer(cases* cel,int joueur) {
	if (joueur) *cel = Jaune;
	else *cel = Rouge;
}
std::map<int,Plateau::cases*> Plateau::tourPossible(){
	std::map<int,cases*> possible;
	for ( int colonne = 0; colonne < (int)tableau[0].size(); colonne++) {
		cases* point = celPossible(colonne);
		if (point != nullptr) {
			possible.emplace(colonne + 1, point);
		}
	}
	return possible;
}
Plateau::cases* Plateau::celPossible(int colonne) {
	for (auto ligne = tableau.size() - 1; (int)ligne >= 0; ligne--) {
		if (tableau[ligne][colonne] == Vide) {
			cases* pointe = &tableau[ligne][colonne];
			return pointe;
		}
	} return nullptr;
}
int Plateau::jeuFini() {
	if (tourPossible().size() == 0) {
		return 2;
	}
	for (auto colonne = 0; colonne < tableau[0].size(); colonne++) {
		for (auto ligne = 0; ligne < tableau.size() - 3; ligne++) {
			if (tableau[ligne][colonne] != Vide &&
				tableau[ligne][colonne] == tableau[ligne + 1][colonne] &&
				tableau[ligne][colonne] == tableau[ligne + 2][colonne] &&
				tableau[ligne][colonne] == tableau[ligne + 3][colonne])
				return 1;
		}
	}
	for (auto ligne = 0; ligne < tableau.size(); ligne++) {
		for (auto colonne = 0; colonne < tableau[0].size() - 3; colonne++) {
			if (tableau[ligne][colonne] != Vide &&
				tableau[ligne][colonne] == tableau[ligne][colonne + 1] &&
				tableau[ligne][colonne] == tableau[ligne][colonne + 2] &&
				tableau[ligne][colonne] == tableau[ligne][colonne + 3])
				return 1;
		}
	}
	for (auto ligne = 3; ligne < tableau.size(); ligne++) {
		for (auto colonne = 0; colonne < tableau[0].size() - 3; colonne++) {
			if (tableau[ligne][colonne] != Vide &&
				tableau[ligne][colonne] == tableau[ligne - 1][colonne + 1] &&
				tableau[ligne][colonne] == tableau[ligne - 2][colonne + 2] &&
				tableau[ligne][colonne] == tableau[ligne - 3][colonne + 3])
				return 1;
		}
	}
	for (auto ligne = 0; ligne < tableau.size() - 3; ligne++) {
		for (auto colonne = 0; colonne < tableau[0].size() - 3; colonne++) {
			if (tableau[ligne][colonne] != Vide &&
				tableau[ligne][colonne] == tableau[ligne + 1][colonne + 1] &&
				tableau[ligne][colonne] == tableau[ligne + 2][colonne + 2] &&
				tableau[ligne][colonne] == tableau[ligne + 3][colonne + 3])
				return 1;
		}
	}
	return 0;
		// Compléter les 4 en ligne avec les colonnes, les lignes, les diagonales droite et gauche
		//Afficher le joueur qui gagne
		// Mettre en place une boucle de jeu pour 2j;
}
bool Plateau::tour(int col, int joueur) {
	std::map<int, cases*> possible = tourPossible();
	try {
		jouer(possible.at(col), joueur);
		return true;
	}
	catch (const std::out_of_range& oor) {
		std::cout << "\nIl n'est pas possible de jouer sur cette colonne !\n";
		return false;
	}
}
std::string Plateau::getJoueur(int index) {
	return joueurs[index];
}
void Plateau::afficheJoueurs() {
	std::cout  << joueurs[0] << " : O\n" << joueurs[1] << " : X\n\n";
}
bool Plateau::getActive() {
	return active;
}
void Plateau::toggleActive() {
	active = !active;
}