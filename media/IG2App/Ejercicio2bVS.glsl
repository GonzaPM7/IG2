#version 330 core

in vec4 vertex; //datos de la malla:
in vec3 normal;
in vec2 uv0;
out vec3 vWvertex; //en world space
out vec3 vWnormal; //en world space
out vec2 vUv0;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 normalMat;

void main() {
	vUv0 = uv0;
	vWvertex = vec3(model*vertex); // en world space
	vWnormal = mat3(normalMat)*normal;
	
	gl_Position = projection*view*vec4(vWvertex, 1.0);
}