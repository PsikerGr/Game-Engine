#include <memory>
#include <mutex>


#ifdef SFML
#include "SFMLRender.h"
typedef renderer::SFMLRender InstanciableRender;

#endif // SFML

namespace renderer
{
	AbstractRender::~AbstractRender()
	{
		delete _events;
		_events = nullptr;
	}

	void AbstractRender::CreateRenderWindow(int width, int height, const char* windowTitle)
	{
		GetInstance().CoreCreateWindow(width, height, windowTitle);
	}

	void AbstractRender::Run()
	{
		GetInstance().CoreRun();
	}

	void AbstractRender::WindowEvent(component::Camera * camera)
	{
		GetInstance().CoreWindowEvent(camera);
	}

	void AbstractRender::CloseWindow()
	{
		
		GetInstance().CoreCloseWindow();
		
	}

	Maths::Vec2d AbstractRender::GetMousePos()
	{
		return GetInstance().CoreGetMousePos();
	}

	AbstractRender & AbstractRender::GetInstance()
	{
		static std::unique_ptr<AbstractRender> instance;
		static std::once_flag once_flag;

		std::call_once(once_flag, [](void)
		{
			instance.reset(new InstanciableRender());
		});

		return *instance.get();
	}
}