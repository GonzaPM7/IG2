#version 330 core // 
in vec2 vUv0;
uniform sampler2D RTT0; // textura con la escena
out vec4 fFragColor;
// weight vector for luminance in sRGB
const vec3 WsRGB = vec3(0.2125, 0.7154, 0.0721);
void main() {
    vec4 frag = gl_FragCoord;
    vec4 sceneColor = texture(RTT0, vUv0);
    float lum;
    if(int(frag.y) % 6 < 3) 
        fFragColor = sceneColor;
    else {
        lum = dot(vec3(sceneColor), vec3(0.5, 0.5, 0.5));
        fFragColor = vec4(lum, lum, lum, sceneColor.a);//* vec4(RTT0,1.0);
    }
	
}