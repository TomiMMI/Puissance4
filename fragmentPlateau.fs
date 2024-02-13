#version 330 core


out vec4 FragColor;
in vec3 SommetColor;

void main(){
	FragColor = vec4(SommetColor,1.0f);
}