#include <iostream>

#include "SFMLRender.h"
#include "SFML\System\Clock.hpp"
#include "../../Render/Rendering.h"
#include "../RHI.h"
#include "../../Event/Event.hpp"
#include "../Event/SFMLEvent.h"


namespace renderer
{
	SFMLRender::SFMLRender()
	: _deltaTime(0.f), _lastFrame(0.f)
	{
		_events = new SFMLEvent(_win);

		for (size_t idx = 0; idx < E_EventType::Count; idx++)
		{
			_enumEventArray[idx] = static_cast<E_EventType>(idx);
		}
	}
	
	void SFMLRender::CoreCreateWindow(int width, int height, const char* windowTitle)
	{
		sf::ContextSettings context(24, 8, 2, 3, 3);
		_win.create(sf::VideoMode(width, height), windowTitle, 7U, context);
		RHI::Initialize();
		Rendering::GetInstance().CoreInitializeRender(width, height);
	}

	void SFMLRender::CoreRun()
	{

		while (_win.isOpen())
		{
			CoreWindowEvent(RHI::GetCamera());

			_win.setActive(true);

			Rendering::GetInstance().CoreRender(_deltaTime);

			_win.display();
		}
	}

	void SFMLRender::CoreWindowEvent(component::Camera * camera)
	{
		_events->WindowEvent(camera);
	}

	void SFMLRender::CoreCloseWindow()
	{
		_win.close();
	}



	sf::Event::EventType SFMLRender::GetIntKey(const int key)
	{
		return static_cast<sf::Event::EventType>(_enumEventArray[static_cast<uint8_t>(key)]);
	}

	sf::Event::EventType SFMLRender::GetKey(const E_EventType key)
	{
		return static_cast<sf::Event::EventType>(_enumEventArray[static_cast<uint8_t>(key)]);
	}

	E_EventType SFMLRender::GetEventKey(const int key)
	{
		return static_cast<E_EventType>(_enumEventArray[static_cast<uint8_t>(key)]);
	}



	Maths::Vec2d SFMLRender::CoreGetMousePos()
	{
		Maths::Vec2d mousePos = { 0, 0 };
		mousePos.x = sf::Mouse::getPosition(_win).x;
		mousePos.y = sf::Mouse::getPosition(_win).y;
		return mousePos;
	}
}