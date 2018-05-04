#include <iostream>

#include "AbstractInputs.h"

#ifdef SFML
#include "SFMLInputs.h"
typedef SFMLInputs InstanciableInputs;
#endif // SFML

AbstractInputs* AbstractInputs::CreateInstance()
{
	AbstractInputs * result = new InstanciableInputs();
	return result;
}

bool AbstractInputs::IsPressed(E_KeyboardInputsType key)
{
	return CoreIsPressed(key);
}

bool AbstractInputs::IsPressed()
{
	return CoreIsPressed(_key);
}

void AbstractInputs::SetKey(E_KeyboardInputsType key)
{
	_key = key;
}

const E_KeyboardInputsType AbstractInputs::GetKey() const
{
	return _key;
}
