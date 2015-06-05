#include "Application.h"
#include <chrono>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Mat4.h"
#include "Shader.h"
#include <stdio.h>
#include "Vec2.h"
#include "Vec3.h"

int main(int argc, char *argv[])
{
	if (Application::getInstance().initialize(argc, argv))
		Application::getInstance().run();

	return 0;
}