#version 450 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec4 v_color;
layout (location = 2) in vec3 v_normal;
layout (location = 3) in float v_textureid;
layout (location = 4) in float v_idx;
layout (location = 5) in vec2 v_uv;

layout (std140, binding = 0) uniform ProjectionMatrix {
    mat4 model;
    mat4 view;
    mat4 projection;
};

out vec3 normal;
out vec4 color;
out float textureid;
out float idx;
out vec2 uv;

void main() {
	normal = mat3(transpose(inverse(model))) * v_normal;
	color = v_color;
	textureid = v_textureid;
	idx = v_idx;
	uv = v_uv;

	gl_Position = projection * view * model * vec4(v_position, 1.0);
}