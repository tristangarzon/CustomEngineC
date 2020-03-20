/// My vertex shader
#version 330
in  vec4 vVertex;
out vec3 textureCoords;
uniform mat4 projectionMatrix;
uniform mat4 modelViewMatrix;
void main() {
	textureCoords = vec3(vVertex);
	gl_Position =  projectionMatrix * modelViewMatrix * vVertex;
}
