#include "Application.h"

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

