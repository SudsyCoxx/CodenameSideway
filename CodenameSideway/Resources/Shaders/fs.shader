#version 410 core

out vec4 color;

in DATA {
	vec4 position;
	vec2 uv;
	vec4 color;
	float tid;
} fs_in;

uniform sampler2D textures[16];

void main() {
	color = fs_in.color;
	if (fs_in.tid > 0.0) {
		int tid = int(fs_in.tid - 0.5);
		color = texture2D(textures[tid], fs_in.uv);
	}
}