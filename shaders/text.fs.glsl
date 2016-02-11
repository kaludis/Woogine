#version 330 core

varying vec2 f_texcoord;

uniform sampler2D glyph;
uniform vec3 textcolor;

void main()
{
	vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(glyph, f_texcoord).r);
	gl_FragColor = vec4(textcolor, 1.0f) * sampled;
}