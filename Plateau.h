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

	Plateau();
	void afficheJeu() const;
	void afficheJoueurs() const;

	bool tour(int);
	void tourOrdi();

	int minimaxAlphabeta(int profondeur, int alpha, int beta, bool noeudMin);

	int getMode() const;
	std::string getJoueur(int) const;
	bool getActive() const;
	bool getIsTourOrdi() const;
	int jeuFini();

	void toggleActive();
	void setIsTourOrdi(bool);
	void setMode(int);
	void setJoueurs(std::string, std::string);
protected:
	bool isTourOrdi = false;
	int mode = 0;
	std::string joueurs[2];
	bool active = true;
	std::map<int, cases*> tourPossible();
	cases* celPossible(int);
	void jouer(cases*);
	int heuristique();
	Plateau enfant(cases* modif);
};