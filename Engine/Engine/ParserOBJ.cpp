#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <mutex>

#include "ParserOBJ.h"
#include "LogDebug\ILogger.h"
#include "Mesh.h"
#include "Wrapper\RHI.h"
#include "Render/Rendering.h"
#include "ResourceManager.h"
#include "Material.h"
#include "GameObject.h"

namespace resource
{
	ParserOBJ::ParserOBJ()
	{
		core::ILogger::LogMessage("Create ParserOBJ at : ", __FILE__, __LINE__);
		InitValue();
	}

	ParserOBJ::~ParserOBJ()
	{
		core::ILogger::LogMessage("Delete ParserOBJ at : ", __FILE__, __LINE__);

		Clearvalue();
	}

	GameObject* ParserOBJ::ParseOBJ(const char* objFilename, const char* mtlFileName)
	{
		std::ifstream fileStream;
		fileStream.open(objFilename, std::ios::binary);
		if (!fileStream.is_open())
		{
			std::cout << "Impossible to open " << objFilename <<" !\n" << std::endl;
			return false;
		}
		
		std::string line;
		
		GameObject* newGameObject = new GameObject();
		newGameObject->SetIsParent(true);
		renderer::RHI::DrawGameObject(newGameObject);
		GameObject* currentObject = nullptr;
		std::string curname = "";

		while (std::getline(fileStream, line))
		{

			if (line == "" || line[0] == '#')
				continue;

			std::istringstream lineStream(line);
			

			if (line.substr(0, 1) == "g")
			{
				curname = line.substr(2);

				CreateGroupMesh(currentObject);

				GameObject* newGameObjectGroup = new GameObject();
				newGameObjectGroup->AddComponent(new Mesh(), "Mesh");
				newGameObjectGroup->SetName(curname);
				currentObject = newGameObjectGroup;
				newGameObject->AddChild(currentObject);
			}

			else if (line.substr(0, 2) == "v ")
			{
				std::istringstream stream(line.substr(2));
				Maths::Vec3d vertex;
				
				stream >> vertex.x; stream >> vertex.y; stream >> vertex.z;
				_vVertices.push_back(vertex);
			}


			else if (line.substr(0, 2) == "vt")
			{
				std::istringstream stream(line.substr(2));
				Maths::Vec2d uv;
		
				stream >> uv.x; stream >> uv.y;
				_vTextures.push_back(uv);
			}

			else if (line.substr(0, 2) == "vn")
			{
				std::istringstream stream(line.substr(2));
				Maths::Vec3d normal;
			
				stream >> normal.x; stream >> normal.y; stream >> normal.z;
				_vNormals.push_back(normal);
			}

			else if (line.substr(0, 2) == "f ")
			{

				std::istringstream stream(line.substr(2));
				CreateFace(line);
			}

			else if (line.substr(0, 1) == "u")
			{
				std::string mtlName = line.substr(7);


				ParseMTL(mtlFileName, currentObject->GetComponent<Mesh>());
			}
		}

		CreateGroupMesh(currentObject);
		
		return newGameObject;
	}

	bool ParserOBJ::ParseMTL(const char* filename, Mesh* mesh)
	{
		std::ifstream fileStream;
		fileStream.open(filename, std::ios::binary);

		std::vector<Material*> materialVector;

		std::string line;
		std::string curname;
		std::string curText;

		Material * mat = nullptr;

		while (std::getline(fileStream, line))
		{
			if (line.substr(0, 1) == "n")
			{
				curname = line.substr(7);
				mat = new Material();
				materialVector.push_back(mat);
			}

			else if (line.substr(0, 2) == "Kd")
			{
				std::vector<std::string> splitted = Split(line.substr(3), " ");
				
				mat->AddMaterial((float)std::strtod(splitted[0].c_str(), NULL), (float)std::strtod(splitted[1].c_str(), NULL), (float)std::strtod(splitted[2].c_str(), NULL), EMaterialType::Diffuse);
			}

			else if (line.substr(0, 2) == "Ka")
			{
				std::vector<std::string> splitted = Split(line.substr(3), " ");

				mat->AddMaterial((float)std::strtod(splitted[0].c_str(), NULL), (float)std::strtod(splitted[1].c_str(), NULL), (float)std::strtod(splitted[2].c_str(), NULL), EMaterialType::Ambiant);
			}

			else if (line.substr(0, 2) == "Ks")
			{
				std::vector<std::string> splitted = Split(line.substr(3), " ");

				mat->AddMaterial((float)std::strtod(splitted[0].c_str(), NULL), (float)std::strtod(splitted[1].c_str(), NULL), (float)std::strtod(splitted[2].c_str(), NULL), EMaterialType::Specular);
			}

			else if (line.substr(0, 3) == "map")
			{
				if (line.substr(4, 2) == "Kd")
				{
					std::string texturePath = line.substr(7);
					std::vector<std::string> splitted = Split(texturePath, "\r");
					mesh->GetMaterial()->AddTexture(splitted[0]);
				}

				else if (line.substr(4, 2) == "Ka")
				{
				}

				else if (line.substr(4, 2) == "Ks")
				{
				}
			}


			else if (line.substr(0, 1) == "d")
			{
			}

		}

		return true;
	}
	
