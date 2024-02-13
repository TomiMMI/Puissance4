#pragma once
#ifndef SHADER_H    // Évite d'inclure plusieurs fois ce fichier
#define SHADER_H

#include <glad/glad.h> // inclure glad pour disposer de tout en-tête OpenGL 

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    // the program ID
    unsigned int ID;

    // le constructeur lit et construit le shader
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    // Activation du shader
    void use();
    // fonctions utiles pour l'uniform
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec4(const std::string& name, float value, float value2, float value3, float value4) const;
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;
};

#endif