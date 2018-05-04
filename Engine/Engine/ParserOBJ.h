#pragma once

#include <vector>
#include "../MathLib/Vec2d.h"
#include "../MathLib/Vec3d.h"

namespace resource
{
	class Mesh;
	class GameObject;

	enum ELineType
	{
		V = 0,
		VT,
		VN,
		F,
		O,
		G,
		MTLIB,
		USEMTL

	};

	struct FragmentIdx
	{
		uint32_t _vFragment;
		uint32_t _tIndices;
		uint32_t _nFragment;
		
				
	};

	struct Fragment
	{
		Maths::Vec3d _vVertex;
		Maths::Vec2d _vTexture;
		Maths::Vec3d _vNormal;
		
	};

	struct Face
	{
		uint32_t _fragmentIdx[3];
	};


	class ParserOBJ
	{
	public:
		ParserOBJ();
		~ParserOBJ();

		GameObject* ParseOBJ(const char* objFilename, const char* mtlFileName);
		bool ParseMTL(const char* filename, Mesh* mesh);
		std::vector<std::string> Split(std::string& subject, const char* delimiter);
		uint16_t ParseFragment(std::vector<std::string>& splitline, uint32_t vertexIdx);
		uint32_t CreateFragmentIdx(uint32_t vertexIdx, uint32_t textureIdx, uint32_t normalIdx);
		void CreateVertexList(std::vector<Maths::Vec3d> vertices, std::vector<Maths::Vec3d> normals, std::vector<Maths::Vec2d> textures);
		void CreateFace(std::string splitline);
		void InitValue();
		void CreateGroupMesh(GameObject* currentGameObject);
		void Clearvalue();

		template<typename T, typename T1>
		T* VectorToFloatArray(std::vector<T1> vector, int32_t offset);

		static ParserOBJ& GetInstance();


	private:

		std::vector<Maths::Vec3d> _vVertices;
		std::vector<Maths::Vec3d> _vNormals;
		std::vector<Maths::Vec2d> _vTextures;

		std::vector<FragmentIdx> _vecFragmentIdx;
		std::vector<Face> _vecFaces;
		std::vector<Fragment> _vecFragments;

	};

	template<typename T, typename T1>
	T* ParserOBJ::VectorToFloatArray(std::vector<T1> vector, int32_t offset)
	{
		uint32_t vertexSize = vector.size() * offset;
		T* convertedVector = new T[vertexSize];



		std::memcpy(convertedVector, &vector[0], vector.size() * sizeof(T1));

		return convertedVector;

	}


}