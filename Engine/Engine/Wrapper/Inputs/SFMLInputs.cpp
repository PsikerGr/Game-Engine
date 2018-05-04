#include <iostream>
#include "SFMLInputs.h"

SFMLInputs::SFMLInputs()
	: AbstractInputs()
{
	for (int idx = 0; idx < E_KeyboardInputsType::KeyCount; idx++)
	{
		_keyboadInputsArray[idx] = static_cast<E_KeyboardInputsType>(idx);
	}
}

SFMLInputs::~SFMLInputs()
{
	delete _keyboadInputsArray;
}


bool SFMLInputs::CoreIsPressed(E_KeyboardInputsType key)
{
	sf::Keyboard sfKey;
	if (sfKey.isKeyPressed(GetKey(key)))
	{
		return true;
	}
	else
		return false;
}

bool SFMLInputs::CoreIsPressed()
{
	return false;
}

sf::Keyboard::Key SFMLInputs::GetKey(const E_KeyboardInputsType key)
{
	return static_cast<sf::Keyboard::Key>(_keyboadInputsArray[static_cast<int8_t>(key)]);
}

sf::Keyboard::Key SFMLInputs::GetKey(const int key)
{
	return static_cast<sf::Keyboard::Key>(_keyboadInputsArray[static_cast<int8_t>(key)]);
}
