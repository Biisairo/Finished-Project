#version 400 core

out vec4 color;

uniform vec3 COLOR;
uniform bool GEO;

void main(){
	if (GEO) {
		color = vec4(COLOR, 0.5);
	} else
		color = vec4(COLOR, 1);
}