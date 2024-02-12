#pragma once

#include <vector>
#include <map>
#include <string>
class Plateau
{
public:
	enum cases { Vide, Jaune, Rouge };
	std::vector<std::vector<cases>> tableau;

	Plateau(std::string,std::string);
	void afficheJeu() const;
	void afficheJoueurs();
	bool tour(int, int);
	int jeuFini();

	std::string getJoueur(int);
	bool getActive();
	void toggleActive();

private:
	std::string joueurs[2];
	bool active = true;
	std::map<int, cases*> tourPossible();
	cases* celPossible(int);
	void jouer(cases*, int);
};