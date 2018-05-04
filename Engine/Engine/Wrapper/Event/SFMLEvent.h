#pragma once
#include "AbstractEvent.h"
#include "../../Event/E_EventType.h"
#include "SFML\Window\Mouse.hpp"
#include "SFML\Window.hpp"

namespace resource
{
	class GameObject;
}

namespace component
{
	class Camera;
}


class SFMLEvent : public AbstractEvent
{
public:
	SFMLEvent( sf::Window& window );
	~SFMLEvent();

	void CoreWindowEvent(component::Camera* camera) override;


	sf::Event::EventType GetKey(const E_EventType key);
	sf::Event::EventType GetKey(const int key);



private:
	sf::Window& _win;

	E_EventType _enumEventArray[Count];

};

