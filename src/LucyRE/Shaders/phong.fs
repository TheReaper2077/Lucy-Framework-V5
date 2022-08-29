#version 450 core

in vec3 normal;
// in vec4 color;
in vec3 frag_pos;

uniform vec4 light_color;
uniform vec3 light_dir;
uniform vec3 light_pos;

void main() {
	float ambient = 0.2;
	float specular_lighting = 0.2;

	vec4 result;
	vec4 color = vec4(normal, 1);
	
	if (normal.x < 0)
		color.x = -normal.x;
	if (normal.y < 0)
		color.y = -normal.y;
	if (normal.z < 0)
		color.z = -normal.z;

	vec3 light_dir = normalize(light_pos - frag_pos);
	float diffuse = max(dot(light_dir, normal), 0.0);

	result = color * light_color * (diffuse + ambient);
	// result = color * diffuse;

	gl_FragData[0] = result;
}