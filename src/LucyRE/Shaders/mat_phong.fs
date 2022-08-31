#version 450 core

in vec3 normal;
in vec4 color;
in vec3 frag_pos;
in vec3 view_pos;

struct Material {
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec4 color;
	vec4 pos;

	float ambient;
	float diffuse;
};

uniform Light light;
uniform Material material;

void main() {
	vec3 light_dir;
	if (light.pos.w == 1.0)
		light_dir = normalize(light_dir.xyz - frag_pos);
	else
		light_dir = light.pos.xyz;

	vec3 view_dir = normalize(view_pos - frag_pos);
	vec3 halfway = normalize(view_dir + light_dir);

	float diffuse = max(dot(normal, light_dir), 0.0);

	vec3 result = material.ambient * light.ambient;
	result += diffuse * material.diffuse * light.diffuse;
	int f;

	if (dot(n,l) > 0.0)
		result += pow(max(0,dot(n,h)),gl_FrontMaterial.shininess) * gl_FrontMaterial.specular*gl_LightSource[0].specular;
}