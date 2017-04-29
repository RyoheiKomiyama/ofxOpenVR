#version 150

uniform mat4 matrix;

in vec4 position;
in vec3 v3ColorIn;

out vec4 v4Color;

void main() {
	v4Color.xyz = v3ColorIn; v4Color.a = 1.0;
	gl_Position = matrix * position;
}
