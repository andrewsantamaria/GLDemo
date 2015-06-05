#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
#include "Singleton.h"
#include "Vec2.h"
#include "Vec3.h"

class Application : public Singleton<Application>
{
public:
	~Application();

	bool initialize(int argc, char *argv[]);
	void run();

private:
	static void error_callback(int error, const char* description);
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

	bool initGLFW(); 
	bool initGLEW(); 
	bool initShader(); 
	bool initContent();

	GLFWwindow* window;
	Shader shader;
	std::vector<Vec3f> vertices;
	std::vector<Vec2f> texCoords;
	std::vector<GLuint> indices;
	GLuint vertexArray, VBO, uvBuffer, IBO;
};


#define INIT_WIDTH 640
#define INIT_HEIGHT 480

#endif