#include "Plateau.h"
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <sstream>

Plateau::Plateau() {
	tableau = std::vector<std::vector<cases>>(6, std::vector<cases>(7, Vide));

	const void* adressePourSeed = static_cast<const void*>(this);
	std::stringstream seed;
	seed << adressePourSeed;
	srand(atoi(seed.str().c_str()));
}
void Plateau::afficheJeu() const{
	for (std::vector<cases> line : tableau) {
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
void Plateau::jouer(cases* cel) {
	if (joueurActuel == 1) *cel = Jaune;
	else *cel = Rouge;
}
std::map<int,Plateau::cases*> Plateau::tourPossible(){
	std::map<int,cases*> possible;
	for ( int colonne = 0; colonne < (int)tableau[0].size(); colonne++) {
		cases* point = celPossible(colonne);
		if (point != nullptr) {
			possible.emplace(colonne, point);
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
int Plateau::jeuFini(){
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
bool Plateau::tour(int col) {
	std::map<int, cases*> possible = tourPossible();
	try {
		jouer(possible.at(col-1));
		joueurActuel = !joueurActuel;
		return true;
	}
	catch (const std::out_of_range& oor) {
		std::cout << "\nIl n'est pas possible de jouer sur cette colonne !\n";
		return false;
	}
}
std::string Plateau::getJoueur(int index) const {
	return joueurs[index];
}
void Plateau::afficheJoueurs() const {
	std::cout  << joueurs[!joueurActuel] << " : O\n" << joueurs[joueurActuel] << " : X\n\n";
}
bool Plateau::getActive() const {
	return active;
}
void Plateau::toggleActive() {
	active = !active;
}
int Plateau::heuristique() {
	int heuristique = 0;
	if (joueurs[joueurActuel] == "ORDI") {
		if (this->jeuFini() == 1) {
			heuristique -= 10000;
		}
			for (auto colonne = 0; colonne < tableau[0].size(); colonne++) {
				for (auto ligne = 0; ligne < tableau.size() - 2; ligne++) {
					if (tableau[ligne][colonne] != Vide &&
						tableau[ligne][colonne] == tableau[ligne + 1][colonne] &&
						tableau[ligne][colonne] == tableau[ligne + 2][colonne])
						heuristique-= 10;
				}
			}
			for (auto ligne = 0; ligne < tableau.size(); ligne++) {
				for (auto colonne = 0; colonne < tableau[0].size() - 2; colonne++) {
					if (tableau[ligne][colonne] != Vide &&
						tableau[ligne][colonne] == tableau[ligne][colonne + 1] &&
						tableau[ligne][colonne] == tableau[ligne][colonne + 2])
						heuristique -= 10;
				}
			}
			for (auto ligne = 3; ligne < tableau.size(); ligne++) {
				for (auto colonne = 0; colonne < tableau[0].size() - 2; colonne++) {
					if (tableau[ligne][colonne] != Vide &&
						tableau[ligne][colonne] == tableau[ligne - 1][colonne + 1] &&
						tableau[ligne][colonne] == tableau[ligne - 2][colonne + 2])
						heuristique -= 10;
				}
			}
			for (auto ligne = 0; ligne < tableau.size() - 3; ligne++) {
				for (auto colonne = 0; colonne < tableau[0].size() - 2; colonne++) {
					if (tableau[ligne][colonne] != Vide &&
						tableau[ligne][colonne] == tableau[ligne + 1][colonne + 1] &&
						tableau[ligne][colonne] == tableau[ligne + 2][colonne + 2])
						heuristique -= 10;
				}
			}
			return heuristique;
	}
	else {
		if (this->jeuFini() == 1) {
			heuristique += 10000;
		}
		else {
			for (auto colonne = 0; colonne < tableau[0].size(); colonne++) {
				for (auto ligne = 0; ligne < tableau.size() - 2; ligne++) {
					if (tableau[ligne][colonne] != Vide &&
						tableau[ligne][colonne] == tableau[ligne + 1][colonne] &&
						tableau[ligne][colonne] == tableau[ligne + 2][colonne])
						heuristique += 10;
				}
			}
			for (auto ligne = 0; ligne < tableau.size(); ligne++) {
				for (auto colonne = 0; colonne < tableau[0].size() - 2; colonne++) {
					if (tableau[ligne][colonne] != Vide &&
						tableau[ligne][colonne] == tableau[ligne][colonne + 1] &&
						tableau[ligne][colonne] == tableau[ligne][colonne + 2])
						heuristique += 10;
				}
			}
			for (auto ligne = 3; ligne < tableau.size(); ligne++) {
				for (auto colonne = 0; colonne < tableau[0].size() - 2; colonne++) {
					if (tableau[ligne][colonne] != Vide &&
						tableau[ligne][colonne] == tableau[ligne - 1][colonne + 1] &&
						tableau[ligne][colonne] == tableau[ligne - 2][colonne + 2])
						heuristique += 10;
				}
			}
			for (auto ligne = 0; ligne < tableau.size() - 3; ligne++) {
				for (auto colonne = 0; colonne < tableau[0].size() - 2; colonne++) {
					if (tableau[ligne][colonne] != Vide &&
						tableau[ligne][colonne] == tableau[ligne + 1][colonne + 1] &&
						tableau[ligne][colonne] == tableau[ligne + 2][colonne + 2])
						heuristique += 10;
				}
			}
			return heuristique;
		}
	}
}
int Plateau::minimaxAlphabeta(int profondeur, int alpha, int beta, bool noeudMin) {
	if (this->jeuFini() || profondeur <= 0) {
		return this->heuristique() * (profondeur + 1);
	}
	else {
		if (noeudMin) {
			int valeur = 100000000;
			for (auto coupPossible : this->tourPossible()) {
				valeur = std::min(valeur, this->enfant(coupPossible.second).minimaxAlphabeta(profondeur - 1, alpha, beta, false));
				beta = std::min(beta, valeur);
				if (alpha >= valeur) {
					break;
				}
			}
			return valeur;
		}
		else {
			int valeur = -100000000;
			for (auto coupPossible : this->tourPossible()) {
				valeur = std::max(valeur, this->enfant(coupPossible.second).minimaxAlphabeta(profondeur - 1, alpha, beta, true));
				alpha = std::max(alpha, valeur);
				if (valeur >= beta) {
					break;
				}
			}
			return valeur;
		}
	}
}

Plateau Plateau::enfant(cases* modif) {
	this->jouer(modif);
	Plateau plateauEnfant = *this;
	plateauEnfant.joueurActuel = !plateauEnfant.joueurActuel;
	*modif = Vide;
	return plateauEnfant;

}
void Plateau::tourOrdi() {
	this->afficheJeu();
	std::cout << "\nORDI joue... \n";
	std::vector<cases*> meilleursTours;
	std::vector<int> valeurs;
	int valeurMax = -100000000;

	for (auto tourEnfant : this->tourPossible()) {

		int valeurEnfant = this->enfant(tourEnfant.second).minimaxAlphabeta(5, -10000,10000,true);
		if (valeurEnfant > valeurMax) {
			meilleursTours.clear();
			valeurMax = valeurEnfant;
			meilleursTours.push_back(tourEnfant.second);
		}
		else if (valeurEnfant == valeurMax) {
			meilleursTours.push_back(tourEnfant.second);
		}
	}
	if (meilleursTours.size() == 1) {
		this->jouer(meilleursTours[0]);
		this->afficheJeu();
		this->afficheJoueurs();
		joueurActuel = !joueurActuel;
	}
	else {
		this->jouer(meilleursTours[meilleursTours.size()/2]);
		this->afficheJeu();
		this->afficheJoueurs();
		joueurActuel = !joueurActuel;
	}

}
int Plateau::getMode() const {
	return mode;
}
void Plateau::setMode(int i) {
	mode = i;

}
void Plateau::setJoueurs(std::string J1, std::string J2) {
	int indextab = rand() % 2;


	joueurs[indextab] = J1;
	joueurs[!indextab] = J2;
}
void Plateau::setIsTourOrdi(bool val) {
	isTourOrdi = val;
}
bool Plateau::getIsTourOrdi() const {
	return isTourOrdi;
}