#version 450 core

in vec3 normal;
// in vec4 color;
in vec3 frag_pos;
in vec3 view_pos;

uniform vec4 light_color;
uniform vec3 light_dir;
uniform vec3 light_pos;

void main() {
	// blinn-phong

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
	float specular = 0.0;

	if (diffuse != 0.0) {
		vec3 view_dir = normalize(view_pos - frag_pos);

		vec3 halfway = normalize(view_dir + light_dir);
		specular = pow(max(dot(normal, halfway), 0.0), 8) * specular_lighting;
	}

	result = color * light_color * (diffuse + ambient + specular);

	gl_FragData[0] = result;
}