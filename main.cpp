#include "Plateau.h"

int main() {
	Plateau* jeu = new Plateau();
	for (auto cel : jeu->tourPossibles()) {
		jeu->jouer(*cel, true);
	}
	jeu->afficheJeu();
}