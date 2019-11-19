#version 330 core
in vec4 vertex; // atributos de los vértices a procesar
in vec2 uv0;
uniform mat4 modelViewProjMat; // constante de programa
out vec2 vUv0; // out del vertex shader
out vec2 vUv1;
uniform float offset;

void main() {
	vUv0 = uv0;
	vUv1 = uv0;
	vUv1.s = vUv0.s - offset/15;
	gl_Position = modelViewProjMat * vertex; // obligatorio
}