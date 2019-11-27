#version 330 core
uniform sampler2D textura0; // tipo sampler2D para texturas 2D
uniform sampler2D textura1;
uniform vec4 InColor;
uniform vec4 OutColor;
in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader

uniform sampler2D materialColors;
in vec3 vWvertex; //en world space
in vec3 vWnormal; //en world space

uniform vec3 viewPos; //posición de la cámara en world space

uniform vec3 lightPosition; //en world space
uniform vec3 lightDiffuse;

uniform vec3 materialDiffuse; //datos del material

void main() {
	vec3 color0 = vec3(texture(textura0, vUv0)); // acceso a texel
	vec3 color1 = vec3(texture(textura1, vUv0)); // configuración
	
	if(color1.x > 0.6){
        discard;
    }
	
	//diffuse
	vec3 norm = normalize(vWnormal);
	
	if(!gl_FrontFacing)
        norm = -norm;
		
	
	vec3 lightDir = lightPosition;
	float diff = max(dot(norm,lightDir),0.0);
	vec3 diffuse = diff*lightDiffuse*materialDiffuse;
	
	if(gl_FrontFacing){
		fFragColor = OutColor * vec4(color0, 1.0) * vec4(diffuse,1.0);
    }else{
		fFragColor = InColor * vec4(diffuse,1.0);
    }
}