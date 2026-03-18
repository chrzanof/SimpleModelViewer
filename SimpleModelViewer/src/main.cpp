#include "Application.h"

//TODO: use size callback somewhere. Probably should move this definition to Application.h
static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	WindowSpecs windowSpecs {
		.width{ 1500 },
		.height{ 1000 },
		.title{"Model Viewer" }
	};

	ApplicationSpecs appSpecs {
		windowSpecs,
		"shaders/vert.glsl",
		"shaders/frag.glsl"
	};

	Application application(appSpecs);
	application.Run();

	return 0;
}

static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

