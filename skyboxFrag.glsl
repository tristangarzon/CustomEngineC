/// My fragment shader
#version 330


in  vec3 textureCoords;

out vec4 fragColor;
uniform samplerCube cubeTexture;  

void main() { 
	mat3 scale = mat3(vec3(-1.0,0.0,0.0),
					  vec3(0.0,1.0,0.0),
					  vec3(0.0,0.0,1.0));

	fragColor =  texture(cubeTexture, scale * textureCoords) ;
}

