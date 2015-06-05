#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <map>
#include <string>
#include <vector>

class Shader
{
public:
    Shader();
    virtual ~Shader();
    
	void bind() const;
    
    bool attachVertexShader(const char *vertex_file_path, const std::string &strBefore = "");
    bool attachFragmentShader(const char *fragment_file_path, const std::string &strBefore = "");
    bool link();
    
	GLuint getProgram() const;
    
	GLint getUniformLocation(const std::string &name);
	GLint getAttribLocation(const std::string &name);
	GLint getLocation(const std::string &name);
    
    void setUniformMatrix3fv(const std::string &name,
                             GLsizei count,
                             GLboolean transpose,
							 const GLfloat *value);
    void setUniformMatrix4fv(const std::string &name,
                             GLsizei count,
                             GLboolean transpose,
							 const GLfloat *value);
	void setUniform1i(const std::string &name, GLint value);
	void setUniform1iv(const std::string &name, GLsizei count, const GLint *value);
	void setUniform1f(const std::string &name, GLfloat value);
	void setUniform2f(const std::string &name, GLfloat v0, GLfloat v1);
	void setUniform1fv(const std::string &name, GLsizei count, const GLfloat *value);
	void setUniform2fv(const std::string &name, GLsizei count, const GLfloat *value);
	void setUniform3fv(const std::string &name, GLsizei count, const GLfloat *value);
	void setUniform4fv(const std::string &name, GLsizei count, const GLfloat *value);
    
protected:
    bool locExists(const std::string &name) const;
    
    GLint Result;
    int InfoLogLength;
    
    std::vector<GLuint> vertexShaders;
    std::vector<GLuint> fragmentShaders;
    GLuint shader;
    
    std::map<std::string, GLint> locs;
    
    GLint previousShader;
};

#endif
