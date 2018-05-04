#pragma once
#include "Vec2d.h"
#include "../../Camera.h"


namespace renderer
{
	class AbstractRender
	{
	public:
		
		virtual ~AbstractRender();

		static void CreateRenderWindow(int width, int height, const char* windowTitle);
		static void Run();
		static void WindowEvent(component::Camera* camera);
		static void CloseWindow();

		static Maths::Vec2d GetMousePos();

	protected:
		AbstractRender() = default;
		AbstractRender(const AbstractRender&) = delete;
		AbstractRender(const AbstractRender&&) = delete;

		virtual void CoreCreateWindow(int width, int height, const char* windowTitle) = 0;
		virtual void CoreRun() = 0;
		virtual void CoreWindowEvent(component::Camera* camera) = 0;
		virtual void CoreCloseWindow() = 0;

		virtual Maths::Vec2d CoreGetMousePos() = 0;

		AbstractEvent* _events;

	private:
		static AbstractRender& GetInstance();
	};




}