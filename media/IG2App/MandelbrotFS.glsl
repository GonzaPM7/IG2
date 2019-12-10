#version 330 core
in vec2 vUv0; // out del vertex shader
in vec2 vUv1;
uniform vec4 InColor; // in Mandelbrot set
uniform vec4 OutColor1;
uniform vec4 OutColor2;
const int MaxIter = 500;
out vec4 fFragColor;
uniform sampler2D skyspace;
void main() { // cambio de cuadrante: zoom, traslación
	vec4 textureSky = texture(skyspace, vUv1);
	float Creal = vUv0.s - 1.5; // traslación ¿en el vertex shader?
	float Cimag = vUv0.t;
	float real = Creal; // Zr
	float imag = Cimag; // Zi
	float z2 = (real * real) + (imag * imag) ; // Z2
	int iter = 0;
	float tempreal = 0.0;
	while (iter < MaxIter && z2 < 4.0) {
		tempreal = real;
		real = (tempreal * tempreal) - (imag * imag) + Creal;
		imag = 2.0 * tempreal * imag + Cimag;
		z2 = (real * real) + (imag * imag);
		iter = iter + 1;
	}
	vec4 color = textureSky; // in Mandelbrot set
	if (z2 > 4.0)
		color = mix(OutColor1, OutColor2, fract(float(iter)* 0.04));
	fFragColor = color; // fract(float(iter)/ 25.0)
}