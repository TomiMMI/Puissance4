#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "PlateauGraphique.h"
#include "Shader.h"
#include <string>
#include <vector>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Plateau.h"
#include "FonctionsEtValeursPourOpenGL.h"

PlateauGraphique::PlateauGraphique() : Plateau(), UIJeu{ UI("fonts/COMIC.ttf") },
shaders{ Shader("vertexPlateau.vs", "fragmentPlateau.fs"), Shader("vertexJetons.vs", "fragmentJetons.fs") } {
    glGenVertexArrays(2, VAOS);
	glGenBuffers(2, VBOS);
	glGenBuffers(2, EBOS);

    glBindVertexArray(VAOS[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plateauVertices), plateauVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOS[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(plateauIndices), plateauIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOS[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOS[1]);
    glBufferData(GL_ARRAY_BUFFER, ((jetonsVertices).size()) * sizeof(float), &jetonsVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOS[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * (jetonsIndices.size()), &jetonsIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
void PlateauGraphique::afficherTableauGraphique() {
    shaders[0].use();
    glBindVertexArray(VAOS[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    shaders[1].use();
    glBindVertexArray(VAOS[1]);
    for (int i = 0; i < tableau.size(); i++) {
        for (int j = 0; j < tableau[0].size(); j++) {
            shaders[1].setInt("couleur", int(tableau[tableau.size() - i - 1][j]));
            shaders[1].setVec4("trans", positionsJetons[i * 7 + j].x, positionsJetons[i * 7 + j].y, positionsJetons[i * 7 + j].z, 0.0f);
            glDrawElements(GL_TRIANGLES, jetonsIndices.size(), GL_UNSIGNED_INT, 0);
        }
    }
}
PlateauGraphique::~PlateauGraphique() {
    glDeleteVertexArrays(2, VAOS);
    glDeleteBuffers(2, VBOS);
    glDeleteBuffers(2, EBOS);
}
Shader PlateauGraphique::getShader(int num) const{
    return shaders[num];
}
bool PlateauGraphique::dansLePlateau() const{
    if (xyzSouris.x >= 0.4 * (SCR_WIDTH / 2) && xyzSouris.x <= 1.6 * (SCR_WIDTH / 2)) {
        return true;
    }
    return false;

}