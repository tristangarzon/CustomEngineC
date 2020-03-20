
#include "shader.h"
#include "GL/glew.h"
#include <fstream>
#include <string.h>
#include <stdarg.h>

using namespace GAME;

/// Vertex and Fragment Shader filenames,
/// Next, the number of attributes (in pairs)
/// The pair consists of (int)attribute index, (char*) attribute name
Shader::Shader(const char *vsFilename, const char *fsFilename, int numAttributes,...) {
	char* name;
	int index;
	readCompileAttach(vsFilename,fsFilename);
	
	va_list args;
	va_start(args, numAttributes);
	
	for(int i = 0; i < numAttributes; ++i){
		index = va_arg(args, int);
		name = va_arg(args, char*);
		printf("Binding attribute %s at %d\n",name, index);
		glBindAttribLocation(shader, index, name);
	}
	va_end(args);	

	link();

	exploreUniforms();
}


void Shader::readCompileAttach(const char *vsFilename, const char *fsFilename){
    GLint status;
	shader = 0;
	vertShader = 0;
	fragShader = 0;
	try { 		
		const char* vsText = readTextFile(vsFilename);
		const char* fsText = readTextFile(fsFilename);
		if (vsText == NULL || fsText == NULL) return;

		/// GL_VERTEX_SHADER and GL_FRAGMENT_SHADER are defined in glew.h
		vertShader = glCreateShader(GL_VERTEX_SHADER);
		fragShader = glCreateShader(GL_FRAGMENT_SHADER);
		/// Check for errors
		if (vertShader == 0 || fragShader == 0) {
			std::string errorMsg("Can't create a new shader");
			throw errorMsg;
		}
    
		glShaderSource(vertShader, 1, &vsText, 0);   
		glShaderSource(fragShader, 1, &fsText, 0);
    
		glCompileShader(vertShader);
		/// Check for errors
		glGetShaderiv(vertShader, GL_COMPILE_STATUS, &status);
			if(status == 0) {
				GLsizei errorLogSize = 0;
				GLsizei titleLength;
				std::string errorLog ="VERT:\n";
				titleLength = errorLog.length();
				glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &errorLogSize);
				errorLog.resize( titleLength + errorLogSize );
				glGetShaderInfoLog(vertShader, errorLogSize, &errorLogSize, &errorLog[titleLength]);
				throw errorLog;
			}

		glCompileShader(fragShader);
		/// Check for errors
		glGetShaderiv(fragShader, GL_COMPILE_STATUS, &status);
			if(status == 0) {
				GLsizei errorLogSize = 0;
				GLsizei titleLength;
				std::string errorLog ="FRAG:\n";
				titleLength = errorLog.length();
				glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &errorLogSize);
				errorLog.resize( titleLength + errorLogSize );
				glGetShaderInfoLog(fragShader, errorLogSize, &errorLogSize, &errorLog[titleLength]);
				throw errorLog;
			}
    
		shader = glCreateProgram();
		glAttachShader(shader, fragShader);
		glAttachShader(shader, vertShader);
		if(vsText) delete[] vsText;
		if(fsText) delete[] fsText;

	}catch(std::string error){
		printf("%s\n",&error[0]);
	}
	 
}

void Shader::link(){
	GLint status;
	try{
			glLinkProgram(shader);
			/// Check for errors
			glGetProgramiv(shader, GL_LINK_STATUS, &status);
			if(status == 0) {
				GLsizei errorLogSize = 0;
				std::string errorLog;
				glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &errorLogSize);
				errorLog.resize(errorLogSize);
				glGetProgramInfoLog(shader, errorLogSize, &errorLogSize, &errorLog[0]);
				throw errorLog;
			}
		
	}catch(std::string error){
		printf("ERROR:%s\n",&error[0]);
	}

}

Shader::~Shader() {
	glDetachShader(shader, fragShader);
	glDetachShader(shader, vertShader);  
	glDeleteShader(fragShader);
	glDeleteShader(vertShader);
	glDeleteProgram(shader);
}

unsigned int Shader::getProgram() {
	return shader;
}

/// Read from a specified file and return a char array from the heap 
/// The memory must be deleted within this class. It may not be the best way 
/// to do this but it is all private and I did delete it! SSF
char* Shader::readTextFile(const char *filename){
	char* buffer = NULL;
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {								/// Open the file
        file.seekg(0, std::ios::end);					/// goto the end of the file
        int bufferSize = (int) file.tellg();			/// Get the length of the file
		if(bufferSize == 0) {							/// If zero, bad file
			std::string errorMsg("Can't read shader file: ");
			std::string str2(filename);
			errorMsg += str2;
			throw errorMsg;								/// Bail out
		}
		buffer = new char[(int)(bufferSize + 1)];		/// Need to NULL terminate the array
        file.seekg(0, std::ios::beg);
        file.read(buffer, bufferSize);
		buffer[bufferSize] = '\0';						/// Add the NULL
		file.close();
    }else { 
		std::string errorMsg("Can't open shader file: ");
		printf("ERROR:%s:%s\n",filename,&errorMsg[0]);
	}
	return buffer;
}

void Shader::exploreUniforms(){
	int count;
	GLsizei actualLen;
	GLint size;
	GLenum type;
	char *name;
	int maxUniLength;
	unsigned int loc;

	glGetProgramiv(shader, GL_ACTIVE_UNIFORMS, &count);
	printf("There are %d active Uniforms\n",count);

	/// get the length of the longest named uniform 
	glGetProgramiv(shader, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniLength);

	/// Create a little buffer to hold the uniform's name - old C memory call just for fun 
	name = (char *)malloc(sizeof(char) * maxUniLength);

	
	for (int i = 0; i < count; ++i) {
		/// Get the name of the ith uniform
		glGetActiveUniform(shader, i, maxUniLength, &actualLen, &size, &type, name);
		/// Get the (unsigned int) loc for this uniform
		loc = glGetUniformLocation(shader, name);

		printf("\"%s\" loc:%d\n",name,loc);
	}
	free(name);
}