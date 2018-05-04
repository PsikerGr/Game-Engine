#pragma once

#include "..\Macro.h"

namespace renderer
{
	class Device;

	class ENGINE_DLL Simulation
	{
	public:
		Simulation();
		~Simulation();

		void Play();


		static Simulation& GetInstance();

	private:

		Device* _dev;

	};

}