#pragma once
#include "Plateau.h"
#include "Shader.h"
#include <string>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <vector>
#include "FonctionsEtValeursPourOpenGL.h"
#include "UI.h"

class PlateauGraphique : public Plateau {

public :
	PlateauGraphique();
	void afficherTableauGraphique();
	bool dansLePlateau() const ;
	~PlateauGraphique();

	Shader getShader(int) const;
	
	UI UIJeu;
private:
	float inline static plateauVertices[]{
		-0.6f,  0.7f, 0.0f, 0.0f, 0.0f, 0.8f,
		 0.6f,  0.7f, 0.0f, 0.0f, 0.0f, 0.8f,
		-0.6f, -1.f, 0.0f, 0.0f, 0.0f, 0.8f,
		 0.6f, -1.f, 0.0f, 0.0f, 0.0f, 0.8f };

	inline static int plateauIndices[]{
	0, 1, 2,
	2, 3, 1
	};
	inline static std::vector<float> jetonsVertices = génèreJeton(0, 0, 0.1, nombrePointsDansJeton);
	inline static std::vector<int> jetonsIndices = génèreEBOJeton(nombrePointsDansJeton);

	inline static std::vector<glm::vec3>  positionsJetons = génererPositionsJetons(6,7, -0.53, 0.314, -0.84, 0.27);

	Shader shaders[2];
	inline static unsigned int VAOS[2] = { 0,0 };
	inline static unsigned int VBOS[2] = { 0,0 };
	inline static unsigned int EBOS[2] = { 0,0 };
};