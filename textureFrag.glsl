#version 330

in  vec2 texCoords;
in  vec3 vertNormal;
in  vec3 lightDir;


out vec4 fragColor;
uniform sampler2D myTexture0;  


void main() { 
	/// I could have passed these in as Uniforms but for simplicity, 
	/// I'll just define them here: specular, diffuse, ambient for the surface material 
	const vec4 ks = vec4(0.5, 0.2, 0.2, 0.0);
	const vec4 tint = vec4(0.2, 0.0, 0.0, 0.0);
	
	/// The reflect() method this most GPU expensive step in this proceedure
	/// The Blinn-Phong method is faster.   	
	vec3 reflection = normalize(reflect(-lightDir, vertNormal));
	float diff = max(dot(vertNormal, lightDir), 0.0);
	float spec = max(0.0, dot(vertNormal, reflection));
	if(diff != 0.0){
		spec = pow(spec,16.0);
	}
	vec4 kd = texture2D(myTexture0,texCoords);
	vec4 ka = 0.1 * kd;
	fragColor =  ka + ((diff + tint) * kd) + (spec * ks);

	//fragColor = texture2D(myTexture0,texCoords);
}