	std::vector<std::string> ParserOBJ::Split(std::string& subject, const char* delimiter)
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

	uint16_t ParserOBJ::ParseFragment(std::vector<std::string>& splitline, uint32_t vertexIdx)
	{
		std::vector<std::string> fragmentVertex = Split(splitline[vertexIdx], "/");

		int32_t tmp;

 		uint32_t idxVertex = 0;
		uint32_t idxTexture = 0;
		uint32_t idxNormal = 0;

		if (fragmentVertex.size() == 3)
		{
			tmp = std::stoi(fragmentVertex[0]);
			idxVertex = tmp < 0 ? static_cast<uint32_t>(_vVertices.size() + tmp) : tmp;

			tmp = std::stoi(fragmentVertex[1]);
			idxTexture = tmp < 0 ? static_cast<uint32_t>(_vTextures.size() + tmp) : tmp;

			tmp = std::stoi(fragmentVertex[2]);
			idxNormal = tmp < 0 ? static_cast<uint32_t>(_vNormals.size() + tmp) : tmp;

		}
		else if (fragmentVertex.size() == 2)
		{
			tmp = std::stoi(fragmentVertex[0]);
			idxVertex = tmp < 0 ? static_cast<uint16_t>(_vVertices.size() + tmp) : tmp;

			tmp = std::stoi(fragmentVertex[1]);
			idxTexture = tmp < 0 ? static_cast<uint16_t>(_vTextures.size() + tmp) : tmp;
		}

		else if (fragmentVertex.size() == 1)
		{
			tmp = std::stoi(fragmentVertex[0]);
			idxVertex = tmp < 0 ? static_cast<uint16_t>(_vVertices.size() + tmp) : tmp;
		}
		else
			throw std::runtime_error("ParserOBJ::ParseFragmentVertex() - bad fragment vertex format");

		return CreateFragmentIdx(idxVertex, idxTexture, idxNormal);
	}

	uint32_t ParserOBJ::CreateFragmentIdx(uint32_t vertexIdx, uint32_t textureIdx, uint32_t normalIdx)
	{
		_vecFragmentIdx.push_back({ vertexIdx, textureIdx, normalIdx });

		return _vecFragmentIdx.size() - 1;
	}

	void ParserOBJ::CreateFace(std::string splitline)
	{
		std::vector<std::string> splitted = Split(splitline, " ");
		uint16_t fragmentArray[3];

		for (size_t i = 0; i < 3; ++i)
		{
			fragmentArray[i] = ParseFragment(splitted, i);
		}

		_vecFaces.push_back({fragmentArray[0], fragmentArray[1], fragmentArray[2] });
	}

	void ParserOBJ::InitValue()
	{
		_vVertices.clear();
		_vVertices.push_back(Maths::Vec3d());

		_vNormals.clear();
		_vNormals.push_back(Maths::Vec3d());

		_vTextures.clear();
		_vTextures.push_back(Maths::Vec2d());

		_vecFragmentIdx.clear();
		_vecFaces.clear();
		_vecFragments.clear();
	}

	void ParserOBJ::CreateVertexList(std::vector<Maths::Vec3d> vertices, std::vector<Maths::Vec3d> normals, std::vector<Maths::Vec2d> textures)
	{
		std::vector<FragmentIdx>::iterator fragIt;

		for (fragIt = _vecFragmentIdx.begin(); fragIt != _vecFragmentIdx.end(); fragIt++)
		{
			_vecFragments.push_back({ vertices[(*fragIt)._vFragment], textures[(*fragIt)._tIndices], normals[(*fragIt)._nFragment] });
		}
	}
	
	void ParserOBJ::CreateGroupMesh(GameObject* currentGameObject)
	{
		if (currentGameObject != nullptr)
		{
			CreateVertexList(_vVertices, _vNormals, _vTextures);
			float* vertexArray = VectorToFloatArray<float, Fragment>(_vecFragments, 8);
			uint32_t* indicesArray = VectorToFloatArray<uint32_t, Face>(_vecFaces, 3);
			renderer::Rendering::GetInstance().CoreCreateMesh(currentGameObject, _vecFragments.size() * 8, vertexArray, _vecFaces.size() * 3, indicesArray, currentGameObject->GetName(), currentGameObject->GetComponent<Mesh>()->GetMaterial()->GetTexture()->TextureData._path);
			_vecFaces.clear();
			_vecFragments.clear();
		}
	}


	ParserOBJ& ParserOBJ::GetInstance()
	{
		static std::unique_ptr<ParserOBJ> instance;
		static std::once_flag once_flag;

		std::call_once(once_flag, [](void)
		{
			instance.reset(new ParserOBJ());
		});

		return *instance.get();
	}

	void ParserOBJ::Clearvalue()
	{
		_vVertices.clear();
		_vNormals.clear();
		_vTextures.clear();
		_vecFragmentIdx.clear();
		_vecFaces.clear();
		_vecFragments.clear();
	}
}