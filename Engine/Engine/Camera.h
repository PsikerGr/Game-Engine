#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "../MathLib/Vec3d.h"
#include "../MathLib/Mat4.h"
#include "../MathLib/Tools.h"
#include "../MathLib/Vec2d.h"
#include "GameObject.h"
#include "Event\Event.hpp"

#include "Macro.h"

namespace component
{

	struct BlockCamera
	{
		Maths::Mat4 _viewMatrix;
		Maths::Mat4 _projectionMatrix;
	};

	class Camera : public resource::GameObject
	{
	public:
		Camera();
		Camera(Camera& camera) = delete;
		~Camera();

		void OnMouseMotion();
		void OnMouseWheel(const sf::Event& mouseEvent);
		void OnKeyboard(const sf::Event eventKey);
		void OnMouseButton(const sf::Event& mouseEvent, bool val);

		inline bool GetHold() { return _hold; }
		void SetHold(bool val);
		void SetTargetOnX();
		void SetTargetOnY();
		void SetTargetOnZ();
		void CameraMoveForward();
		void CameraMoveBackward();
		void CameraMoveLeft();
		void CameraMoveRight();

		void UpdateMatrix(float deltaTime);
		void UpdateFrontVector();

		inline BlockCamera& GetBlockCamera() { return _blockCamera; }

		Event<void()> Forward;
		Event<void()> BackWard;
		Event<void()> Left;
		Event<void()> Right;

	private:
		Maths::Vec2d _lastMousePos;
		
		Maths::Vec2d _eulerAngles;

		Maths::Vec3d _cameraPos;
		Maths::Vec3d _cameraUp;
		Maths::Vec3d _cameraFront;

		bool _hold;
		bool _firstMouse;

		float _mouseSensitivity;
		float _scrollSensitivity;
		float _cameraSpeed;
		float _deltaTime;
		float _fov;
		float _aspect;

		BlockCamera _blockCamera;
		
	};
}