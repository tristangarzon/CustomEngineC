#version 330
in  vec4 vVertex;
in  vec4 vNormal;
in  vec4 vColor;
out vec3 vertNormal;
out vec3 lightDir;
 
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform vec3 lightPos;

void main() {

	vertNormal = normalMatrix * vNormal.xyz; /// Rotate the normal to the correct orientation 
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	vec4 eyePos = modelViewMatrix * vVertex; /// Create the eye vector 
	lightDir = normalize(lightPos - eyePos.xyz); /// Create the light direction 

	gl_Position =  projectionMatrix * modelViewMatrix * vVertex; 
}
