#pragma once


class Camera;
class Mesh;
namespace core
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();
		void Draw();
		Camera* GetCam();

	private:
		Camera *_cam;

	};
}