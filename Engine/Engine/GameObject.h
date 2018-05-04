#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
#include "Component.h"
#include "../MathLib/Tools.h"
#include "Macro.h"
#include "Event\Event.hpp"
#include "Vec3d.h"

class AbstractEvent;

namespace resource
{
	class Component;

	class ENGINE_DLL GameObject
	{
	public:
		GameObject();
		GameObject(std::string name);

		GameObject(GameObject& gameObject);
		~GameObject();

		const std::unordered_map<std::string, Component*>& GetComponentMap() const;
		const std::unordered_map<std::string, GameObject*>& GetChildMap() const;

		bool IsParent();
		void SetIsParent(bool isParent);

		bool HaveParent();

		void MoveForward();
		void MoveBackward();
		void MoveLeft();
		void MoveRight();
		void Rotate();

		void AddComponent(Component* component, std::string name);
		void AddChild(GameObject* child);

		Event<void()> TransformChange;

		void OnParentTransformChange();
		Maths::Vec3d GetParentTransform(GameObject* gameObject);

		const std::string GetName() const;
		void SetName(std::string name);

		GameObject* GetParent() const;
		void SetParent(GameObject* parent);

		template<typename T>
		T* GetComponent();

		template<typename T>
		bool HaveComponentOfType();

	private:
		std::string _name = "";
		bool _isParent = false;
		GameObject* _parent;
		std::unordered_map<std::string, Component*> _componentMap;
		std::unordered_map<std::string, GameObject*> _childList;
	};

	template<typename T>
	T* GameObject::GetComponent()
	{
		T* component = nullptr;

		std::string className = typeid(T).name();
		std::string splittedClassName = className.substr(6); 
		std::vector<std::string> splitted = Maths::Tools::Split(splittedClassName, "::");
		std::unordered_map<std::string, Component*>::const_iterator objectComponent = _componentMap.find(splitted[2]);

		if (objectComponent == _componentMap.end())
			throw std::runtime_error("Component not found");
		else
			component = static_cast<T*>(objectComponent->second);

		return component;
	}


	template<typename T>
	bool GameObject::HaveComponentOfType()
	{
		std::string className = typeid(T).name();
		std::string splittedClassName = className.substr(6); 
		std::vector<std::string> splitted = Maths::Tools::Split(splittedClassName, "::");

		std::unordered_map<std::string, Component*>::const_iterator objectComponent = _componentMap.find(splitted[2]);

		if (objectComponent == _componentMap.end())
			return false;
		else
			return true;
	}
	

}

