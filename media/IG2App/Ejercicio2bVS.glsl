#version 330 core

in vec4 vertex; //datos de la malla:
in vec3 normal;
in vec2 uv0;
out vec3 vWvertex; //en world space
out vec3 vWnormal; //en world space
out vec2 vUv0;
uniform mat4model;
uniform mat4view;
uniform mat4projection;

void main() {
	vWvertex = vec3(model*vertex); // en world space
	vWnormal = mat3(transpose(inverse(model)))*normal;
	vUv0 = uv0;
	gl_Position = projection*view*vec4(vWvertex, 1.0);
}