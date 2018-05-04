#pragma once
#include <vector>
#include <unordered_map>

#include "../Event/E_EventType.h"
#include "../Inputs/E_InputsType.h"
#include "../Event/Event.hpp"
#include "../Wrapper/Inputs/AbstractInputs.h"
#include "../Macro.h"

namespace resource
{
	class GameObject;
}

class ENGINE_DLL InputsManager
{
public:
	InputsManager() = default;
	InputsManager(const InputsManager&) = delete;
	InputsManager(const InputsManager&&) = delete;
	~InputsManager();

	void RegisterInput(Event<void()> eventType, E_KeyboardInputsType key);

	bool CheckIfKeyIsBinded(E_KeyboardInputsType key, std::pair<AbstractInputs*, Event<void()>> pair);
	void Check();
	const std::unordered_map<AbstractInputs*, Event<void()>> GetInputsMap() const;


	static void MoveForward(resource::GameObject* gameObject);

	static InputsManager& GetInstance();

private:
	
	std::unordered_map<AbstractInputs*, Event<void()>> _inputsMap;
	bool _isBind = false;
	

};

