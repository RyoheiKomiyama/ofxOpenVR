#version 150

uniform sampler2DRect baseTex;
in vec2 texCoordVarying;
out vec4 fragColor;
vec2 texcoord0 = texCoordVarying;

void main() {
	vec2 tx = texcoord0;
	tx.y = 256.0 - tx.y;
	vec4 image = texture(baseTex, tx);
	fragColor = image;
}