#pragma once

#include <string>


namespace resource
{
	enum LoadMode
	{
		DDS = 0,
		STBI
	};

	class Texture
	{
	public:
		Texture();
		~Texture();

		struct TexData
		{
			uint32_t _texture;
			std::string _path;
		} TextureData;

	};

}
