#include "Game.h"

int main() {
	Game* jeu = new Game();
	jeu->jouer(0, 1, 2);
	jeu->jouer(1, 6, 6);
	jeu->afficheJeu();
}