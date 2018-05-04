#include <iostream>

#include "Transform.h"
#include "Tools.h"
#include "LogDebug\ILogger.h"

namespace component
{

	Transform::Transform()
		: Component("Transform"), _position(0.0f, 0.0f, 0.0f), _rotation(0.0f, 0.0f, 0.0f), _scale(1.0f, 1.0f, 1.0f)
	{
		core::ILogger::LogMessage("Create Transform at : ", __FILE__, __LINE__);
		_translationMatrix.Identity();
		_rotationMatrix.Identity();
		_scaleMatrix.Identity();
		_world.Identity();
	}

	Transform::Transform(Maths::Vec3d position, Maths::Vec3d rotation, Maths::Vec3d scale)
		: Component("Transform"), _position(position), _rotation(rotation), _scale(scale)
	{
		core::ILogger::LogMessage("Create Transform at : ", __FILE__, __LINE__);
	}

	Transform::~Transform()
	{
		core::ILogger::LogMessage("Delete Transform at : ", __FILE__, __LINE__);
	}

	Maths::Mat4 Transform::TranslationMatrix(Maths::Vec3d translateVector)
	{
		_position = translateVector;

		_translationMatrix.Translate(Maths::Vec3d(_position.x, _position.y, _position.z));



		return _translationMatrix;
	}

	Maths::Mat4 Transform::ScaleMatrix(Maths::Vec3d scaleVector)
	{
		_scale = scaleVector;
		
		_scaleMatrix.Scale(Maths::Vec3d(_scale.x, _scale.y, _scale.z));

		return _scaleMatrix;
	}


	Maths::Mat4 Transform::RotationMatrix(Maths::Vec3d rotationVector)
	{
		//Maths::Quat secondQuat = Maths::Quat::AngleToQuat(rotationVector);

		///*Maths::Quat rotationQuat = Maths::Quat::AngleToQuat(_rotation);



		//Maths::Quat finalQuat = secondQuat * rotationQuat;*/


		////Maths::Quat secondRotation(1, Maths::Tools::DegToRad(rotationVector.x), Maths::Tools::DegToRad(rotationVector.y), Maths::Tools::DegToRad (rotationVector.z));
		//Maths::Quat first = Maths::Quat::MatrixToQuat(_rotationMatrix);
	
		//Maths::Quat finalRotation = secondQuat * first;

		////Maths::Quat slerpedRotation = Maths::Quat::Slerp(first, secondQuat, 10.f);

		//_rotationMatrix = Maths::Mat4::QuatToMatrix(finalRotation);
		float cosP = cos(rotationVector.x);
		float sinP = sin(rotationVector.x);
		Maths::Mat4 rotX{ cosP, -sinP, 0, 0,
						sinP, cosP, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 };

		float cosT = cos(rotationVector.y);
		float sinT = sin(rotationVector.y);
		Maths::Mat4 rotY{ cosT, 0, sinT, 0,
						0, 1, 0, 0,
						-sinT, 0, cosT, 0,
						0, 0, 0, 1 };

		float cosD = cos(rotationVector.z);
		float sinD = sin(rotationVector.z);
		Maths::Mat4 rotZ{ 1, 0, 0, 0,
						0, cosD, -sinD, 0,
						0, sinD, cosD, 0,
						0, 0, 0, 1 };

		_rotationMatrix = _rotationMatrix * rotX * rotY * rotZ;
		//_rotationMatrix = Rotation()


		/*if (rotationVector.y > 360.f)
		{
			rotationVector.y = 0.f;

			std::cout << "Out of bound" << std::endl;
		}*/

		return _rotationMatrix;
	}

	Maths::Mat4 Transform::RotateYMatrix(float angle)
	{
		Maths::Quat _rotationQuat = Maths::Quat::AngleToQuat(_rotation);

		_rotationMatrix = Maths::Mat4::QuatToMatrix(_rotationQuat);
				

		return _rotationMatrix;
	}

	Maths::Mat4 Transform::WorldMatrix()
	{
		_world =  _translationMatrix *_scaleMatrix * _rotationMatrix;
		//_world.LogMatrix();
		return _world;
	}
	
	void Transform::SetPosition(const Maths::Vec3d position)
	{
		_position = position;
	}

	const Maths::Vec3d Transform::GetPosition() const
	{
		return _position;
	}

	void Transform::SetRotation(const Maths::Vec3d rotation)
	{
		_rotation = rotation;
	}

	const Maths::Vec3d Transform::GetRotation() const
	{
		return _rotation;
	}

	void Transform::SetScale(const Maths::Vec3d scale)
	{
		_scale = scale;
	}
	
	const Maths::Vec3d Transform::GetScale() const
	{
		return _scale;
	}

	Maths::Mat4 Transform::GetWorld() const
	{
		return _world;
	}

	const Maths::Mat4 Transform::GetLocalRotation() const
	{
		return Maths::Mat4::QuatToMatrix(_localRotation);
	}

	Maths::Mat4	Transform::Rotation() const
	{
		Maths::Mat4 vertex = Maths::Mat4();

		// Line 0
		vertex.m[0] = _localRotation.w * _localRotation.w
			+ _localRotation.x * _localRotation.x
			- _localRotation.y * _localRotation.y
			- _localRotation.z * _localRotation.z;
		vertex.m[1] = 2 * _localRotation.x * _localRotation.y - 2 * _localRotation.w * _localRotation.z;
		vertex.m[2] = 2 * _localRotation.w * _localRotation.y + 2 * _localRotation.x * _localRotation.z;
		vertex.m[3] = _position.x;

		// Line 1
		vertex.m[4] = 2 * _localRotation.w * _localRotation.z + 2 * _localRotation.x * _localRotation.y;
		vertex.m[5] = _localRotation.w * _localRotation.w
			- _localRotation.x * _localRotation.x
			+ _localRotation.y * _localRotation.y
			- _localRotation.z * _localRotation.z;
		vertex.m[6] = 2 * _localRotation.y * _localRotation.z - 2 * _localRotation.w * _localRotation.x;
		vertex.m[7] = _position.y;

		// Line 2
		vertex.m[8] = 2 * _localRotation.x * _localRotation.z - 2 * _localRotation.w * _localRotation.y;
		vertex.m[9] = 2 * _localRotation.w * _localRotation.x + 2 * _localRotation.y * _localRotation.z;
		vertex.m[10] = _localRotation.w * _localRotation.w
			- _localRotation.x * _localRotation.x
			- _localRotation.y * _localRotation.y
			+ _localRotation.z * _localRotation.z;
		vertex.m[11] = _position.z;

		// Line 3
		vertex.m[12] = 0.0f;
		vertex.m[13] = 0.0f;
		vertex.m[14] = 0.0f;
		vertex.m[15] = 1.0f;

		return vertex;
	}

}