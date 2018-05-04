#include "SFMLEvent.h"
#include "../../GameObject.h"
#include "../../Wrapper/SFML/AbstractRender.h"
#include "../Inputs/AbstractInputs.h"

SFMLEvent::SFMLEvent( sf::Window& window )
	: _win(window)
{
	for (size_t idx = 0; idx < E_EventType::Count; idx++)
	{
		_enumEventArray[idx] = static_cast<E_EventType>(idx);
	}
}

SFMLEvent::~SFMLEvent()
{
	delete _enumEventArray;
}

void SFMLEvent::CoreWindowEvent(component::Camera* camera)
{
	sf::Event event;
	while (_win.pollEvent(event))
	{		
		switch (event.type)
		{
		case sf::Event::Closed:
			renderer::AbstractRender::CloseWindow();
			break;
		case sf::Event::MouseMoved:
			camera->OnMouseMotion();
			break;
		case sf::Event::MouseButtonPressed:
			camera->OnMouseButton(event, true);
			break;
		case sf::Event::MouseButtonReleased:
			camera->OnMouseButton(event, false);
			break;
		case sf::Event::MouseWheelMoved:
			camera->OnMouseWheel(event);
			break;

		default:
			break;
		}
	}
}

sf::Event::EventType SFMLEvent::GetKey(const E_EventType key)
{
	return static_cast<sf::Event::EventType>(_enumEventArray[static_cast<uint8_t>(key)]);
}

sf::Event::EventType SFMLEvent::GetKey(const int key)
{
	return static_cast<sf::Event::EventType>(_enumEventArray[static_cast<uint8_t>(key)]);
}
