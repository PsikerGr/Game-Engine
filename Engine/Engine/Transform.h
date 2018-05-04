#pragma once

#include "SFML\System.hpp"
#include "Vec3d.h"
#include "Mat4.h"
#include "Quat.h"
#include "Component.h"


namespace component
{

	class Transform : public resource::Component
	{

	public:
		Transform();
		Transform(Maths::Vec3d position, Maths::Vec3d rotation, Maths::Vec3d scale);
		~Transform();

		void SetPosition(const Maths::Vec3d position);
		const Maths::Vec3d GetPosition() const;

		void SetRotation(const Maths::Vec3d rotation);
		const Maths::Vec3d GetRotation() const;

		void SetScale(const Maths::Vec3d scale);
		const Maths::Vec3d GetScale() const;

		Maths::Mat4 GetWorld() const;
		const Maths::Mat4 GetLocalRotation() const;

		Maths::Mat4 TranslationMatrix(Maths::Vec3d translateVector);
		Maths::Mat4 ScaleMatrix(Maths::Vec3d scaleVector);
		Maths::Mat4 RotationMatrix(Maths::Vec3d rotationVector);
		Maths::Mat4 RotateYMatrix(float angle);
		Maths::Mat4 WorldMatrix();
		Maths::Mat4	Rotation() const;

	private:
		Maths::Vec3d _position;
		Maths::Vec3d _rotation;
		Maths::Vec3d _scale;
		Maths::Quat _localRotation; //= Maths::Quat::AngleToQuat(_rotation);
		Maths::Mat4 _world;
		Maths::Mat4 _scaleMatrix;
		Maths::Mat4 _rotationMatrix;
		Maths::Mat4 _translationMatrix;
	};

}