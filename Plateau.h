#pragma once

#include <vector>
#include <map>
#include <string>
class Plateau
{
public:
	enum cases { Vide, Jaune, Rouge };
	std::vector<std::vector<cases>> tableau;
	 int joueurActuel = 0;

	Plateau(std::string,std::string);
	void afficheJeu() const;
	void afficheJoueurs();
	bool tour(int);
	int jeuFini();
	int minimaxAlphabeta(int profondeur, int alpha, int beta, bool noeudMin);

	std::string getJoueur(int);
	bool getActive();
	void toggleActive();
	void tourOrdi();
	//int minimax(int profondeur, bool maxPlayer);

private:
	std::string joueurs[2];
	bool active = true;
	std::map<int, cases*> tourPossible();
	cases* celPossible(int);
	void jouer(cases*);
	int heuristique();
	Plateau enfant(cases* modif);
};