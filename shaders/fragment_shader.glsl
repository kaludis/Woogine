#version 330 core

varying vec2 f_texcoord;
uniform sampler2D sampler2d;

void main(void)
{
	vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
	vec4 texel = texture2D(sampler2d, flipped_texcoord);
	if (texel.a < 0.5) discard;
	gl_FragColor = texel;
}
