#pragma once
#include "UniEngineAPI.h"
#include "SystemBase.h"
#include "WorldTime.h"
#include "Entity.h"
#include "PrivateComponentStorage.h"
namespace UniEngine {
	struct UNIENGINE_API Bound {
		glm::vec3 m_min;
		glm::vec3 m_max;
		Bound();
		glm::vec3 Size() const;
		glm::vec3 Center() const;
		bool InBound(const glm::vec3& position) const;
		void ApplyTransform(const glm::mat4& transform);
		void PopulateCorners(std::vector<glm::vec3>& corners) const;
	};

	enum class UNIENGINE_API SystemGroup {
		PreparationSystemGroup,
		SimulationSystemGroup,
		PresentationSystemGroup
	};


	struct WorldEntityStorage {
		size_t m_parentHierarchyVersion = 0;
		std::vector<Entity> m_entities;
		std::vector<EntityInfo> m_entityInfos;
		std::vector<EntityComponentDataStorage> m_entityComponentStorage;
		PrivateComponentStorage m_entityPrivateComponentStorage;
		std::vector<EntityQuery> m_entityQueries;
		std::vector<EntityQueryInfo> m_entityQueryInfos;
		std::queue<EntityQuery> m_entityQueryPools;
	};
	
	class UNIENGINE_API World
	{
		friend class Application;
		friend class EntityManager;
		friend class SerializationManager;
		WorldEntityStorage m_worldEntityStorage;
		WorldTime* m_time;
		std::vector<SystemBase*> m_preparationSystems;
		std::vector<SystemBase*> m_simulationSystems;
		std::vector<SystemBase*> m_presentationSystems;
		std::vector<std::function<void()>> m_externalFixedUpdateFunctions;
		size_t m_index;
		Bound m_worldBound;
		bool m_needFixedUpdate = false;
	public:
		void Purge();
		World& operator=(World&&) = delete;
		World& operator=(const World&) = delete;
		void RegisterFixedUpdateFunction(const std::function<void()>& func);
		[[nodiscard]] Bound GetBound() const;
		void SetBound(const Bound& value);
		void SetFrameStartTime(double time) const;
		void SetTimeStep(float timeStep) const;
		[[nodiscard]] size_t GetIndex() const;
		World(size_t index);
		void ResetTime() const;
		[[nodiscard]] WorldTime* Time() const;
		template <class T = SystemBase>
		T* CreateSystem(SystemGroup group);
		template <class T = SystemBase>
		void DestroySystem();
		template <class T = SystemBase>
		T* GetSystem();
		~World();
		void PreUpdate();
		void Update();
		void LateUpdate();
	};

	template <class T>
	T* World::CreateSystem(SystemGroup group) {
		T* system = GetSystem<T>();
		if (system != nullptr) {
			return system;
		}
		system = new T();
		system->m_world = this;
		system->m_time = m_time;
		switch (group)
		{
		case UniEngine::SystemGroup::PreparationSystemGroup:
			m_preparationSystems.push_back(static_cast<SystemBase*>(system));
			break;
		case UniEngine::SystemGroup::SimulationSystemGroup:
			m_simulationSystems.push_back(static_cast<SystemBase*>(system));
			break;
		case UniEngine::SystemGroup::PresentationSystemGroup:
			m_presentationSystems.push_back(static_cast<SystemBase*>(system));
			break;
		default:
			break;
		}
		system->OnCreate();
		return system;
	}
	template <class T>
	void World::DestroySystem() {
		T* system = GetSystem<T>();
		if (system != nullptr) {
			system->OnDestroy();
			delete system;
		}
	}
	template <class T>
	T* World::GetSystem() {
		for (auto i : m_preparationSystems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
		for (auto i : m_simulationSystems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
		for (auto i : m_presentationSystems) {
			if (dynamic_cast<T*>(i) != nullptr) {
				return dynamic_cast<T*>(i);
			}
		}
		return nullptr;
	}
}