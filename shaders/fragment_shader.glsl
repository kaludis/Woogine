#version 120

varying vec2 f_texcoord;
uniform sampler2D sampler2d;

void main(void)
{
	vec2 flipped_texcoord = vec2(f_texcoord.x, 1.0 - f_texcoord.y);
	gl_FragColor = texture2D(sampler2d, flipped_texcoord);
}
