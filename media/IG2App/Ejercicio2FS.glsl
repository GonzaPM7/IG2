#version 330 core
uniform sampler2D textura0; // tipo sampler2D para texturas 2D
uniform sampler2D textura1;
uniform vec4 InColor;
uniform vec4 OutColor;
uniform float FB; // blending factor
uniform float intLuzAmb; // luz ambiente
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader

void main() {

	vec3 color0 = vec3(texture(textura0, vUv0)); // acceso a texel
	vec3 color1 = vec3(texture(textura1, vUv0)); // configuración
	vec3 color = color0 * color1 * FB * intLuzAmb;
	if(gl_FrontFacing){
        fFragColor = OutColor * vec4(color, 1.0) * FB;
    }else{
        fFragColor = InColor * vec4(color, 1.0) * FB;
    }
    if(color1.x > 0.6){
        discard;
    }
}