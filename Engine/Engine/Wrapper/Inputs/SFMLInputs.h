#pragma once

#include "AbstractInputs.h"
#include "SFML\Window\Keyboard.hpp"
#include "SFML\Window\Mouse.hpp"

class SFMLInputs : public AbstractInputs
{
public:
	SFMLInputs();
	~SFMLInputs();

	sf::Keyboard::Key GetKey(const E_KeyboardInputsType key);
	sf::Keyboard::Key GetKey(const int key);

protected:
	bool CoreIsPressed(E_KeyboardInputsType key) override;
	bool CoreIsPressed() override;

private:

	E_KeyboardInputsType _keyboadInputsArray[E_KeyboardInputsType::KeyCount];

};

