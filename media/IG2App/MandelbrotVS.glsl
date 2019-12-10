#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
out vec2 vUv0;
out vec2 vUv1;
uniform float offset;
void main() {
	vUv1 = uv0;
	//vUv0 = uv0; // cuadrante [0, 1] x [0, 1] -> [-0.5, 0.5] x [-0.5, 0.5]
	vUv0.s = uv0.s - 0.5; // traslación [0, 1] -> [-0.5, 0.5]
	vUv0.t = uv0.t - 0.5; // traslación [0, 1] -> [-0.5, 0.5]
	vUv1.s = vUv0.s - offset / 15;
	gl_Position = modelViewProjMat * vertex; // N.D.C.
}