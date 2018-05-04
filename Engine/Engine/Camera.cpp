#include "Camera.h"

#include <iostream>

#include "GL\glew.h"
#include "GL\freeglut.h"
#include "LogDebug\ILogger.h"
#include "Wrapper\SFML\AbstractRender.h"
#include "Inputs\InputsManager.h"

namespace component
{

	Camera::Camera()
		: _mouseSensitivity(0.5f), _scrollSensitivity(1.f), _fov(45.0f), _cameraSpeed(0.1f),
		_cameraPos(Maths::Vec3d(0.0f, 0.0f, 10.0f)),_cameraUp(Maths::Vec3d(0.0f, 1.0f, 0.0f)), _cameraFront(Maths::Vec3d(0.0f, 0.0f, -1.0f)),
		_eulerAngles(Maths::Vec2d(-90.0f, 0.0f)), _lastMousePos(Maths::Vec2d(640.0f, 360.0f))
	{
		core::ILogger::LogMessage("Create Camera at : ", __FILE__, __LINE__);
		SetHold(false);
		_firstMouse = true;

		_aspect = 1280.0f / 720.0f;
		_blockCamera._projectionMatrix = Maths::Mat4::Projection(_aspect, _fov, 0.1f, 1000.0f);

		Forward.Bind<Camera, &Camera::CameraMoveForward>(this);
		BackWard.Bind<Camera, &Camera::CameraMoveBackward>(this);
		Left.Bind<Camera, &Camera::CameraMoveLeft>(this);
		Right.Bind<Camera, &Camera::CameraMoveRight>(this);
		InputsManager::GetInstance().RegisterInput(Forward, E_KeyboardInputsType::W);
		InputsManager::GetInstance().RegisterInput(BackWard, E_KeyboardInputsType::S);
		InputsManager::GetInstance().RegisterInput(Left, E_KeyboardInputsType::A);
		InputsManager::GetInstance().RegisterInput(Right, E_KeyboardInputsType::D);
	}

	Camera::~Camera()
	{
		core::ILogger::LogMessage("Delete Camera at : ", __FILE__, __LINE__);
	}

	void Camera::OnMouseMotion()
	{
		if (_hold == true)
		{
			float x = renderer::AbstractRender::GetMousePos().x;
			float y = renderer::AbstractRender::GetMousePos().y;

			if (_firstMouse)
			{
				_lastMousePos.x = x;
				_lastMousePos.y = y;
				_firstMouse = false;
			}

			float xOffset = x - _lastMousePos.x;
			float yOffset = _lastMousePos.y - y;
			_lastMousePos.x = x;
			_lastMousePos.y = y;

			xOffset *= _mouseSensitivity;
			yOffset *= _mouseSensitivity;

			_eulerAngles.x += xOffset;
			_eulerAngles.y += yOffset;

			if (_eulerAngles.y > 89.0f)
				_eulerAngles.y = 89.0f;
			if (_eulerAngles.y < -89.0f)
				_eulerAngles.y = -89.0f;

			UpdateFrontVector();
		}
	}

	void Camera::SetHold(bool val)
	{
		_hold = val;
	}

	/*	/* Set the X pos of the camera near to the X pos of the target
		WIP : need the position of the current select object */
	void Camera::SetTargetOnX()
	{
		
	}

	/*	Set the Y pos of the camera near to the Y pos of the target
		WIP : need the position of the current select object */
	void Camera::SetTargetOnY()
	{
		
	}

	/*	Set the Z pos of the camera near to the Z pos of the target
		WIP : need the position of the current select object*/
	void Camera::SetTargetOnZ()
	{
		
	}

	void Camera::CameraMoveForward()
	{
		_cameraPos += _cameraSpeed * _cameraFront;
	}

	void Camera::CameraMoveBackward()
	{
		_cameraPos -= _cameraSpeed * _cameraFront;
	}

	void Camera::CameraMoveLeft()
	{
		_cameraPos -= (_cameraFront.CrossProduct(_cameraUp)).Normalized() * _cameraSpeed;
	}

	void Camera::CameraMoveRight()
	{
		_cameraPos += (_cameraFront.CrossProduct(_cameraUp)).Normalized() * _cameraSpeed;
	}

	void Camera::OnMouseButton(const sf::Event& mouseEvent, bool val)
	{
		if (mouseEvent.mouseButton.button == sf::Mouse::Left)
		{
			SetHold(val);
			_firstMouse = true;
		}
		else
			SetHold(false);
	}

	void Camera::OnMouseWheel(const sf::Event& mouseEvent)
	{
		if (mouseEvent.mouseWheel.delta > 0)
		{
			if (_fov >= 1.0f && _fov <= 45.0f)
				_fov -= _scrollSensitivity;
		}
		else if (mouseEvent.mouseWheel.delta < 0)
		{
			if (_fov >= 1.0f && _fov <= 45.0f)
				_fov += _scrollSensitivity;
		}

		if (_fov <= 1.0f)
			_fov = 1.0f;
		if (_fov >= 45.0f)
			_fov = 45.0f;

		_blockCamera._projectionMatrix = Maths::Mat4::Projection(_aspect, _fov, 0.1f, 1000.0f);
	}

	void Camera::OnKeyboard(const sf::Event eventKey)
	{
		sf::Event::KeyEvent keyboardEvent = eventKey.key;
		
		if (keyboardEvent.code == sf::Keyboard::F)
			SetTargetOnX();
	}

	void Camera::UpdateMatrix(float deltaTime)
	{
		Maths::Vec3d newDirection = _cameraPos + _cameraFront;

		auto tmp = Maths::Mat4::LookAt(_cameraPos, newDirection, _cameraUp);
		
		_blockCamera._viewMatrix = tmp;
	}

	void Camera::UpdateFrontVector()
	{
		Maths::Vec3d front;
		front.x = cos(Maths::Tools::DegToRad(_eulerAngles.x)) * cos(Maths::Tools::DegToRad(_eulerAngles.y));
		front.y = sin(Maths::Tools::DegToRad(_eulerAngles.y));
		front.z = sin(Maths::Tools::DegToRad(_eulerAngles.x)) * cos(Maths::Tools::DegToRad(_eulerAngles.y));
		_cameraFront = front.Normalized();
	}

}