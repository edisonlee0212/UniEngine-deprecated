#pragma once
#include "SystemBase.h"
#include "PlanetTerrain.h"
using namespace UniEngine;
namespace Planet{
	class PlanetTerrainSystem :
		public SystemBase
	{
		friend class PlanetTerrain;
		static std::shared_ptr<Material> _DefaultSurfaceMaterial;
	public:
		void OnCreate() override;
		void Update() override;
		void FixedUpdate() override;
		static std::shared_ptr<Material> GetDefaultSurfaceMaterial();
		void CheckLod(std::mutex& mutex, std::unique_ptr<TerrainChunk>& chunk, const PlanetInfo& info, const GlobalTransform& planetTransform, const GlobalTransform& cameraTransform);
		void RenderChunk(std::unique_ptr<TerrainChunk>& chunk, Material* material, glm::mat4& matrix, CameraComponent* camera, bool receiveShadow);
	};
}