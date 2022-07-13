#version 450 core

in vec3 normal;
in vec4 color;
in vec2 uv;
in vec3 uvw;
in float textureid;


void main() {
	vec4 result;
	
	result = vec4(normal, 1);

	gl_FragColor = result;
}