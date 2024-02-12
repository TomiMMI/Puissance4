#include "Plateau.h"
#include <iostream>
#include <string>

int main() {
	std::string J1, J2;
	std::cout << "--------------------------------------------------   Puissance 4   --------------------------------------------------\n\n";
	std::cout << "Entrez le nom du joueur 1 : ";
	std::cin >> J1;
	std::cout << "\nEntrez le nom du joueur 2 : ";
	std::cin >> J2;
	std::cout << "\n\n";

	Plateau* jeu = new Plateau(J1,J2);
	while (jeu->getActive()) {
		static int joueurActuel = 0;
		jeu->afficheJeu();
		jeu->afficheJoueurs();
		std::cout << "C'est au tour de " << jeu->getJoueur(joueurActuel) << ". Dans quelle colonne voulez vous jouer ? : ";
		int choix;
		do {
			std::cin >> choix;
		} while (!jeu->tour(choix, joueurActuel));
		switch (jeu->jeuFini()) {
		case 0 :
			break;
		case 1 :
			std::cout << "\n\nVictoire de " << jeu->getJoueur(joueurActuel) << " !\n\n";
			jeu->toggleActive();
			break;
		case 2 :
			std::cout << "\n\n Egalite !";
			jeu->toggleActive();
			break;
		}
		joueurActuel = !joueurActuel;
	}
	
}