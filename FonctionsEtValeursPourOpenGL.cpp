#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "FonctionsEtValeursPourOpenGL.h"
#include <map>
#include "Shader.h"

 unsigned int SCR_WIDTH = 960;
 unsigned int SCR_HEIGHT = 540;
 float ratio = (float)SCR_HEIGHT / (float)SCR_WIDTH;
 glm::vec3 xyzSouris(0.0f, 0.0f, 0.0f);
 int nombrePointsDansJeton = 128;

std::vector<float> g�n�reJeton(float x, float y, float rayon, int nbPoints) {
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
std::vector<int> g�n�reEBOJeton(int numberOfPoints) {
    std::vector<int> indexes;
    for (int i = 2; i <= numberOfPoints; i++) {
        indexes.push_back(0);
        indexes.push_back(i - 1);
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
std::vector<glm::vec3> g�nererPositionsJetons(int nbLignes, int nbColonnes, float d�calageX, float espaceXJetons, float d�calageY, float espaceYJetons) {
    std::vector<glm::vec3> positions;
    for (int j = 0; j < nbLignes; j++) {
        for (int i = 0; i < nbColonnes; i++) {
            positions.push_back(glm::vec3(d�calageX + (i * espaceXJetons) * ratio, d�calageY + j * espaceYJetons, 0.0f));
        }
    }
    return positions;
}
std::map<char, Caract�re> g�n�reCaract�resPolice(const char* cheminFichierPolice) {
    std::map<char, Caract�re> caract�res;
    FT_Library ft;
    FT_Init_FreeType(&ft);
    FT_Face face;
    if(FT_New_Face(ft, cheminFichierPolice, 0, &face))
    std::cout << "ERROR::FREETYPE: Erreur lecture police" << std::endl;
    FT_Set_Pixel_Sizes(face, 0, 48);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++) {
        FT_Load_Char(face, c, FT_LOAD_RENDER);


        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Caract�re caract�re = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        caract�res.insert(std::pair<char, Caract�re>(c, caract�re));
    }
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
    return caract�res;
}
//Fonction tir�e du site learnOpenGL, par Joey de Vries :https://learnopengl.com
void RenduTexte(
    Shader& shader, 
    std::map<char, Caract�re> listeCaract�res, 
    unsigned int& VAO, 
    unsigned int& VBO, 
    std::string text, 
    float x, 
    float y, 
    float scale, 
    int color)
{
    shader.use();
    shader.setInt("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(VAO);

    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Caract�re ch = listeCaract�res[*c];

        float xpos = x + ch.bearing.x * scale;
        float ypos = y - (ch.taille.y - ch.bearing.y) * scale;

        float w = ch.taille.x * scale;
        float h = ch.taille.y * scale;
        float vertices[6][4] = {
            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos,     ypos,       0.0f, 1.0f },
            { xpos + w, ypos,       1.0f, 1.0f },

            { xpos,     ypos + h,   0.0f, 0.0f },
            { xpos + w, ypos,       1.0f, 1.0f },
            { xpos + w, ypos + h,   1.0f, 0.0f }
        };
        glBindTexture(GL_TEXTURE_2D, ch.ID);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.avance >> 6) * scale; 
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}