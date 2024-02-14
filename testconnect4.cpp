#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include <string>
#include <vector>
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Plateau.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
std::vector<float> drawCircle(float x, float y, float rayon, int nbPoints);
std::vector<int> generateEBOforCircle(int numberOfPoints);
float nearZero(float valeur);

std::vector<glm::vec3> positions;

Plateau* jeu = new Plateau("jean","seb");

const unsigned int SCR_WIDTH = 1920;
const unsigned int SCR_HEIGHT = 1080;
float ratio = (float)SCR_HEIGHT / (float)SCR_WIDTH;

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

float minInput = 0.0f;
float maxInput = 1.0f;
float deltaTime = 0.0f;
float lastFrame = 0.0f;


int main()
{
    for (int j = 0; j < 6; j++) {
        for (int i = 0; i < 7; i++) {
            positions.push_back(glm::vec3(-0.7 + (i * 0.3733f)*ratio + 0.07,-0.9 + j * 0.31 + 0.125, 0.0f));
        }
    }
    int GROSCON = 0;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Puissance 4", NULL, NULL);

    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    float plateauVertices[] = {
        -0.7f,  0.9f, 0.0f, 0.0f, 0.0f, 0.8f, 
         0.7f,  0.9f, 0.0f, 0.0f, 0.0f, 0.8f,
        -0.7f, -0.9f, 0.0f, 0.0f, 0.0f, 0.8f,
         0.7f, -0.9f, 0.0f, 0.0f, 0.0f, 0.8f }; 

    int plateauIndices[]{
        0, 1, 2,
        2, 3, 1

    };
    int numberOfPointsInCircle = 128;
    std::vector<float> cercleVertices = drawCircle(0, 0.0, 0.125, numberOfPointsInCircle);
    std::vector<int> cercleIndices = generateEBOforCircle(numberOfPointsInCircle);

    unsigned int VBOplateau, VAOplateau, EBOplateau,VBOjetons,VAOjetons,EBOjetons;
    glGenVertexArrays(1,&VAOplateau);
    glGenBuffers(1,&VBOplateau);
    glGenBuffers(1,&EBOplateau);
    glGenVertexArrays(1, &VAOjetons);
    glGenBuffers(1, &VBOjetons);
    glGenBuffers(1, &EBOjetons);

    glBindVertexArray(VAOplateau);

    glBindBuffer(GL_ARRAY_BUFFER, VBOplateau);
    glBufferData(GL_ARRAY_BUFFER, sizeof(plateauVertices), plateauVertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOplateau);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(plateauIndices), plateauIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOjetons);

    glBindBuffer(GL_ARRAY_BUFFER, VBOjetons);
    glBufferData(GL_ARRAY_BUFFER, ((cercleVertices).size()) * sizeof(float), &cercleVertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOjetons);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * (cercleIndices.size()), &cercleIndices[0], GL_STATIC_DRAW);



    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    Shader shaderPlateau("vertexPlateau.vs", "fragmentPlateau.fs");
    Shader shaderJetons("vertexJetons.vs", "fragmentJetons.fs");

    std::string J1, J2;
    std::cout << "--------------------------------------------------   Puissance 4   --------------------------------------------------\n\n";
    std::cout << "Entrez le nom du joueur 1 : ";
    std::cin >> J1;
    std::cout << "\nEntrez le nom du joueur 2 : ";
    std::cin >> J2;
    std::cout << "\n\n";

    Plateau* jeu = new Plateau(J1, J2);
    while (jeu->getActive()) {
        glClearColor(1.f, 1.f, 1.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        shaderPlateau.use();
        glBindVertexArray(VAOplateau);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        static int joueurActuel = 0;
        jeu->afficheJeu();
        jeu->afficheJoueurs();
        std::cout << "C'est au tour de " << jeu->getJoueur(joueurActuel) << ". Dans quelle colonne voulez vous jouer ? : ";
        int choix;
        do {
            std::cin >> choix;
        } while (!jeu->tour(choix, joueurActuel));
        //while (!glfwWindowShouldClose(window))
        {

            glClearColor(1.f, 1.f, 1.f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


            shaderPlateau.use();
            glBindVertexArray(VAOplateau);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            shaderJetons.use();
            glBindVertexArray(VAOjetons);
            for (int i = 0; i < jeu->tableau.size(); i++) {
                for (int j = 0; j < jeu->tableau[0].size(); j++) {
                    shaderJetons.setInt("couleur", int(jeu->tableau[jeu->tableau.size()-i-1][j]));
                    shaderJetons.setVec4("trans", positions[i * 7 + j].x, positions[i * 7 + j].y, positions[i * 7 + j].z, 0.0f);
                    glDrawElements(GL_TRIANGLES, cercleIndices.size(), GL_UNSIGNED_INT, 0);
                }
            }

            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        switch (jeu->jeuFini()) {
        case 0:
            break;
        case 1:
            std::cout << "\n\nVictoire de " << jeu->getJoueur(joueurActuel) << " !\n\n";
            jeu->afficheJeu();
            jeu->afficheJoueurs();
            jeu->toggleActive();
            break;
        case 2:
            std::cout << "\n\n Egalite !";
            jeu->toggleActive();
            break;
        }
        joueurActuel = !joueurActuel;
    }
    

    glDeleteVertexArrays(1, &VAOplateau);
    glDeleteBuffers(1, &VBOplateau);
    glDeleteBuffers(1, &EBOplateau);    
    glDeleteVertexArrays(1, &VAOjetons);
    glDeleteBuffers(1, &VBOjetons);
    glDeleteBuffers(1, &EBOjetons);

    glfwTerminate();
    return 0;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
std::vector<float> drawCircle(float x, float y, float rayon, int nbPoints) {
    float valCalcul = 360.0f / nbPoints;
    double PI = 3.14159265;

    std::vector<float> points;
    points.push_back(x);
    points.push_back(y);
    points.push_back(0.0f);
    for (int i = 1; i <= nbPoints; i++) {
        points.push_back(nearZero(static_cast<float>(x + ratio * (rayon * cos(glm::radians(valCalcul * i))))));
        points.push_back(nearZero(static_cast<float>(y + rayon * sin(glm::radians(valCalcul * i)))));
        points.push_back(0.0f);
    }
    return points;
}
std::vector<int> generateEBOforCircle(int numberOfPoints) {
    std::vector<int> indexes;
    for (int i = 2; i <= numberOfPoints; i++) {
        indexes.push_back(0);
        indexes.push_back(i-1);
        indexes.push_back(i);
    }
    indexes.push_back(0);
    indexes.push_back(numberOfPoints);
    indexes.push_back(1);
    return indexes;
}
float nearZero(float valeur) {
    if (valeur > 0) {
        if (valeur < 0.0001) {
            return 0;
        }
        else return valeur;
    }
    else {
        if (valeur > -0.0001) {
            return 0;
        }
        else return valeur;
    }
}