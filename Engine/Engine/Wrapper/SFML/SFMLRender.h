#pragma once
#include "AbstractRender.h"
#include "SFML\Window.hpp"
#include "SFML\Window\Mouse.hpp"
#include "../../Event/E_EventType.h"


namespace renderer
{
	class SFMLRender : public AbstractRender
	{
	public:
		SFMLRender();
		SFMLRender(SFMLRender&&) = delete;
		~SFMLRender() = default;


	protected:

		void CoreCreateWindow(int width, int height, const char* windowTitle) override;
		void CoreRun() override;
		void CoreWindowEvent(component::Camera* camera) override;
		void CoreCloseWindow() override;

		


		sf::Event::EventType GetIntKey(const int key);
		sf::Event::EventType GetKey(const E_EventType key);
		E_EventType GetEventKey(const int key);

		Maths::Vec2d CoreGetMousePos() override;

	private:

		sf::Window _win;
		float _deltaTime;
		float _lastFrame;

		E_EventType _enumEventArray[Count];
		E_EventType _event_type;
		sf::Event::EventType event_type;
		sf::Event::EventType _sfEnumEventArray[sf::Event::EventType::Count];


	};


}