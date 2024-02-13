#version 330 core


out vec4 FragColor;
in vec3 SommetColor;
uniform int couleur;

void main(){
	switch(couleur){
		case(0):
		FragColor = vec4(1.,1.,1.,1.);
		break;
		case(1):
		FragColor = vec4(1.,1.,0.,1.);
		break;
		case(2):
		FragColor = vec4(1.,0.,0.,1.);
		break;
	}
}