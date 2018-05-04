#if _WIN32
#define FREEGLUT_LIB_PRAGMAS	1
#pragma comment (lib, "MathLib.lib")
#endif
#include <GL\glut.h>
#include <vector>

#include <iostream>


#include "ParserOBJ.h"
#include "LogDebug\ILogger.h"
#include "LogDebug\LoggerFile.h"
#include "Render\Simulation.h"


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	core::ILogger::SetLogger(new core::LoggerFile("Out.log"));

	renderer::Simulation::GetInstance().Play();

	core::ILogger::SetLogger(NULL);
	
	return 0;
}