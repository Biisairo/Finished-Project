#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
}; // 물체의 반사도

struct Light {
	vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}; // 실제 빛

in vec2 UV;
in vec3 NORMAL;
in vec4 VERTEXPOS;
in vec3 TMPCOLOR;

out vec3 color;

uniform sampler2D TEXTURE; // texture

uniform Material material;
uniform Light light;

uniform vec3 VIEWPOS; // view position

uniform float TransitionTexture; // transition

void main(){
	vec3 norm = normalize(NORMAL);
	vec3 lightDir = normalize(light.position - vec3(VERTEXPOS));

	// object color
	vec3 objectColor = texture( TEXTURE, UV ).rgb; // 실제 물체의 색

	// ambient
	vec3 ambient = light.ambient * material.ambient;

	// diffusion
	float diff = max(dot(norm, lightDir), 0.0); // 빛의 방향과 노말을 내적해 얼마나 마주보고있는지 확인, 음수이면 아래로 내려간 것이므로 패스
	// float diff = max(dot(norm, lightDir), 0); // 빛의 방향과 노말을 내적해 얼마나 마주보고있는지 확인, 음수이면 아래로 내려간 것이므로 패스
	vec3 diffuse = light.diffuse * diff * material.diffuse; // 광원과 각도의 곱, 광원이 어두워짐

	// Specular
	vec3 viewDir = normalize(VIEWPOS - vec3(VERTEXPOS));
	vec3 reflectDir = reflect(-lightDir, norm);
	// float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = light.specular * spec * material.specular;

	// result
	vec3 colorAdd = TMPCOLOR * 0.005;
	vec3 finalObjectColor = objectColor * TransitionTexture;
	vec3 finalColorAdd = colorAdd * (1 - TransitionTexture);
	color = (ambient + diffuse + specular) * (finalObjectColor + finalColorAdd); // 자연광 + 광원 = 들어오는 빛, 여기에 물체의 색을 곱함
}