#include "Tools.h"

#include <cmath>

namespace Maths
{
	const float Tools::DegToRad(const float degree)
	{
		return (degree * PI / 180.f);
	}

	bool Tools::CompareFloat(float a, float b)
	{
		if (a == b)
			return true;

		float relativeError;
		if (fabs(b) > fabs(a))
			relativeError = fabs((a - b) / b);
		else
			relativeError = fabs((a - b) / a);

		if (relativeError <= 0.00001)
			return true;

		return false;
	}

	std::vector<std::string> Tools::Split(std::string & subject, const char * delimiter)
	{
		std::vector<std::string> splitted;
		std::stringstream stream(subject);
		std::string token;

		while (std::getline(stream, token, delimiter[0]))
		{
			if (token != "f")
				splitted.push_back(token);
		}

		return splitted;
	}
	
}