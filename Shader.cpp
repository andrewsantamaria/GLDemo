#include "Shader.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Shader::Shader() {}

Shader::~Shader()
{
	glDeleteProgram(shader);
}

void Shader::bind() const
{
    glUseProgram(shader);
}

bool Shader::attachVertexShader(const char *vertex_file_path, const std::string &strBefore)
{
    vertexShaders.push_back(glCreateShader(GL_VERTEX_SHADER));
    GLuint VertexShaderID = vertexShaders.back();
    
    // Read the Vertex Shader code from the file
	std::string VertexShaderCode = strBefore + "\n";
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";

		while(getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;

		VertexShaderStream.close();
	}
	else
	{
		cout << "Failed to open " << vertex_file_path << "!\n";
		getchar();
		return false;
	}
    
    // Compile Vertex Shader
    cout << "Compiling vertex shader: " << vertex_file_path << endl;
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
	glCompileShader(VertexShaderID);
    
	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        cout << &VertexShaderErrorMessage[0] << endl;

        return false;
	}
    
    return true;
}

bool Shader::attachFragmentShader(const char *fragment_file_path, const std::string &strBefore)
{
    fragmentShaders.push_back(glCreateShader(GL_FRAGMENT_SHADER));
    GLuint FragmentShaderID = fragmentShaders.back();
    
    std::string FragmentShaderCode = strBefore + "\n";
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		std::string Line = "";

		while(getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;

		FragmentShaderStream.close();
	}
    
    // Compile Fragment Shader
    cout << "Compiling fragment shader: " << fragment_file_path << endl;
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
	glCompileShader(FragmentShaderID);
    
	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);

        cout << &FragmentShaderErrorMessage[0] << endl;
	}
    
    return true;
}

bool Shader::link()
{
    // Link the program
	cout << "Linking program...\n";
    shader = glCreateProgram();
    
    for (std::vector<GLuint>::iterator i = vertexShaders.begin(); i != vertexShaders.end(); ++i)
        glAttachShader(shader, *i);
    
    for (std::vector<GLuint>::iterator i = fragmentShaders.begin(); i != fragmentShaders.end(); ++i)
        glAttachShader(shader, *i);
    
	glLinkProgram(shader);
    
	// Check the program
	glGetProgramiv(shader, GL_LINK_STATUS, &Result);
	glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(shader, InfoLogLength, NULL, &ProgramErrorMessage[0]);

        cout << &ProgramErrorMessage[0] << endl;
        return false;
	}
    
    for (std::vector<GLuint>::iterator i = vertexShaders.begin(); i != vertexShaders.end(); ++i)
        glDeleteShader(*i);
    
    for (std::vector<GLuint>::iterator i = fragmentShaders.begin(); i != fragmentShaders.end(); ++i)
        glDeleteShader(*i);
    
    return true;
}

GLuint Shader::getProgram() const { return shader; }

// Get locations and store in a map so they can be retrieved by their name
GLint Shader::getUniformLocation(const std::string &name) 
{
    return locs[name] = glGetUniformLocation(shader, name.c_str());
}

GLint Shader::getAttribLocation(const std::string &name) 
{
    return locs[name] = glGetAttribLocation(shader, name.c_str());
}

GLint Shader::getLocation(const std::string &name)
{
    return locs[name];
}

// Set uniforms by string
void Shader::setUniform1iv(const std::string &name, GLsizei count, const GLint *value) 
{
	glUniform1iv(locs[name], count, value);
}

void Shader::setUniformMatrix3fv(const std::string &name,
                                 GLsizei count,
                                 GLboolean transpose,
								 const GLfloat *value) 
{
	glUniformMatrix3fv(locs[name], count, transpose, value);
}

void Shader::setUniformMatrix4fv(const std::string &name,
                                 GLsizei count,
                                 GLboolean transpose,
								 const GLfloat *value) 
{
	glUniformMatrix4fv(locs[name], count, transpose, value);
}

void Shader::setUniform1i(const std::string &name, GLint value) 
{
	glUniform1i(locs[name], value);
}

void Shader::setUniform1f(const std::string &name, GLfloat value) 
{
	glUniform1f(locs[name], value);
}

void Shader::setUniform2f(const std::string &name, GLfloat v0, GLfloat v1) 
{
	glUniform2f(locs[name], v0, v1);
}

void Shader::setUniform1fv(const std::string &name, GLsizei count, const GLfloat *value) 
{
	glUniform1fv(locs[name], count, value);
}

void Shader::setUniform2fv(const std::string &name, GLsizei count, const GLfloat *value) 
{
	glUniform2fv(locs[name], count, value);
}

void Shader::setUniform3fv(const std::string &name, GLsizei count, const GLfloat *value) 
{
	glUniform3fv(locs[name], count, value);
}

void Shader::setUniform4fv(const std::string &name, GLsizei count, const GLfloat *value) 
{
	glUniform4fv(locs[name], count, value);
}

bool Shader::locExists(const std::string &name) const
{
    return locs.count(name);
}
