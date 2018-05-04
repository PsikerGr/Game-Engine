#pragma once
#include <vector>

class Skybox
{
public:
	Skybox();
	~Skybox();

	void CreateSkybox(std::vector<const char*> paths);
	void InitializeSkyboxVertices();
	std::vector<const char*> GetCubeMapFaces() { return _faces; }
	uint32_t GetTexSkybox() { return _texSkybox; }
	float* GetSkyboxVertices() { return _skyboxVertices; }

private:
	std::vector<const char*> _faces;
	uint32_t _texSkybox;
	uint32_t _texCubMap;
	float* _skyboxVertices;

};