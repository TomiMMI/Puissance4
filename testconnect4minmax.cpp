#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <string>
#include <vector>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Plateau.h"
#include <ft2build.h>
#include "FonctionsEtValeursPourOpenGL.h"
#include "PlateauGraphique.h"
#include "UI.h"
#include FT_FREETYPE_H

int dansLeBouton();
bool afficherJeton = false;
PlateauGraphique* jeu;
int choixFinPgrm = 0;

int main()
{
    {glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); }

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Puissance 4", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Erreur fenêtre GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, redimensionnementEcran);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(window, posSouris);
    glfwSetKeyCallback(window, retourClavier);
    glfwSetMouseButtonCallback(window, retourClicSouris);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Erreur GLAD" << std::endl;
        return -1;}

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


restart:
    choixFinPgrm = 0;
    jeu = new PlateauGraphique();

    while (!jeu->getMode()) {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        jeu->UIJeu.afficherMenu();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    if (jeu->getMode() == 1) {
        jeu->setJoueurs("J1", "ORDI");
        jeu->setIsTourOrdi(jeu->getJoueur(jeu->joueurActuel) == "ORDI");
        std::cout << jeu->getIsTourOrdi();
        jeu->UIJeu.setCouleurUI(jeu->getIsTourOrdi());
    }
    else{
        jeu->setJoueurs("J1", "J2");
        jeu->UIJeu.setCouleurUI(rand() % 2);
    }
    while (jeu->getActive())
    {
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        jeu->UIJeu.afficherUI(jeu->getJoueur(0), jeu->getJoueur(1));
        jeu->afficherTableauGraphique();
        if (!jeu->getIsTourOrdi() && afficherJeton && !jeu->jeuFini()) {
            jeu->getShader(1).setInt("couleur", (-jeu->joueurActuel + 2));
            jeu->getShader(1).setVec4("trans", (float(xyzSouris.x) / (SCR_WIDTH / 2)) - 1, 0.9, 0.0f, 0.0f);
            glDrawElements(GL_TRIANGLES, jeu->UIJeu.getJetonIndices().size(), GL_UNSIGNED_INT, 0);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
        switch (jeu->jeuFini()) {
        case 0:
            break;
        case 1:
            std::cout << "\n\nVictoire de " << jeu->getJoueur(jeu->joueurActuel) << " !\n\n";
            jeu->toggleActive();
            break;

        case 2:
            std::cout << "\n\n Egalite !\n\n";
            jeu->toggleActive();
            break;
        }
        if (jeu->getIsTourOrdi()) {
            jeu->tourOrdi();
            jeu->setIsTourOrdi(false);
    }
    }
    jeu->afficheJeu();
    jeu->afficheJoueurs();

    glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    jeu->afficherTableauGraphique();
    glfwSwapBuffers(window);

    std::cout << "\n\nAppuyez sur 'F' pour quitter\n\nAppuyez sur 'R' pour rejouer\n\n";
    while (!choixFinPgrm) {
        glfwWaitEvents();
    }
    if (choixFinPgrm == 2) {
        goto restart;
    }
    delete jeu;
    glfwTerminate();
    return 0;

}
int dansLeBouton() {
    if (xyzSouris.x >= 0.3 * (SCR_WIDTH / 2) && xyzSouris.x <= 0.9 * (SCR_WIDTH / 2)
        && xyzSouris.y >= 0.9 * (SCR_HEIGHT / 2) && xyzSouris.y <= 1.1 * (SCR_HEIGHT / 2)) {
        return 1;
    }
    if (xyzSouris.x >= 1.1 * (SCR_WIDTH / 2) && xyzSouris.x <= 1.7 * (SCR_WIDTH / 2)
        && xyzSouris.y >= 0.9 * (SCR_HEIGHT / 2) && xyzSouris.y <= 1.1 * (SCR_HEIGHT / 2)) {
        return 2;
    }
    return 0;
}
void redimensionnementEcran(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    SCR_WIDTH = width;
    SCR_HEIGHT = height;
}
void posSouris(GLFWwindow* window, double x, double y) {
    xyzSouris.x = (float)x;
    xyzSouris.y = (float)y;
    if (jeu->dansLePlateau()) {
        afficherJeton = true;
    }
    else {
        afficherJeton = false;
    }

}
void retourClavier(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (!jeu->getActive()) {
        if (key == GLFW_KEY_F && action == GLFW_PRESS)
            choixFinPgrm = 1;
        if (key == GLFW_KEY_R && action == GLFW_PRESS) {
            choixFinPgrm = 2;
        }
    }
}
void retourClicSouris(GLFWwindow* window, int button, int action, int mods)
{
    if (jeu->getMode() && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && jeu->getActive()) {
        if (jeu->dansLePlateau()) {
            int colonne = xyzSouris.x / (int(((0.6 + 0.035) * SCR_WIDTH) / 7)) - 1;
            if (!jeu->getIsTourOrdi() && jeu->tour(colonne)) {
                if (jeu->getMode() == 1) {
                    jeu->setIsTourOrdi(true);
                }
                jeu->afficheJeu();
                jeu->afficheJoueurs();
            }
        }
    }
    if (!jeu->getMode() && button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        jeu->setMode(dansLeBouton());
    }

}