#version 410 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 uv;
layout(location = 3) in float tid;

uniform mat4 pr_matrix;

out DATA {
	vec4 position;
	vec2 uv;
	vec4 color;
	float tid;
} vs_out;

void main() {
	gl_Position = pr_matrix * vec4(position, 1);
	vs_out.position = vec4(position, 1);
	vs_out.color = vec4(color, 1);
	vs_out.uv = uv;
	vs_out.tid = tid;
}