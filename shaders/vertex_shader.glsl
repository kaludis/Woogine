#version 120

uniform mat4 mvp;
attribute vec3 coord3d;
attribute vec2 texcoord;
varying vec2 f_texcoord;

void main(void)
{
	gl_Position = mvp * vec4(coord3d, 1.0f);
	f_texcoord = texcoord;
}
