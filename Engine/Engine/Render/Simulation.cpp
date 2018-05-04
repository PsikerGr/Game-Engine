#include <memory>
#include <mutex>

#include "Simulation.h"
#include "../Device.h"

namespace renderer
{
	Simulation::Simulation()
	{
		_dev = new Device();
		_dev->Initialize();
	}

	Simulation::~Simulation()
	{
		delete _dev;
		_dev = nullptr;
	}

	void Simulation::Play()
	{
		_dev->Run();
	}

	Simulation & Simulation::GetInstance()
	{
		static std::unique_ptr<Simulation> instance;
		static std::once_flag once_flag;

		std::call_once(once_flag, [](void)
		{
			instance.reset(new Simulation());
		});

		return *instance.get();
	}
}