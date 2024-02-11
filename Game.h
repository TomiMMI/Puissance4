#pragma once

#include <vector>
class Game
{
public:
	enum cases { Vide, Jaune, Rouge };
	std::vector<std::vector<cases>> tableau;

	Game();
	void afficheJeu();
	void jouer(int, int, int);
	void tourPossibles();


};