#version 330 core

uniform mat4 projection;

attribute vec4 texcoord;
varying vec2 f_texcoord;

void main()
{
	gl_Position = projection * vec4(texcoord.xy, 0.0f, 1.0f);
	f_texcoord = texcoord.zw;
}