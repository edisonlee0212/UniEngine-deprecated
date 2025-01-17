#pragma once
#include "Core.h"
#include "EditorManager.h"
#include "UniEngineAPI.h"
namespace UniEngine {
	enum class UNIENGINE_API TextureType {
		Albedo,
		Normal,
		Metallic,
		Roughness,
		Ao,
		Ambient,
		Diffuse,
		Specular,
		Emissive,
		Displacement
	};
	class UNIENGINE_API Texture2D : public ResourceBehaviour
	{
		friend class Material;
		friend class RenderManager;
		friend class Bloom;
		TextureType m_type;
		std::shared_ptr<GLTexture2D> m_texture;
		std::string m_path;
		friend class ResourceManager;
		friend class CameraComponent;
	public:
		Texture2D(TextureType type = TextureType::Diffuse);
		void SetType(TextureType type);
		TextureType GetType() const;
		glm::vec2 GetResolution() const;
		void StoreToPng(const std::string& path, int resizeX = -1, int resizeY = -1, bool alphaChannel = false, unsigned compressionLevel = 8) const;
		void StoreToJpg(const std::string& path, int resizeX = -1, int resizeY = -1, unsigned quality = 100) const;
		std::shared_ptr<GLTexture2D> Texture() const;
		std::string Path() const;
	};
}
