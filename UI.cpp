#include "UI.h"
#include "FonctionsEtValeursPourOpenGL.h"

UI::UI(const char* cheminFichierPolice) : 
    shaders{ Shader("vertexBoutons.vs","fragmentBoutons.fs"),
	Shader("vertexJetons.vs","fragmentJetons.fs"),
	Shader("vertexTexte.vs","fragmentTexte.fs") },
    caractèresTexte{ génèreCaractèresPolice(cheminFichierPolice)} {

	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(SCR_WIDTH), 0.0f, static_cast<float>(SCR_HEIGHT));
	shaders[2].use();
	glUniformMatrix4fv(glGetUniformLocation(shaders[2].ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glGenVertexArrays(3, VAOS);
	glGenBuffers(3, VBOS);
	glGenBuffers(2, EBOS);


    glBindVertexArray(VAOS[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOS[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(boutonVertices), boutonVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOS[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(boutonIndices), boutonIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(VAOS[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOS[1]);
    glBufferData(GL_ARRAY_BUFFER, ((petitJetonUIVertices).size()) * sizeof(float), &petitJetonUIVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOS[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * (jetonIndices.size()), &jetonIndices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    glBindVertexArray(VAOS[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBOS[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
}
void UI::afficherMenu() {

    shaders[0].use();
    shaders[0].setVec4("couleur", 0., 0., 0.8, 1.);
    shaders[0].setVec4("decalage", 0.4, 0., 0., 0.);
    glBindVertexArray(VAOS[0]);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    shaders[0].setVec4("couleur", 0., 0., 0.8, 1.);
    shaders[0].setVec4("decalage", -0.4, 0., 0., 0.);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    RenduTexte(shaders[2], caractèresTexte, VAOS[2], VBOS[2], "Un joueur", 230.0f, 260.0f, 0.6f, 1);
    RenduTexte(shaders[2], caractèresTexte, VAOS[2], VBOS[2], "Deux joueurs", 590.0f, 260.0f, 0.6f, 2);
    RenduTexte(shaders[2], caractèresTexte, VAOS[2], VBOS[2], "Puissance 4 ", 350.0f, 400.0f, 1.f, 3);
}
void UI::afficherUI(std::string J1, std::string J2) {
    if (couleurUI) {
        RenduTexte(shaders[2], caractèresTexte, VAOS[2], VBOS[2], J2 + " :", 20.0f, 50.0f, 0.6f, 1);
        RenduTexte(shaders[2], caractèresTexte, VAOS[2], VBOS[2], J1 + " :", 20.0f, 20.0f, 0.6f, 2);

        shaders[1].use();
        glBindVertexArray(VAOS[1]);

        shaders[1].setInt("couleur", 1);
        shaders[1].setVec4("trans", -0.7, -0.75, 1.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, jetonIndices.size(), GL_UNSIGNED_INT, 0);

        shaders[1].setInt("couleur", 2);
        shaders[1].setVec4("trans", -0.7, -0.89, 1.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, jetonIndices.size(), GL_UNSIGNED_INT, 0);


    }
    else {
        RenduTexte(shaders[2], caractèresTexte, VAOS[2], VBOS[2], J1 + " :", 20.0f, 50.0f, 0.6f, 2);
        RenduTexte(shaders[2], caractèresTexte, VAOS[2], VBOS[2], J2 + " :", 20.0f, 20.0f, 0.6f, 1);

        shaders[1].use();
        glBindVertexArray(VAOS[1]);

        shaders[1].setInt("couleur", 2);
        shaders[1].setVec4("trans", -0.7, -0.75, 1.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, jetonIndices.size(), GL_UNSIGNED_INT, 0);

        shaders[1].setInt("couleur", 1);
        shaders[1].setVec4("trans", -0.7, -0.89, 1.0f, 0.0f);
        glDrawElements(GL_TRIANGLES, jetonIndices.size(), GL_UNSIGNED_INT, 0);
    }
}
UI::~UI() {
    glDeleteVertexArrays(3, VAOS);
    glDeleteBuffers(3, VBOS);
    glDeleteBuffers(2, EBOS);
}
bool UI::getCouleurUI() const {
    return couleurUI;
}
std::vector<int> UI::getJetonIndices() const {
    return jetonIndices;
}
void UI::setCouleurUI(bool val) {
    couleurUI = val;
}