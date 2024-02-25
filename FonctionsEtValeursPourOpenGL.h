#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <map>
#include <ft2build.h>
#include "Shader.h"
#include FT_FREETYPE_H

extern unsigned int SCR_WIDTH;
extern unsigned int SCR_HEIGHT;
extern float ratio;
extern int nombrePointsDansJeton;
extern glm::vec3 xyzSouris;

struct Caract�re {
    unsigned int ID;
    glm::ivec2   taille;     
    glm::ivec2   bearing;  
    unsigned int avance;  
};

float nearZero(float valeur);
std::vector<float> g�n�reJeton(float x, float y, float rayon, int nbPoints);
std::vector<int> g�n�reEBOJeton(int numberOfPoints);
std::vector<glm::vec3> g�nererPositionsJetons(int lignes, int colonnes, float d�calageX, float espaceXJetons, float d�calageY, float espaceYJetons);
std::map<char, Caract�re> g�n�reCaract�resPolice(const char* cheminFichierPolice);

void RenduTexte(
    Shader& s,
    std::map<char, Caract�re> listeCaract�res,
    unsigned int& VAO,
    unsigned int& VBO,
    std::string text,
    float x,
    float y,
    float scale,
    int color);

void redimensionnementEcran(GLFWwindow* window, int width, int height);
void retourClavier(GLFWwindow* window, int key, int scancode, int action, int mods);
void retourClicSouris(GLFWwindow* window, int button, int action, int mods);
void posSouris(GLFWwindow* window, double x, double y);
