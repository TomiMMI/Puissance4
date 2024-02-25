#pragma once
#include <vector>
#include "FonctionsEtValeursPourOpenGL.h"
#include "Shader.h"
#include <map>
#include <string>

class UI {
	bool couleurUI;
	inline static std::vector<float> jetonVertices = génèreJeton(0, 0, 0.1, nombrePointsDansJeton);
	inline static std::vector<float> petitJetonUIVertices = génèreJeton(0, 0, 0.05, nombrePointsDansJeton);
	inline static std::vector<int> jetonIndices = génèreEBOJeton(nombrePointsDansJeton);
	std::map<char, Caractère> caractèresTexte;

	inline static float boutonVertices[] = {
	-0.3f, -0.1f, 0.0f,
	-0.3f,  0.1f, 0.0f,
	 0.3f,  0.1f, 0.0f,
	 0.3f, -0.1f, 0.0f
	};
	inline static int boutonIndices[]{
	0, 1, 2,
	2, 3, 0

	};

	inline static unsigned int VAOS[3] = { 0,0,0 };
	inline static unsigned int VBOS[3] = { 0,0,0 };
	inline static unsigned int EBOS[2] = { 0,0 };
	Shader shaders[3];

public:
	UI(const char* cheminFichierPolice);
	~UI();

	std::vector<int> getJetonIndices() const;
	bool getCouleurUI() const;
	void setCouleurUI(bool);
	void afficherMenu();
	void afficherUI(std::string, std::string);
};