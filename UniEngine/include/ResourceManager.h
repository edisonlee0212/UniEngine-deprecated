#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "Texture2D.h"
#include "MeshRenderer.h"
#include "Model.h"

namespace UniEngine {
	class UNIENGINE_API ResourceManager : public Singleton<ResourceManager>
	{
		bool m_enableAssetMenu = true;
		std::map<size_t, std::pair<std::string, std::map<size_t, std::shared_ptr<ResourceBehaviour>>>> m_resources;
		static void ProcessNode(std::string, std::shared_ptr<GLProgram> shader, std::unique_ptr<ModelNode>&, std::vector<std::shared_ptr<Texture2D>>&, aiNode*, const aiScene*);
		static void ReadMesh(unsigned meshIndex, std::unique_ptr<ModelNode>&, std::string directory, std::shared_ptr<GLProgram> shader, std::vector<std::shared_ptr<Texture2D>>& Texture2DsLoaded, aiMesh* aimesh, const aiScene* scene);
		static void AttachChildren(EntityArchetype archetype, std::unique_ptr<ModelNode>& modelNode, Entity parentEntity, std::string parentName);

	public:
		template<typename T>
		static void Push(std::shared_ptr<T> resource);
		template<typename T>
		static std::shared_ptr<T> Get(size_t hashCode);
		template<typename T>
		static std::shared_ptr<T> Find(std::string objectName);
		template<typename T>
		static void Remove(size_t hashCode);
		static void Remove(size_t id, size_t hashCode);
		static std::shared_ptr<Model> LoadModel(const bool& addResource, std::string const& path, std::shared_ptr<GLProgram> shader, const bool& gamma = false, const unsigned & flags = 0);
		static std::shared_ptr<Texture2D> LoadTexture(const bool& addResource, const std::string& path, TextureType type = TextureType::Diffuse, const bool& generateMipmap = true, const float& gamma = 1.0f);
		static std::shared_ptr<Cubemap> LoadCubemap(const bool& addResource, const std::vector<std::string>& paths, const bool& generateMipmap = true, const float& gamma = 1.0f);
		static std::shared_ptr<Material> LoadMaterial(const bool& addResource, const std::shared_ptr<GLProgram>& program);
		static std::shared_ptr<GLProgram> LoadProgram(const bool& addResource, const std::shared_ptr<GLShader>& vertex, const std::shared_ptr<GLShader>& fragment);
		static std::shared_ptr<GLProgram> LoadProgram(const bool& addResource, const std::shared_ptr<GLShader>& vertex, const std::shared_ptr<GLShader>& geometry, const std::shared_ptr<GLShader>& fragment);
		static void LateUpdate();
		static Entity ToEntity(EntityArchetype archetype, std::shared_ptr<Model> model);
	};

	template <typename T>
	void ResourceManager::Push(std::shared_ptr<T> resource)
	{
		GetInstance().m_resources[typeid(T).hash_code()].first = std::string(typeid(T).name());
		GetInstance().m_resources[typeid(T).hash_code()].second[std::dynamic_pointer_cast<ResourceBehaviour>(resource)->GetHashCode()] = resource;
	}

	template <typename T>
	std::shared_ptr<T> ResourceManager::Get(size_t hashCode)
	{
		return std::dynamic_pointer_cast<ResourceBehaviour>(GetInstance().m_resources[typeid(T).hash_code()].second[hashCode]);
	}

	template <typename T>
	std::shared_ptr<T> ResourceManager::Find(std::string objectName)
	{
		for(const auto& i : GetInstance().m_resources[typeid(T).hash_code()].second)
		{
			if (i.second->m_name._Equal(objectName)) return std::dynamic_pointer_cast<ResourceBehaviour>(i.second);
		}
		return nullptr;
	}

	template <typename T>
	void ResourceManager::Remove(size_t hashCode)
	{
		GetInstance().m_resources[typeid(T).hash_code()].second.erase(hashCode);
	}
}
