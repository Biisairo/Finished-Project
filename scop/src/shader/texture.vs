#version 330 core
// opengl ver 3.3

layout(location = 0) in vec4 VERTEX;
layout(location = 1) in vec2 VERTEXTEXTURE;
layout(location = 2) in vec3 VERTEXNORMAL;
layout(location = 3) in vec3 VERTEXCOLOR;

out vec2 UV;
out vec3 NORMAL;
out vec4 VERTEXPOS;
out vec3 TMPCOLOR;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

void main(){

	mat4 MVP = PROJECTION * VIEW * MODEL;
	gl_Position = MVP * VERTEX;

	
	UV = VERTEXTEXTURE; // testure cordinate
	NORMAL = vec3(MODEL * vec4(VERTEXNORMAL, 0)); // normal vec
	VERTEXPOS = MODEL * VERTEX; // world 좌표계에서 점의 실제 위치
	TMPCOLOR = VERTEXCOLOR;
}

