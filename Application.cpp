#include "Application.h"
#include "Mat4.h"

void Application::error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

// to quit when ESC is pressed
void Application::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

// destroy opengl buffers
Application::~Application()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &uvBuffer);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &vertexArray);

	glfwDestroyWindow(window);
	glfwTerminate();
}

bool Application::initialize(int argc, char *argv[])
{
	if (!(initGLFW() && initGLEW() && initShader() && initContent()))
		return false;

	printf("Initialization successful.\n");
	return true;
}

// for window creation and context handling
bool Application::initGLFW()
{
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		printf("Failed to initialize glfw!\n");
		return false;
	}

	if (!(window = glfwCreateWindow(INIT_WIDTH, INIT_HEIGHT, "Simple example", NULL, NULL)))
	{
		printf("Failed to create window!\n");
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	glfwSetKeyCallback(window, key_callback);
	
	printf("GLFW initialized.\n");
	return true;
}

// for extensions
bool Application::initGLEW()
{
	if (glewInit() != GLEW_OK)
	{
		printf("Failed to initialize glew!\n");
		return false;
	}

	printf("GLEW initialized.\n");
	return true;
}

// shader setup
bool Application::initShader()
{
	// link
	if (!(shader.attachVertexShader("basic.vert") &&
		shader.attachFragmentShader("basic.frag") &&
		shader.link()))
	{
		printf("Failed to link shader!\n");
		return false;
	}

	// retrieve uniform locations
	if ((shader.getUniformLocation("u_ModelViewProjectionMatrix")) == -1)
	{
		printf("Failed to locate u_ModelViewProjectionMatrix!");
		return false;
	}

	if ((shader.getUniformLocation("u_Time")) == -1)
	{
		printf("Failed to locate u_Time!");
		return false;
	}

	if ((shader.getUniformLocation("u_Resolution")) == -1)
	{
		printf("Failed to locate u_Resolution!");
		return false;
	}

	printf("Shader initialized.\n");
	return true;
}

// vbo setup
bool Application::initContent()
{
	//vertices
	if (!vertices.empty())
		vertices.clear();

	vertices.push_back(Vec3f(-1.0f, -1.0f, 0.0f));
	vertices.push_back(Vec3f(1.0f, -1.0f, 0.0f));
	vertices.push_back(Vec3f(1.0f, 1.0f, 0.0f));
	vertices.push_back(Vec3f(-1.0f, 1.0f, 0.0f));
	for (int i = 0, len = vertices.size(); i < len; ++i) // transform to 0-1
		vertices[i] = vertices[i] * 0.5f + 0.5f;

	// texture coordinates
	if (!texCoords.empty())
		texCoords.clear();

	for (int i = 0, len = vertices.size(); i < len; ++i)
		texCoords.push_back(Vec2f(vertices[i].x, vertices[i].y));

	//indices
	if (!indices.empty())
		indices.clear();

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(2);
	indices.push_back(3);

	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	//generate the buffers
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec3f) * vertices.size(), &vertices.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2f) * texCoords.size(), &texCoords.front(), GL_STATIC_DRAW);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices.front(), GL_STATIC_DRAW);

	printf("Buffers initialized.\n");
	return true;
}

// the app is worth running if the initialization returns true
void Application::run()
{
	while (!glfwWindowShouldClose(window))
	{
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		float ratio = width / (float)height;
		
		// set viewport accordingly
		glViewport(0, 0, width, height);

		//clear it out
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		const Mat4f u_ModelViewProjectionMatrix = Mat4f::ortho(0.0f, 1.0f, 0.0f, 1.0f, -1.0f, 1.0f);

		shader.bind();
		shader.setUniformMatrix4fv("u_ModelViewProjectionMatrix", 1, GL_FALSE, u_ModelViewProjectionMatrix.m);
		shader.setUniform1f("u_Time", glfwGetTime());
		shader.setUniform2f("u_Resolution", width, height);
		//printf("%f\n", glfwGetTime());

		// vertex attribute
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		// texture coordinate attribute
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glDisableVertexAttribArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}