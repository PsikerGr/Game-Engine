#pragma once
#include "../../Inputs/E_InputsType.h"
#include "../../Macro.h"

class ENGINE_DLL AbstractInputs abstract
{
public:
	AbstractInputs() = default;
	AbstractInputs(const AbstractInputs&) = delete;
	AbstractInputs(const AbstractInputs&&) = delete;
	virtual ~AbstractInputs() = default;

	static AbstractInputs* CreateInstance();
	bool IsPressed(E_KeyboardInputsType key);
	bool IsPressed();

	void SetKey(E_KeyboardInputsType key);
	const E_KeyboardInputsType GetKey() const;

protected:

	virtual bool CoreIsPressed(E_KeyboardInputsType key) = 0;
	virtual bool CoreIsPressed() = 0;

private:
	E_KeyboardInputsType _key;

};

