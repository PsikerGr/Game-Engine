#pragma once

#include <cstdint>


class GLShader
{
public:

	GLShader() = default;
	~GLShader() = default;

	bool LoadShader(uint32_t type, const char* path);
	void LoadShaders(const char* vertexShader, const char* fragmentShader, const char* geometryShader = nullptr);

	bool Create();
	void Bind();
	void Unbind();
	void Destroy();
	inline uint32_t Get() { return _Program; }

	void SetLinkCallBack(void (*func)(int)) { LinkCallBack = func; }

private:
	uint32_t _VertexShader;
	uint32_t _Program;
	uint32_t _FragmentShader;
	uint32_t _GeometryShader;

	//ret (*name)(params ...) definit un pointeur sur fonction
	//

	void(*LinkCallBack)(int);
};