#pragma once

#include <iostream>


namespace resource
{
	class Component
	{
	public:

		Component();
		Component(std::string name);
		virtual ~Component();

		const std::string& GetName() const;



	private:
		std::string _name;
		

	};

	

}