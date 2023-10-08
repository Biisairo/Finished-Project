#version 400 core

layout(location = 0) in vec3 VERTEX;
layout(location = 1) in vec3 PARENT;
layout(location = 2) in vec3 CHILD;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;
uniform vec3 POSITION;
uniform bool ISCOR;

out float DIST;

mat4 rotateVector(vec3 source, vec3 target) {
    // 벡터를 회전하기 전에 정규화
    source = normalize(source);
    target = normalize(target);

    // 벡터의 내적을 계산하여 각도 구하기
    float dotProduct = dot(source, target);
    float angle = acos(clamp(dotProduct, -1.0, 1.0));

    // 회전 축 계산
    vec3 rotationAxis = cross(source, target);

    // 회전 행렬 생성
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    float oneMinusCosTheta = 1.0 - cosTheta;

    mat4 rotationMatrix = mat4(
        cosTheta + rotationAxis.x * rotationAxis.x * oneMinusCosTheta,
        rotationAxis.x * rotationAxis.y * oneMinusCosTheta - rotationAxis.z * sinTheta,
        rotationAxis.x * rotationAxis.z * oneMinusCosTheta + rotationAxis.y * sinTheta,
        0.0,

        rotationAxis.y * rotationAxis.x * oneMinusCosTheta + rotationAxis.z * sinTheta,
        cosTheta + rotationAxis.y * rotationAxis.y * oneMinusCosTheta,
        rotationAxis.y * rotationAxis.z * oneMinusCosTheta - rotationAxis.x * sinTheta,
        0.0,

        rotationAxis.z * rotationAxis.x * oneMinusCosTheta - rotationAxis.y * sinTheta,
        rotationAxis.z * rotationAxis.y * oneMinusCosTheta + rotationAxis.x * sinTheta,
        cosTheta + rotationAxis.z * rotationAxis.z * oneMinusCosTheta,
        0.0,

        0.0, 0.0, 0.0, 1.0
    );

    return rotationMatrix;
}


void main(){

	if (ISCOR) {
		mat4 MVP = PROJECTION * VIEW * MODEL;
		gl_Position = MVP * vec4(VERTEX, 1);
	} else {
		mat4 MVP = PROJECTION * VIEW * MODEL;

		vec3 V = PARENT - CHILD;

		vec3 scale = vec3(length(V), 0.5, 0.5);
		vec3 trans = (PARENT + CHILD) / 2;
        mat4 rotate = rotateVector(vec3(1, 0, 0), V);

		gl_Position = MVP * (rotate * vec4(scale * VERTEX, 1) + vec4(trans, 0));

        // gl_Position = MVP * vec4((rotateVectorToMatch(vec3(1, 0, 0), vec3(0, 1, 1)) * VERTEX), 1);
	}
	
	vec3 tmp = POSITION - vec3(VERTEX);
	DIST = dot(tmp, tmp);
}

