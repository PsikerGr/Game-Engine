#pragma once

#include "Wrapper/RendererOpenGL.h"


namespace renderer
{
	class Device
	{
	public:
		Device();
		~Device();

		static void LoseMP(int, int);
		static void ChangeGUI(int, int);
		static void ExplainWhatHappened(int, int);
		static void Log();
		static void SendMessageFunction();
		void Initialize();
		void Run();


	private:
		int _width = 1280;
		int _height = 720;

	};
}