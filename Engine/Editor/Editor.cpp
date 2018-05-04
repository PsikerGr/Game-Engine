#include "stdafx.h"
#include <iostream>

#include "Render\Simulation.h"
#include "Event\Event.hpp"


int main()
{

	renderer::Simulation::GetInstance().Play();

    return 0;
}

