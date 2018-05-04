#include <memory>
#include <mutex>
#include <iostream>

#include "InputsManager.h"
#include "../Wrapper/Inputs/AbstractInputs.h"
#include "../Transform.h"
#include "../GameObject.h"

InputsManager::~InputsManager()
{
	_inputsMap.clear();
}

void InputsManager::RegisterInput(Event<void()> eventType, E_KeyboardInputsType key)
{
	for (auto ievent : _inputsMap)
	{
		if (CheckIfKeyIsBinded(key, ievent))
		{
			ievent.second = eventType;
			std::cout << "Already bind" << std::endl;
			_isBind = true;
		}
		else
			_isBind = false;
	}

	if (!_isBind)
	{
		AbstractInputs* input = AbstractInputs::CreateInstance();
		input->SetKey(key);
		_inputsMap.insert(std::make_pair(input, eventType));
	}
}

bool InputsManager::CheckIfKeyIsBinded(E_KeyboardInputsType key, std::pair<AbstractInputs*, Event<void()>> pair)
{
	if (pair.first->GetKey() == key)
		return true;
	else
		return false;
}

void InputsManager::Check()
{
	for (auto ievent : _inputsMap)
	{
		if (ievent.first->IsPressed())
		{
			ievent.second.Invoke();
		}
	}
}

const std::unordered_map<AbstractInputs*, Event<void()>> InputsManager::GetInputsMap() const
{
	return _inputsMap;
}

void InputsManager::MoveForward(resource::GameObject * gameObject)
{
	component::Transform* objectTransform = gameObject->GetComponent<component::Transform>();

	objectTransform->SetPosition(((Maths::Vec3d(0.0f, 0.0f, -1.0f)).CrossProduct(Maths::Vec3d(0.0f, 1.0f, 0.0f))).Normalized() * 5.f);
}

InputsManager& InputsManager::GetInstance()
{
	static std::unique_ptr<InputsManager> instance;
	static std::once_flag once_flag;

	std::call_once(once_flag, [](void) 
	{ 
		instance.reset(new InputsManager());
	});

	return *instance.get();
}
