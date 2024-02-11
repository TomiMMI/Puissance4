#pragma once

#include <vector>
class Plateau
{
public:
	enum cases { Vide, Jaune, Rouge };
	std::vector<std::vector<cases>> tableau;

	Plateau();
	void afficheJeu();
	void jouer(cases&,bool);
	std::vector<cases*> tourPossible();
	cases* celPossible(int);
	bool isEnded();


};