#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include <string>


namespace Maths
{
#define PI 3.14159265359f

	struct Tools
	{
		static const float DegToRad(const float degree);
		static bool CompareFloat(float a, float b);
		static std::vector<std::string> Split(std::string& subject, const char* delimiter);
		
	};
}