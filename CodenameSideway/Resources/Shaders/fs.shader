#version 410 core

out vec4 color;

in DATA
{
	vec4 position;
	vec2 uv;
	vec4 color;
	float tid;
} fs_in;

void main()
{
    color = fs_in.color;
}
