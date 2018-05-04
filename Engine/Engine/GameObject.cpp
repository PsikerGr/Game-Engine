#include "GameObject.h"
#include "Transform.h"
#include "Wrapper\Event\AbstractEvent.h"
#include "Wrapper\RHI.h"

Maths::Vec3d rotateVector(0.f, 0.f, 0.f);

namespace resource
{

	GameObject::GameObject()
	{
		AddComponent(new component::Transform(), "Transform");
		TransformChange.Bind<resource::GameObject, &resource::GameObject::OnParentTransformChange>(this);
	}

	GameObject::GameObject(std::string name)
	:_name(name)
	{
		AddComponent(new component::Transform(), "Transform");
	}



	GameObject::GameObject(GameObject & gameObject)
	: _name(gameObject._name), _isParent(gameObject._isParent), _componentMap(gameObject._componentMap), _childList(gameObject._childList)
	{
	}


	GameObject::~GameObject()
	{
		delete _parent;
		_parent = nullptr;
		_componentMap.clear();
		_childList.clear();
		_name.erase();
	}

	const std::unordered_map<std::string, Component*>& GameObject::GetComponentMap() const
	{
		return _componentMap;
	}

	const std::unordered_map<std::string, GameObject*>& GameObject::GetChildMap() const
	{
		return _childList;
	}

	bool GameObject::IsParent()
	{
		return _isParent;
	}

	void GameObject::MoveForward()
	{
		component::Transform* objectTransform = GetComponent<component::Transform>();


		Maths::Vec3d translation = GetParentTransform(this);

		translation.z += 1.f;

		objectTransform->TranslationMatrix(translation);
		Maths::Mat4 worldMatrix = objectTransform->WorldMatrix();

		TransformChange.Invoke();
	}

	void GameObject::AddComponent(Component* component, std::string name)
	{
		_componentMap.insert(std::make_pair(name, component));
	}

	void GameObject::AddChild(GameObject * child)
	{
		child->SetParent(this);
		_childList.insert(std::make_pair(child->GetName(), child));
	}

	const std::string GameObject::GetName() const
	{
		return _name;
	}
	void GameObject::SetName(std::string name)
	{
		_name = name;
	}

	GameObject* GameObject::GetParent() const
	{
		return _parent;
	}

	void GameObject::SetParent(GameObject* parent)
	{
		_parent = parent;
	}
	
	void GameObject::SetIsParent(bool isParent)
	{
		_isParent = isParent;
	}

	bool GameObject::HaveParent()
	{
		if (_parent != nullptr)
			return true;
		else
			return false;
	}

	Maths::Vec3d GameObject::GetParentTransform(GameObject* gameObject)
	{
		if (gameObject->HaveParent())
			return GetParentTransform(gameObject->GetParent()) + gameObject->GetComponent<component::Transform>()->GetPosition();
		else
			return gameObject->GetComponent<component::Transform>()->GetPosition();
	}

	void GameObject::OnParentTransformChange()
	{
		component::Transform* transform = GetComponent<component::Transform>();
		transform->WorldMatrix();
	}

	void GameObject::Rotate()
	{
		component::Transform* transform = GetComponent<component::Transform>();
		
		rotateVector.y += 1.f;
		rotateVector.z += 1.f;
		rotateVector.x += 1.f;

		transform->RotationMatrix(rotateVector);

		transform->WorldMatrix();
	}
}
