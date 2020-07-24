#pragma once
#include "UniEngine.h"
#include "Branch.h"
#include "Envelope.h"
namespace SpaceColonizationTree {
	class Tree
	{
	public:
		
		Tree(Material* pointMaterial, Material* meshMaterial, Material* organMaterial);
		
		void Draw(Camera* camera, Material* pointMaterial, glm::vec3 scale, bool drawOrgan = true);

		~Tree();

		void GrowTrunk(float growDist, float attractionDist, Envelope* envelope, glm::vec3 tropism);

		void Grow(float growDist, float attractionDist, float removeDist, Envelope* envelope, glm::vec3 tropism = glm::vec3(0.0f),
			float distDec = 0.015f, float minDist = 0.01f, float decimationDistChild = 0.02f, float decimationDistParent = 0.02f);

		void CalculateMesh(int resolution = 4, int triangleLimit = 8192);
		Mesh* GetMesh();
		std::vector<glm::mat4>* GetLeafList();
		bool NeedsToGrow();
	private:
		Mesh* _Mesh;
		std::vector<glm::mat4> _LeafList;
		Branch* _Root;
		std::vector<Branch*> _GrowingBranches;
		bool _NeedsToGrow, _MeshGenerated, _OrganGenerated;
		int _MaxGrowIteration;
		std::vector<glm::mat4> _PointMatrices;


		inline void CalculateRadius();

		inline void CollectPoints();

		inline void NodeRelocation();

		inline void NodeSubdivision();

		inline void GenerateOrgan();
	};
}