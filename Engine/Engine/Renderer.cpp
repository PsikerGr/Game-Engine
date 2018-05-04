#include "Renderer.h"
#include "Camera.h"

namespace core
{
	Renderer::Renderer()
	{
		_cam = new Camera();
	}

	Renderer::~Renderer()
	{
		delete _cam;
	}

	Camera* Renderer::GetCam()
	{
		return _cam;
	}
}