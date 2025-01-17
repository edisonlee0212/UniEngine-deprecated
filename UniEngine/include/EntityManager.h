#pragma once
#include "UniEngineAPI.h"
#include "Transforms.h"
#include "Singleton.h"
#include "Debug.h"
#include "JobManager.h"
#include "World.h"
namespace UniEngine {
	UNIENGINE_API bool ComponentTypeComparator(const ComponentDataType& a, const ComponentDataType& b);
#pragma region EntityManager
	class UNIENGINE_API EntityManager final : public Singleton<EntityManager>{
		friend class PrivateComponentStorage;
		friend class TransformManager;
		friend class EditorManager;
		friend class World;
		friend class SerializationManager;
		friend struct EntityArchetype;
		friend struct EntityQuery;
		friend struct Entity;
		size_t m_archetypeChunkSize = ARCHETYPECHUNK_SIZE;
		EntityArchetype m_basicArchetype = EntityArchetype();
#pragma region Data Storage
		WorldEntityStorage* m_currentAttachedWorldEntityStorage = nullptr;
		std::vector<Entity>* m_entities = nullptr;
		std::vector<EntityInfo>* m_entityInfos = nullptr;
		std::vector<EntityComponentDataStorage>* m_entityComponentStorage = nullptr;
		PrivateComponentStorage* m_entityPrivateComponentStorage = nullptr;
		std::vector<EntityQuery>* m_entityQueries = nullptr;
		std::vector<EntityQueryInfo>* m_entityQueryInfos = nullptr;
		std::queue<EntityQuery>* m_entityQueryPools = nullptr;
#pragma endregion
		template<typename T = ComponentDataBase>
		static bool CheckComponentTypes(T arg);
		template<typename T = ComponentDataBase, typename... Ts>
		static bool CheckComponentTypes(T arg, Ts... args);

		template<typename T = ComponentDataBase>
		static size_t CollectComponentTypes(std::vector<ComponentDataType>* componentTypes, T arg);
		template<typename T = ComponentDataBase, typename... Ts>
		static size_t CollectComponentTypes(std::vector<ComponentDataType>* componentTypes, T arg, Ts... args);
		template<typename T = ComponentDataBase, typename... Ts>
		static std::vector<ComponentDataType> CollectComponentTypes(T arg, Ts... args);
		static void DeleteEntityInternal(const Entity& entity);
		static void RefreshEntityQueryInfos(const size_t& index);
		static void EraseDuplicates(std::vector<ComponentDataType>& types);
#pragma region ForEach
		template<typename T1 = ComponentDataBase>
		static void ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase>
		static void ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase>
		static void ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase>
		static void ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase>
		static void ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase>
		static void ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase, typename T7 = ComponentDataBase>
		static void ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase, typename T7 = ComponentDataBase, typename T8 = ComponentDataBase>
		static void ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&)>& func, bool checkEnable = true);

#pragma endregion
		template<typename T = ComponentDataBase>
		static void GetComponentDataArrayStorage(const EntityComponentDataStorage& storage, std::vector<T>& container);
		static void GetEntityStorage(const EntityComponentDataStorage& storage, std::vector<Entity>& container);
		static size_t SwapEntity(const EntityComponentDataStorage& storage, size_t index1, size_t index2);

		template<typename T = ComponentDataBase>
		static void GetComponentDataArray(const EntityQuery& entityQuery, std::vector<T>& container);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase>
		static void GetComponentDataArray(const EntityQuery& entityQuery, std::vector<T1>& container, const std::function<bool(const T2&)>& filterFunc);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase>
		static void GetComponentDataArray(const EntityQuery& entityQuery, std::vector<T1>& container, const std::function<bool(const T2&, const T3&)>& filterFunc);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase>
		static void GetComponentDataArray(const EntityQuery& entityQuery, const T1& filter, std::vector<T2>& container);


		static void GetEntityArray(const EntityQuery& entityQuery, std::vector<Entity>& container);
		template<typename T1 = ComponentDataBase>
		static void GetEntityArray(const EntityQuery& entityQuery, std::vector<Entity>& container, const std::function<bool(const Entity&, const T1&)>& filterFunc);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase>
		static void GetEntityArray(const EntityQuery& entityQuery, std::vector<Entity>& container, const std::function<bool(const Entity&, const T1&, const T2&)>& filterFunc);
		template<typename T1 = ComponentDataBase>
		static void GetEntityArray(const EntityQuery& entityQuery, const T1& filter, std::vector<Entity>& container);

		static size_t GetEntityAmount(EntityQuery entityQuery);
		//Enable or Disable an Entity. Note that the disable action will recursively disable the children of current entity. 
		static void SetEnable(const Entity& entity, const bool& value);
		static void SetStatic(const Entity& entity, const bool& value);

		static void SetEnableSingle(const Entity& entity, const bool& value);
		static bool IsEntityEnabled(const Entity& entity);
		static bool IsEntityStatic(const Entity& entity);

		static bool IsEntityDeleted(const size_t& index);
		static bool IsEntityValid(const Entity& entity);

		static void SetComponentData(const Entity& entity, size_t id, size_t size, ComponentDataBase* data);
		friend class SerializationManager;
		static ComponentDataBase* GetComponentDataPointer(const Entity& entity, const size_t& id);
		static EntityArchetype CreateEntityArchetype(const std::string& name, const std::vector<ComponentDataType>& types);
		static void SetPrivateComponent(const Entity& entity, const std::string& name, const size_t& id, PrivateComponentBase* ptr, const bool& enabled = true);
		static bool IsEntityArchetypeValid(const EntityArchetype& archetype);

		static void EntityHierarchyIteratorHelper(const Entity& target, const std::function<void(const Entity& entity)>& func);
	public:
		static void EntityHierarchyIterator(const Entity& target, const std::function<void(const Entity& entity)>& func, const bool& fromRoot = true);
		
#pragma region Unsafe
		//Unsafe zone, allow directly manipulation of entity data, which may result in data corruption.
		/**
		 * \brief Unsafe method, retrieve the internal storage of the entities.
		 * \return A pointer to the internal storage for all arrays.
		 */
		static std::vector<Entity>* UnsafeGetAllEntities();
		
		static std::vector<EntityComponentDataStorage> UnsafeGetComponentDataStorage(const EntityQuery& entityQuery);
		static void UnsafeForEachComponent(const Entity& entity, const std::function<void(const ComponentDataType& type, void* data)>& func);
		static void UnsafeForEachEntityStorage(const std::function<void(int i, const EntityComponentDataStorage& storage)>& func);

		/**
		 * \brief Unsafe method, directly retrieve the pointers and sizes of component data array.
		 * \tparam T The type of data
		 * \param entityQuery The query to filter the data for targeted entity type.
		 * \return If the entity type contains the data, return a list of pointer and size pairs, which the pointer points to the first data instance and the size indicates the amount of data instances.
		 */
		template <typename T>
		static std::vector<std::pair<T*, size_t>> UnsafeGetComponentDataArray(const EntityQuery& entityQuery);
#pragma endregion

		static size_t GetArchetypeChunkSize();
		
		static EntityArchetypeInfo GetArchetypeInfo(const EntityArchetype& entityArchetype);
		
		static Entity GetRoot(const Entity& entity);
		static Entity GetEntity(const size_t& index);
		static EntityArchetype GetEntityArchetype(const Entity& entity);

		template <typename T>
		static const std::vector<Entity>* GetPrivateComponentOwnersList();
		static void ForEachPrivateComponent(const Entity& entity, const std::function<void(PrivateComponentElement& data)>& func);

		static void GetAllEntities(std::vector<Entity>& target);
		static void Detach();
		static void Attach(std::unique_ptr<World>& world);
		template<typename T = ComponentDataBase, typename... Ts>
		static EntityArchetype CreateEntityArchetype(const std::string& name, T arg, Ts... args);

		static Entity CreateEntity(const std::string& name = "New Entity");

		static Entity CreateEntity(const EntityArchetype& archetype, const std::string& name = "New Entity");
		static std::vector<Entity> CreateEntities(const EntityArchetype& archetype, const size_t& amount, const std::string& name = "New Entity");
		static void DeleteEntity(const Entity& entity);

		static std::string GetEntityName(const Entity& entity);

		static void SetEntityName(const Entity& entity, const std::string& name);

		static void SetParent(const Entity& entity, const Entity& parent, const bool& recalculateTransform = true);
		static Entity GetParent(const Entity& entity);
		static std::vector<Entity> GetChildren(const Entity& entity);
		static size_t GetChildrenAmount(const Entity& entity);
		static void ForEachChild(const Entity& entity, const std::function<void(Entity child)>& func);

		static void RemoveChild(const Entity& entity, const Entity& parent);
		static size_t GetParentHierarchyVersion();

		template<typename T = ComponentDataBase>
		static void AddComponentData(const Entity& entity, const T& value);

		template<typename T = ComponentDataBase>
		static T RemoveComponentData(const Entity& entity);

		static void RemoveComponentData(const Entity& entity, const size_t& typeID);

		template<typename T = ComponentDataBase>
		static void SetComponentData(const Entity& entity, const T& value);

		template<typename T = ComponentDataBase>
		static void SetComponentData(const size_t& index, const T& value);

		template<typename T = ComponentDataBase>
		static T GetComponentData(const Entity& entity);



		template<typename T = ComponentDataBase>
		static bool HasComponentData(const Entity& entity);

		template<typename T = ComponentDataBase>
		static T GetComponentData(const size_t& index);
		template<typename T = ComponentDataBase>
		static bool HasComponentData(const size_t& index);


		template <typename T = PrivateComponentBase>
		static std::unique_ptr<T>& GetPrivateComponent(const Entity& entity);
		template <typename T = PrivateComponentBase>
		static void SetPrivateComponent(const Entity& entity, std::unique_ptr<T> value);
		template <typename T = PrivateComponentBase>
		static void RemovePrivateComponent(const Entity& entity);
		template <typename T = PrivateComponentBase>
		static bool HasPrivateComponent(const Entity& entity);

		static void RemovePrivateComponent(const Entity& entity, const size_t& typeId);

		static EntityQuery CreateEntityQuery();
		template<typename T = ComponentDataBase, typename... Ts>
		static void SetEntityQueryAllFilters(const EntityQuery& entityQuery, T arg, Ts... args);
		template<typename T = ComponentDataBase, typename... Ts>
		static void SetEntityQueryAnyFilters(const EntityQuery& entityQuery, T arg, Ts... args);
		template<typename T = ComponentDataBase, typename... Ts>
		static void SetEntityQueryNoneFilters(const EntityQuery& entityQuery, T arg, Ts... args);

		//For implicit parallel task dispatching
		template<typename T1 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase, typename T7 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase, typename T7 = ComponentDataBase, typename T8 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&)>& func, bool checkEnable = true);
		//For implicit parallel task dispatching
		template<typename T1 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&, T2&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&, T2&, T3&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase, typename T7 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&)>& func, bool checkEnable = true);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase, typename T7 = ComponentDataBase, typename T8 = ComponentDataBase>
		static void ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&)>& func, bool checkEnable = true);


		//For explicit parallel task dispatching
		template<typename T1 = ComponentDataBase>
		static std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> CreateParallelTask(const std::function<void(int i, Entity entity, T1&)>& func);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase>
		static std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> CreateParallelTask(const std::function<void(int i, Entity entity, T1&, T2&)>& func);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase>
		static std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> CreateParallelTask(const std::function<void(int i, Entity entity, T1&, T2&, T3&)>& func);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase>
		static std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> CreateParallelTask(const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&)>& func);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase>
		static std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> CreateParallelTask(const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&)>& func);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase>
		static std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> CreateParallelTask(const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&)>& func);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase, typename T7 = ComponentDataBase>
		static std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> CreateParallelTask(const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&)>& func);
		template<typename T1 = ComponentDataBase, typename T2 = ComponentDataBase, typename T3 = ComponentDataBase, typename T4 = ComponentDataBase, typename T5 = ComponentDataBase, typename T6 = ComponentDataBase, typename T7 = ComponentDataBase, typename T8 = ComponentDataBase>
		static std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> CreateParallelTask(const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&)>& func);

		static void ForAllEntities(const std::function<void(int i, Entity entity)>& func);
		static std::string GetEntityArchetypeName(const EntityArchetype& entityArchetype);
	};
#pragma endregion
#pragma region Functions
#pragma region Collectors

	template <typename T>
	bool EntityManager::CheckComponentTypes(T arg)
	{
		return std::is_standard_layout<T>::value;
	}

	template <typename T, typename ... Ts>
	bool EntityManager::CheckComponentTypes(T arg, Ts... args)
	{
		return std::is_standard_layout<T>::value && CheckComponentTypes(args...);
	}

	template<typename T>
	size_t EntityManager::CollectComponentTypes(std::vector<ComponentDataType>* componentTypes, T arg)
	{
		const auto type = Typeof<T>();
		componentTypes->push_back(type);
		return type.m_size;
	}

	template<typename T, typename ...Ts>
	size_t EntityManager::CollectComponentTypes(std::vector<ComponentDataType>* componentTypes, T arg, Ts ...args)
	{
		auto offset = CollectComponentTypes(componentTypes, args...);
		ComponentDataType type = Typeof<T>();
		componentTypes->push_back(type);
		return type.m_size + offset;
	}

	template<typename T, typename ...Ts>
	std::vector<ComponentDataType> EntityManager::CollectComponentTypes(T arg, Ts ...args)
	{
		auto retVal = std::vector<ComponentDataType>();
		retVal.push_back(Typeof<Transform>());
		retVal.push_back(Typeof<GlobalTransform>());
		CollectComponentTypes(&retVal, arg, args...);
		std::sort(retVal.begin() + 2, retVal.end(), ComponentTypeComparator);
		size_t offset = 0;
		EraseDuplicates(retVal);
		for (auto& i : retVal)
		{
			i.m_offset = offset;
			offset += i.m_size;
		}
		return retVal;
	}
#pragma endregion
#pragma region ForEachStorage
	template<typename T1>
	void EntityManager::ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&)>& func, bool checkEnable)
	{
		auto targetType1 = Typeof<T1>();
		const auto entityCount = storage.m_archetypeInfo->m_entityAliveCount;
		auto found1 = false;
		for (const auto& type : storage.m_archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == targetType1.m_typeId)
			{
				targetType1 = type;
				found1 = true;
			}
		}
		if (!found1) return;
		const auto capacity = storage.m_archetypeInfo->m_chunkCapacity;
		const auto* chunkArray = storage.m_chunkArray;
		const auto* entities = &chunkArray->Entities;
		std::vector<std::shared_future<void>> results;
		const auto threadSize = workers.Size();
		const auto threadLoad = entityCount / threadSize;
		const auto loadReminder = entityCount % threadSize;
		for (int threadIndex = 0; threadIndex < threadSize; threadIndex++)
		{
			results.push_back(
				workers.Push([=](int id)
					{
						for (int i = threadIndex * threadLoad; i < (threadIndex + 1) * threadLoad; i++) {
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder]
							);
						}
						if (threadIndex < loadReminder)
						{
							const int i = threadIndex + threadSize * threadLoad;
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder]
							);
						}
					}
			).share());
		}
		for (const auto& i : results) i.wait();

	}
	template<typename T1, typename T2>
	void EntityManager::ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&)>& func, bool checkEnable)
	{
		auto targetType1 = Typeof<T1>();
		auto targetType2 = Typeof<T2>();
		const auto entityCount = storage.m_archetypeInfo->m_entityAliveCount;
		bool found1 = false;
		bool found2 = false;
		for (const auto& type : storage.m_archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == targetType1.m_typeId)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.m_typeId == targetType2.m_typeId)
			{
				targetType2 = type;
				found2 = true;
			}
		}

		if (!found1 || !found2) return;
		const auto capacity = storage.m_archetypeInfo->m_chunkCapacity;
		const auto* chunkArray = storage.m_chunkArray;
		const auto* entities = &chunkArray->Entities;
		std::vector<std::shared_future<void>> results;
		const auto threadSize = workers.Size();
		const auto threadLoad = entityCount / threadSize;
		const auto loadReminder = entityCount % threadSize;
		for (int threadIndex = 0; threadIndex < threadSize; threadIndex++)
		{
			results.push_back(
				workers.Push([=](int id)
					{
						for (int i = threadIndex * threadLoad; i < (threadIndex + 1) * threadLoad; i++) {
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder]
							);
						}
						if (threadIndex < loadReminder)
						{
							const int i = threadIndex + threadSize * threadLoad;
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder]
							);
						}
					}
			).share());
		}
		for (const auto& i : results) i.wait();

	}
	template<typename T1, typename T2, typename T3>
	void EntityManager::ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&)>& func, bool checkEnable) {
		auto targetType1 = Typeof<T1>();
		auto targetType2 = Typeof<T2>();
		auto targetType3 = Typeof<T3>();
		const auto entityCount = storage.m_archetypeInfo->m_entityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		for (const auto& type : storage.m_archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == targetType1.m_typeId)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.m_typeId == targetType2.m_typeId)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.m_typeId == targetType3.m_typeId)
			{
				targetType3 = type;
				found3 = true;
			}
		}
		if (!found1 || !found2 || !found3) return;
		const auto capacity = storage.m_archetypeInfo->m_chunkCapacity;
		const auto* chunkArray = storage.m_chunkArray;
		const auto* entities = &chunkArray->Entities;
		std::vector<std::shared_future<void>> results;
		const auto threadSize = workers.Size();
		const auto threadLoad = entityCount / threadSize;
		const auto loadReminder = entityCount % threadSize;
		for (int threadIndex = 0; threadIndex < threadSize; threadIndex++)
		{
			results.push_back(
				workers.Push([=](int id)
					{
						for (int i = threadIndex * threadLoad; i < (threadIndex + 1) * threadLoad; i++) {
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder]
							);
						}
						if (threadIndex < loadReminder)
						{
							const int i = threadIndex + threadSize * threadLoad;
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder]
							);
						}
					}
			).share());
		}
		for (const auto& i : results) i.wait();

	}
	template<typename T1, typename T2, typename T3, typename T4>
	void EntityManager::ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&)>& func, bool checkEnable) {
		auto targetType1 = Typeof<T1>();
		auto targetType2 = Typeof<T2>();
		auto targetType3 = Typeof<T3>();
		auto targetType4 = Typeof<T4>();
		const auto entityCount = storage.m_archetypeInfo->m_entityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		for (const auto& type : storage.m_archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == targetType1.m_typeId)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.m_typeId == targetType2.m_typeId)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.m_typeId == targetType3.m_typeId)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.m_typeId == targetType4.m_typeId)
			{
				targetType4 = type;
				found4 = true;
			}
		}
		if (!found1 || !found2 || !found3 || !found4) return;
		const auto capacity = storage.m_archetypeInfo->m_chunkCapacity;
		const auto* chunkArray = storage.m_chunkArray;
		const auto* entities = &chunkArray->Entities;
		std::vector<std::shared_future<void>> results;
		const auto threadSize = workers.Size();
		const auto threadLoad = entityCount / threadSize;
		const auto loadReminder = entityCount % threadSize;
		for(int threadIndex = 0; threadIndex < threadSize; threadIndex++)
		{
			results.push_back(
				workers.Push([=](int id)
					{
						for (int i = threadIndex * threadLoad; i < (threadIndex + 1) * threadLoad; i++) {
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T1 copy1 = address1[remainder];
							T2 copy2 = address2[remainder];
							T3 copy3 = address3[remainder];
							T4 copy4 = address4[remainder];
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								copy1,
								copy2,
								copy3,
								copy4
							);
							address1[remainder] = copy1;
							address2[remainder] = copy2;
							address3[remainder] = copy3;
							address4[remainder] = copy4;
						}
						
						if(threadIndex < loadReminder)
						{
							const int i = threadIndex + threadSize * threadLoad;
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T1 copy1 = address1[remainder];
							T2 copy2 = address2[remainder];
							T3 copy3 = address3[remainder];
							T4 copy4 = address4[remainder];
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								copy1,
								copy2,
								copy3,
								copy4
							);
							address1[remainder] = copy1;
							address2[remainder] = copy2;
							address3[remainder] = copy3;
							address4[remainder] = copy4;
						}
					}
			).share());
		}
		for (const auto& i : results) i.wait();
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	void EntityManager::ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&)>& func, bool checkEnable) {
		auto targetType1 = Typeof<T1>();
		auto targetType2 = Typeof<T2>();
		auto targetType3 = Typeof<T3>();
		auto targetType4 = Typeof<T4>();
		auto targetType5 = Typeof<T5>();
		const auto entityCount = storage.m_archetypeInfo->m_entityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		bool found5 = false;
		for (const auto& type : storage.m_archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == targetType1.m_typeId)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.m_typeId == targetType2.m_typeId)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.m_typeId == targetType3.m_typeId)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.m_typeId == targetType4.m_typeId)
			{
				targetType4 = type;
				found4 = true;
			}
			else if (type.m_typeId == targetType5.m_typeId)
			{
				targetType5 = type;
				found5 = true;
			}
		}
		if (!found1 || !found2 || !found3 || !found4 || !found5) return;
		const auto capacity = storage.m_archetypeInfo->m_chunkCapacity;
		const auto* chunkArray = storage.m_chunkArray;
		const auto* entities = &chunkArray->Entities;
		std::vector<std::shared_future<void>> results;
		const auto threadSize = workers.Size();
		const auto threadLoad = entityCount / threadSize;
		const auto loadReminder = entityCount % threadSize;
		for (int threadIndex = 0; threadIndex < threadSize; threadIndex++)
		{
			results.push_back(
				workers.Push([=](int id)
					{
						for (int i = threadIndex * threadLoad; i < (threadIndex + 1) * threadLoad; i++) {
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T5* address5 = reinterpret_cast<T5*>(data + targetType5.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder],
								address4[remainder],
								address5[remainder]
							);
						}
						if (threadIndex < loadReminder)
						{
							const int i = threadIndex + threadSize * threadLoad;
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T5* address5 = reinterpret_cast<T5*>(data + targetType5.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder],
								address4[remainder],
								address5[remainder]
							);
						}
					}
			).share());
		}
		for (const auto& i : results) i.wait();
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	void EntityManager::ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&)>& func, bool checkEnable) {
		auto targetType1 = Typeof<T1>();
		auto targetType2 = Typeof<T2>();
		auto targetType3 = Typeof<T3>();
		auto targetType4 = Typeof<T4>();
		auto targetType5 = Typeof<T5>();
		auto targetType6 = Typeof<T6>();
		const auto entityCount = storage.m_archetypeInfo->m_entityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		bool found5 = false;
		bool found6 = false;
		for (const auto& type : storage.m_archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == targetType1.m_typeId)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.m_typeId == targetType2.m_typeId)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.m_typeId == targetType3.m_typeId)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.m_typeId == targetType4.m_typeId)
			{
				targetType4 = type;
				found4 = true;
			}
			else if (type.m_typeId == targetType5.m_typeId)
			{
				targetType5 = type;
				found5 = true;
			}
			else if (type.m_typeId == targetType6.m_typeId)
			{
				targetType6 = type;
				found6 = true;
			}
		}
		if (!found1 || !found2 || !found3 || !found4 || !found5 || !found6) return;
		const auto capacity = storage.m_archetypeInfo->m_chunkCapacity;
		const auto* chunkArray = storage.m_chunkArray;
		const auto* entities = &chunkArray->Entities;
		std::vector<std::shared_future<void>> results;
		const auto threadSize = workers.Size();
		const auto threadLoad = entityCount / threadSize;
		const auto loadReminder = entityCount % threadSize;
		for (int threadIndex = 0; threadIndex < threadSize; threadIndex++)
		{
			results.push_back(
				workers.Push([=](int id)
					{
						for (int i = threadIndex * threadLoad; i < (threadIndex + 1) * threadLoad; i++) {
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T5* address5 = reinterpret_cast<T5*>(data + targetType5.m_offset * capacity);
							T6* address6 = reinterpret_cast<T6*>(data + targetType6.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder],
								address4[remainder],
								address5[remainder],
								address6[remainder]
							);
						}
						if (threadIndex < loadReminder)
						{
							const int i = threadIndex + threadSize * threadLoad;
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T5* address5 = reinterpret_cast<T5*>(data + targetType5.m_offset * capacity);
							T6* address6 = reinterpret_cast<T6*>(data + targetType6.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder],
								address4[remainder],
								address5[remainder],
								address6[remainder]
							);
						}
					}
			).share());
		}
		for (const auto& i : results) i.wait();
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	void EntityManager::ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&)>& func, bool checkEnable) {
		auto targetType1 = Typeof<T1>();
		auto targetType2 = Typeof<T2>();
		auto targetType3 = Typeof<T3>();
		auto targetType4 = Typeof<T4>();
		auto targetType5 = Typeof<T5>();
		auto targetType6 = Typeof<T6>();
		auto targetType7 = Typeof<T7>();
		const auto entityCount = storage.m_archetypeInfo->m_entityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		bool found5 = false;
		bool found6 = false;
		bool found7 = false;
		for (const auto& type : storage.m_archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == targetType1.m_typeId)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.m_typeId == targetType2.m_typeId)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.m_typeId == targetType3.m_typeId)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.m_typeId == targetType4.m_typeId)
			{
				targetType4 = type;
				found4 = true;
			}
			else if (type.m_typeId == targetType5.m_typeId)
			{
				targetType5 = type;
				found5 = true;
			}
			else if (type.m_typeId == targetType6.m_typeId)
			{
				targetType6 = type;
				found6 = true;
			}
			else if (type.m_typeId == targetType7.m_typeId)
			{
				targetType7 = type;
				found7 = true;
			}
		}
		if (!found1 || !found2 || !found3 || !found4 || !found5 || !found6 || !found7) return;
		const auto capacity = storage.m_archetypeInfo->m_chunkCapacity;
		const auto* chunkArray = storage.m_chunkArray;
		const auto* entities = &chunkArray->Entities;
		std::vector<std::shared_future<void>> results;
		const auto threadSize = workers.Size();
		const auto threadLoad = entityCount / threadSize;
		const auto loadReminder = entityCount % threadSize;
		for (int threadIndex = 0; threadIndex < threadSize; threadIndex++)
		{
			results.push_back(
				workers.Push([=](int id)
					{
						for (int i = threadIndex * threadLoad; i < (threadIndex + 1) * threadLoad; i++) {
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T5* address5 = reinterpret_cast<T5*>(data + targetType5.m_offset * capacity);
							T6* address6 = reinterpret_cast<T6*>(data + targetType6.m_offset * capacity);
							T7* address7 = reinterpret_cast<T7*>(data + targetType7.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder],
								address4[remainder],
								address5[remainder],
								address6[remainder],
								address7[remainder]
							);
						}
						if (threadIndex < loadReminder)
						{
							const int i = threadIndex + threadSize * threadLoad;
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T5* address5 = reinterpret_cast<T5*>(data + targetType5.m_offset * capacity);
							T6* address6 = reinterpret_cast<T6*>(data + targetType6.m_offset * capacity);
							T7* address7 = reinterpret_cast<T7*>(data + targetType7.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder],
								address4[remainder],
								address5[remainder],
								address6[remainder],
								address7[remainder]
							);
						}
					}
			).share());
		}
		for (const auto& i : results) i.wait();
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	void EntityManager::ForEachStorage(ThreadPool& workers, const EntityComponentDataStorage& storage, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&)>& func, bool checkEnable) {
		auto targetType1 = Typeof<T1>();
		auto targetType2 = Typeof<T2>();
		auto targetType3 = Typeof<T3>();
		auto targetType4 = Typeof<T4>();
		auto targetType5 = Typeof<T5>();
		auto targetType6 = Typeof<T6>();
		auto targetType7 = Typeof<T7>();
		auto targetType8 = Typeof<T8>();
		const auto entityCount = storage.m_archetypeInfo->m_entityAliveCount;
		bool found1 = false;
		bool found2 = false;
		bool found3 = false;
		bool found4 = false;
		bool found5 = false;
		bool found6 = false;
		bool found7 = false;
		bool found8 = false;
		for (const auto& type : storage.m_archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == targetType1.m_typeId)
			{
				targetType1 = type;
				found1 = true;
			}
			else if (type.m_typeId == targetType2.m_typeId)
			{
				targetType2 = type;
				found2 = true;
			}
			else if (type.m_typeId == targetType3.m_typeId)
			{
				targetType3 = type;
				found3 = true;
			}
			else if (type.m_typeId == targetType4.m_typeId)
			{
				targetType4 = type;
				found4 = true;
			}
			else if (type.m_typeId == targetType5.m_typeId)
			{
				targetType5 = type;
				found5 = true;
			}
			else if (type.m_typeId == targetType6.m_typeId)
			{
				targetType6 = type;
				found6 = true;
			}
			else if (type.m_typeId == targetType7.m_typeId)
			{
				targetType7 = type;
				found7 = true;
			}
			else if (type.m_typeId == targetType8.m_typeId)
			{
				targetType8 = type;
				found8 = true;
			}
		}
		if (!found1 || !found2 || !found3 || !found4 || !found5 || !found6 || !found7 || !found8) return;
		const auto capacity = storage.m_archetypeInfo->m_chunkCapacity;
		const auto* chunkArray = storage.m_chunkArray;
		const auto* entities = &chunkArray->Entities;
		std::vector<std::shared_future<void>> results;
		const auto threadSize = workers.Size();
		const auto threadLoad = entityCount / threadSize;
		const auto loadReminder = entityCount % threadSize;
		for (int threadIndex = 0; threadIndex < threadSize; threadIndex++)
		{
			results.push_back(
				workers.Push([=](int id)
					{
						for (int i = threadIndex * threadLoad; i < (threadIndex + 1) * threadLoad; i++) {
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T5* address5 = reinterpret_cast<T5*>(data + targetType5.m_offset * capacity);
							T6* address6 = reinterpret_cast<T6*>(data + targetType6.m_offset * capacity);
							T7* address7 = reinterpret_cast<T7*>(data + targetType7.m_offset * capacity);
							T8* address8 = reinterpret_cast<T8*>(data + targetType8.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder],
								address4[remainder],
								address5[remainder],
								address6[remainder],
								address7[remainder],
								address8[remainder]
							);
						}
						if (threadIndex < loadReminder)
						{
							const int i = threadIndex + threadSize * threadLoad;
							const auto chunkIndex = i / capacity;
							const auto remainder = i % capacity;
							auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
							T1* address1 = reinterpret_cast<T1*>(data + targetType1.m_offset * capacity);
							T2* address2 = reinterpret_cast<T2*>(data + targetType2.m_offset * capacity);
							T3* address3 = reinterpret_cast<T3*>(data + targetType3.m_offset * capacity);
							T4* address4 = reinterpret_cast<T4*>(data + targetType4.m_offset * capacity);
							T5* address5 = reinterpret_cast<T5*>(data + targetType5.m_offset * capacity);
							T6* address6 = reinterpret_cast<T6*>(data + targetType6.m_offset * capacity);
							T7* address7 = reinterpret_cast<T7*>(data + targetType7.m_offset * capacity);
							T8* address8 = reinterpret_cast<T8*>(data + targetType8.m_offset * capacity);
							const auto entity = entities->at(i);
							if (checkEnable && !GetInstance().m_entityInfos->at(entity.m_index).m_enabled) return;
							func(static_cast<int>(i), entity,
								address1[remainder],
								address2[remainder],
								address3[remainder],
								address4[remainder],
								address5[remainder],
								address6[remainder],
								address7[remainder],
								address8[remainder]
							);
						}
					}
			).share());
		}
		for (const auto& i : results) i.wait();
	}
#pragma endregion
#pragma region Others
	template<typename T>
	void EntityManager::GetComponentDataArrayStorage(const EntityComponentDataStorage& storage, std::vector<T>& container)
	{
		auto targetType = Typeof<T>();
		for (const auto& type : storage.m_archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == targetType.m_typeId)
			{
				targetType = type;
				size_t amount = storage.m_archetypeInfo->m_entityAliveCount;
				if (amount == 0) return;
				container.resize(container.size() + amount);
				const auto capacity = storage.m_archetypeInfo->m_chunkCapacity;
				const auto chunkAmount = amount / capacity;
				const auto remainAmount = amount % capacity;
				for (size_t i = 0; i < chunkAmount; i++) {
					memcpy(&container.at(container.size() - remainAmount - capacity * (chunkAmount - i)), reinterpret_cast<void*>(static_cast<char*>(storage.m_chunkArray->Chunks[i].m_data) + capacity * targetType.m_offset), capacity * targetType.m_size);
				}
				if (remainAmount > 0) memcpy(&container.at(container.size() - remainAmount), reinterpret_cast<void*>(static_cast<char*>(storage.m_chunkArray->Chunks[chunkAmount].m_data) + capacity * targetType.m_offset), remainAmount * targetType.m_size);
			}
		}
	}

	template<typename T, typename ...Ts>
	EntityArchetype EntityManager::CreateEntityArchetype(const std::string& name, T arg, Ts ...args)
	{
		EntityArchetype retVal = EntityArchetype();
		if (!CheckComponentTypes(arg, args...))
		{
			Debug::Error("CreateEntityArchetype failed: Standard Layout");
			return retVal;
		}
		auto* info = new EntityArchetypeInfo();
		info->m_name = name;
		info->m_entityCount = 0;
		info->m_componentTypes = CollectComponentTypes(arg, args...);
		info->m_entitySize = info->m_componentTypes.back().m_offset + info->m_componentTypes.back().m_size;
		info->m_chunkCapacity = GetInstance().m_archetypeChunkSize / info->m_entitySize;
		int duplicateIndex = -1;
		for (size_t i = 1; i < GetInstance().m_entityComponentStorage->size(); i++) {
			EntityArchetypeInfo* compareInfo = GetInstance().m_entityComponentStorage->at(i).m_archetypeInfo;
			if (info->m_chunkCapacity != compareInfo->m_chunkCapacity) continue;
			if (info->m_entitySize != compareInfo->m_entitySize) continue;
			bool typeCheck = true;

			for (auto& componentType : info->m_componentTypes)
			{
				if (!compareInfo->HasType(componentType.m_typeId)) typeCheck = false;
			}
			if (typeCheck) {
				duplicateIndex = compareInfo->m_index;
				delete info;
				info = compareInfo;
				break;
			}
		}
		if (duplicateIndex == -1) {
			retVal.m_index = GetInstance().m_entityComponentStorage->size();
			info->m_index = retVal.m_index;
			GetInstance().m_entityComponentStorage->push_back(EntityComponentDataStorage(info, new ComponentDataChunkArray()));
		}
		else {
			retVal.m_index = duplicateIndex;
		}
		for (size_t i = 0; i < GetInstance().m_entityQueryInfos->size(); i++) {
			RefreshEntityQueryInfos(i);
		}
		return retVal;
	}
#pragma endregion
#pragma region GetSetHas
	template <typename T>
	void EntityManager::AddComponentData(const Entity& entity, const T& value)
	{
		if (!entity.IsValid()) return;
		const auto id = typeid(T).hash_code();
		if (id == typeid(Transform).hash_code())
		{
			return;
		}
		if (id == typeid(GlobalTransform).hash_code())
		{
			return;
		}
		auto& entityInfo = GetInstance().m_entityInfos->at(entity.m_index);
#pragma region Check if componentdata already exists. If yes, go to SetComponentData
		if (GetInstance().m_entities->at(entity.m_index) != entity) {
			Debug::Error("Entity version mismatch!");
			return;
		}
		EntityArchetypeInfo* archetypeInfo = GetInstance().m_entityComponentStorage->at(entityInfo.m_archetypeInfoIndex).m_archetypeInfo;
		const auto chunkIndex = entityInfo.m_chunkArrayIndex / archetypeInfo->m_chunkCapacity;
		const auto chunkPointer = entityInfo.m_chunkArrayIndex % archetypeInfo->m_chunkCapacity;
		ComponentDataChunk chunk = GetInstance().m_entityComponentStorage->at(entityInfo.m_archetypeInfoIndex).m_chunkArray->Chunks[chunkIndex];
		
		for (const auto& type : archetypeInfo->m_componentTypes)
		{
			if (type.m_typeId == id)
			{
				chunk.SetData<T>(static_cast<size_t>(type.m_offset * archetypeInfo->m_chunkCapacity + chunkPointer * type.m_size), value);
				return;
			}
		}
#pragma endregion
#pragma region If not exist, we first need to create a new archetype
		EntityArchetypeInfo* newArchetypeInfo = new EntityArchetypeInfo();
		newArchetypeInfo->m_name = "New archetype";
		newArchetypeInfo->m_entityCount = 0;
		newArchetypeInfo->m_componentTypes = archetypeInfo->m_componentTypes;
		newArchetypeInfo->m_componentTypes.push_back(Typeof<T>());
#pragma region Sort types and check duplicate
		std::sort(newArchetypeInfo->m_componentTypes.begin() + 2, newArchetypeInfo->m_componentTypes.end(), ComponentTypeComparator);
		size_t offset = 0;
		ComponentDataType prev = newArchetypeInfo->m_componentTypes[0];
		//Erase duplicates
		EraseDuplicates(newArchetypeInfo->m_componentTypes);
		for (auto& i : newArchetypeInfo->m_componentTypes)
		{
			i.m_offset = offset;
			offset += i.m_size;
		}

		newArchetypeInfo->m_entitySize = newArchetypeInfo->m_componentTypes.back().m_offset + newArchetypeInfo->m_componentTypes.back().m_size;
		newArchetypeInfo->m_chunkCapacity = GetInstance().m_archetypeChunkSize / newArchetypeInfo->m_entitySize;
		int duplicateIndex = -1;
		for (size_t i = 1; i < GetInstance().m_entityComponentStorage->size(); i++) {
			EntityArchetypeInfo* compareInfo = GetInstance().m_entityComponentStorage->at(i).m_archetypeInfo;
			if (newArchetypeInfo->m_chunkCapacity != compareInfo->m_chunkCapacity) continue;
			if (newArchetypeInfo->m_entitySize != compareInfo->m_entitySize) continue;
			bool typeCheck = true;
			for (size_t j = 0; j < newArchetypeInfo->m_componentTypes.size(); j++) {
				if (!compareInfo->HasType(newArchetypeInfo->m_componentTypes[j].m_typeId)) typeCheck = false;
			}
			if (typeCheck) {
				duplicateIndex = compareInfo->m_index;
				delete newArchetypeInfo;
				newArchetypeInfo = compareInfo;
				break;
			}
		}
#pragma endregion
		EntityArchetype archetype;
		if (duplicateIndex == -1) {
			archetype.m_index = GetInstance().m_entityComponentStorage->size();
			newArchetypeInfo->m_index = archetype.m_index;
			GetInstance().m_entityComponentStorage->push_back(EntityComponentDataStorage(newArchetypeInfo, new ComponentDataChunkArray()));
		}
		else {
			archetype.m_index = duplicateIndex;
		}
#pragma endregion
#pragma region Create new Entity with new archetype.
		Entity newEntity = CreateEntity(archetype);
		//Transfer component data
		for (const auto& type : archetypeInfo->m_componentTypes)
		{
			SetComponentData(newEntity, type.m_typeId, type.m_size, GetComponentDataPointer(entity, type.m_typeId));
		}
		newEntity.SetComponentData(value);
		//5. Swap entity.
		EntityInfo& newEntityInfo = GetInstance().m_entityInfos->at(newEntity.m_index);
		const auto tempArchetypeInfoIndex = newEntityInfo.m_archetypeInfoIndex;
		const auto tempChunkArrayIndex = newEntityInfo.m_chunkArrayIndex;
		newEntityInfo.m_archetypeInfoIndex = entityInfo.m_archetypeInfoIndex;
		newEntityInfo.m_chunkArrayIndex = entityInfo.m_chunkArrayIndex;
		entityInfo.m_archetypeInfoIndex = tempArchetypeInfoIndex;
		entityInfo.m_chunkArrayIndex = tempChunkArrayIndex;
		//Apply to chunk.
		GetInstance().m_entityComponentStorage->at(entityInfo.m_archetypeInfoIndex).m_chunkArray->Entities[entityInfo.m_chunkArrayIndex] = entity;
		GetInstance().m_entityComponentStorage->at(newEntityInfo.m_archetypeInfoIndex).m_chunkArray->Entities[newEntityInfo.m_chunkArrayIndex] = newEntity;
		DeleteEntity(newEntity);
#pragma endregion
		for (size_t i = 0; i < GetInstance().m_entityQueryInfos->size(); i++) {
			RefreshEntityQueryInfos(i);
		}
	}

	template <typename T>
	T EntityManager::RemoveComponentData(const Entity& entity)
	{
		if (!entity.IsValid()) return T();
		const auto id = typeid(T).hash_code();
		if (id == typeid(Transform).hash_code())
		{
			return T();
		}
		if (id == typeid(GlobalTransform).hash_code())
		{
			return T();
		}
		EntityInfo& entityInfo = GetInstance().m_entityInfos->at(entity.m_index);
		if (GetInstance().m_entities->at(entity.m_index) != entity) {
			Debug::Error("Entity version mismatch!");
			return T();
		}
		EntityArchetypeInfo* archetypeInfo = GetInstance().m_entityComponentStorage->at(entityInfo.m_archetypeInfoIndex).m_archetypeInfo;
		if (archetypeInfo->m_componentTypes.size() <= 1)
		{
			Debug::Error("Remove Component Data failed: Entity must have at least 1 data component!");
			return T();
		}
#pragma region Create new archetype
		EntityArchetypeInfo* newArchetypeInfo = new EntityArchetypeInfo();
		newArchetypeInfo->m_name = "New archetype";
		newArchetypeInfo->m_entityCount = 0;
		newArchetypeInfo->m_componentTypes = archetypeInfo->m_componentTypes;
		bool found = false;
		for (int i = 0; i < newArchetypeInfo->m_componentTypes.size(); i++)
		{
			if (newArchetypeInfo->m_componentTypes[i].m_typeId == id)
			{
				newArchetypeInfo->m_componentTypes.erase(newArchetypeInfo->m_componentTypes.begin() + i);
				found = true;
				break;
			}
		}
		if (!found)
		{
			delete newArchetypeInfo;
			Debug::Error("Failed to remove component data: Component not found");
			return T();
		}
#pragma region Sort types
		size_t offset = 0;
		for (auto& i : newArchetypeInfo->m_componentTypes)
		{
			i.m_offset = offset;
			offset += i.m_size;
		}

		newArchetypeInfo->m_entitySize = newArchetypeInfo->m_componentTypes.back().m_offset + newArchetypeInfo->m_componentTypes.back().m_size;
		newArchetypeInfo->m_chunkCapacity = GetInstance().m_archetypeChunkSize / newArchetypeInfo->m_entitySize;
		int duplicateIndex = -1;
		for (size_t i = 1; i < GetInstance().m_entityComponentStorage->size(); i++) {
			EntityArchetypeInfo* compareInfo = GetInstance().m_entityComponentStorage->at(i).m_archetypeInfo;
			if (newArchetypeInfo->m_chunkCapacity != compareInfo->m_chunkCapacity) continue;
			if (newArchetypeInfo->m_entitySize != compareInfo->m_entitySize) continue;
			bool typeCheck = true;
			for (size_t j = 0; j < newArchetypeInfo->m_componentTypes.size(); j++) {
				if (!compareInfo->HasType(newArchetypeInfo->m_componentTypes[j].m_typeId)) typeCheck = false;
			}
			if (typeCheck) {
				duplicateIndex = compareInfo->m_index;
				delete newArchetypeInfo;
				newArchetypeInfo = compareInfo;
				break;
			}
		}
#pragma endregion
		EntityArchetype archetype;
		if (duplicateIndex == -1) {
			archetype.m_index = GetInstance().m_entityComponentStorage->size();
			newArchetypeInfo->m_index = archetype.m_index;
			GetInstance().m_entityComponentStorage->push_back(EntityComponentDataStorage(newArchetypeInfo, new ComponentDataChunkArray()));
		}
		else {
			archetype.m_index = duplicateIndex;
		}
#pragma endregion
#pragma region Create new Entity with new archetype
		const Entity newEntity = CreateEntity(archetype);
		//Transfer component data
		for (const auto& type : newArchetypeInfo->m_componentTypes)
		{
			SetComponentData(newEntity, type.m_typeId, type.m_size, GetComponentDataPointer(entity, type.m_typeId));
		}
		T retVal = entity.GetComponentData<T>();
		//5. Swap entity.
		EntityInfo& newEntityInfo = GetInstance().m_entityInfos->at(newEntity.m_index);
		const auto tempArchetypeInfoIndex = newEntityInfo.m_archetypeInfoIndex;
		const auto tempChunkArrayIndex = newEntityInfo.m_chunkArrayIndex;
		newEntityInfo.m_archetypeInfoIndex = entityInfo.m_archetypeInfoIndex;
		newEntityInfo.m_chunkArrayIndex = entityInfo.m_chunkArrayIndex;
		entityInfo.m_archetypeInfoIndex = tempArchetypeInfoIndex;
		entityInfo.m_chunkArrayIndex = tempChunkArrayIndex;
		//Apply to chunk.
		GetInstance().m_entityComponentStorage->at(entityInfo.m_archetypeInfoIndex).m_chunkArray->Entities[entityInfo.m_chunkArrayIndex] = entity;
		GetInstance().m_entityComponentStorage->at(newEntityInfo.m_archetypeInfoIndex).m_chunkArray->Entities[newEntityInfo.m_chunkArrayIndex] = newEntity;
		DeleteEntity(newEntity);
#pragma endregion
		for (size_t i = 0; i < GetInstance().m_entityQueryInfos->size(); i++) {
			RefreshEntityQueryInfos(i);
		}
		return retVal;
	}



	template<typename T>
	void EntityManager::SetComponentData(const Entity& entity, const T& value)
	{
		if (!entity.IsValid()) return;
		EntityInfo& info = GetInstance().m_entityInfos->at(entity.m_index);

		if (GetInstance().m_entities->at(entity.m_index) == entity) {
			EntityArchetypeInfo* chunkInfo = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_archetypeInfo;
			const size_t chunkIndex = info.m_chunkArrayIndex / chunkInfo->m_chunkCapacity;
			const size_t chunkPointer = info.m_chunkArrayIndex % chunkInfo->m_chunkCapacity;
			ComponentDataChunk chunk = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_chunkArray->Chunks[chunkIndex];
			const size_t id = typeid(T).hash_code();
			if (id == typeid(Transform).hash_code())
			{
				const auto& type = chunkInfo->m_componentTypes[0];
				chunk.SetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size), value);
				return;
			}
			if (id == typeid(GlobalTransform).hash_code())
			{
				const auto& type = chunkInfo->m_componentTypes[1];
				chunk.SetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size), value);
				return;
			}
			for (const auto& type : chunkInfo->m_componentTypes)
			{
				if (type.m_typeId == id)
				{
					chunk.SetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size), value);
					return;
				}
			}
			Debug::Log("ComponentData doesn't exist");
			return;
		}
		Debug::Error("Entity version mismatch!");
	}
	template<typename T>
	void EntityManager::SetComponentData(const size_t& index, const T& value)
	{
		if (index > GetInstance().m_entityInfos->size()) return;
		EntityInfo& info = GetInstance().m_entityInfos->at(index);

		if (GetInstance().m_entities->at(index).m_version != 0) {
			EntityArchetypeInfo* chunkInfo = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_archetypeInfo;
			const size_t chunkIndex = info.m_chunkArrayIndex / chunkInfo->m_chunkCapacity;
			const size_t chunkPointer = info.m_chunkArrayIndex % chunkInfo->m_chunkCapacity;
			ComponentDataChunk chunk = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_chunkArray->Chunks[chunkIndex];
			const size_t id = typeid(T).hash_code();
			if (id == typeid(Transform).hash_code())
			{
				const auto& type = chunkInfo->m_componentTypes[0];
				chunk.SetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size), value);
				return;
			}
			if (id == typeid(GlobalTransform).hash_code())
			{
				const auto& type = chunkInfo->m_componentTypes[1];
				chunk.SetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size), value);
				return;
			}
			for (const auto& type : chunkInfo->m_componentTypes)
			{
				if (type.m_typeId == id)
				{
					chunk.SetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size), value);
					return;
				}
			}
			Debug::Log("ComponentData doesn't exist");
			return;
		}
		Debug::Error("Entity already deleted!");
	}
	template<typename T>
	T EntityManager::GetComponentData(const Entity& entity)
	{
		if (!entity.IsValid()) return T();
		EntityInfo& info = GetInstance().m_entityInfos->at(entity.m_index);
		if (GetInstance().m_entities->at(entity.m_index) == entity) {
			EntityArchetypeInfo* chunkInfo = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_archetypeInfo;
			const size_t chunkIndex = info.m_chunkArrayIndex / chunkInfo->m_chunkCapacity;
			const size_t chunkPointer = info.m_chunkArrayIndex % chunkInfo->m_chunkCapacity;
			ComponentDataChunk chunk = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_chunkArray->Chunks[chunkIndex];
			const size_t id = typeid(T).hash_code();
			if (id == typeid(Transform).hash_code())
			{
				const auto& type = chunkInfo->m_componentTypes[0];
				return chunk.GetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size));
			}
			if (id == typeid(GlobalTransform).hash_code())
			{
				const auto& type = chunkInfo->m_componentTypes[1];
				return chunk.GetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size));
			}
			for (const auto& type : chunkInfo->m_componentTypes)
			{
				if (type.m_typeId == id)
				{
					return chunk.GetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size));
				}
			}
			Debug::Log("ComponentData doesn't exist");
			return T();
		}
		Debug::Error("Entity version mismatch!");
		return T();
	}
	template<typename T>
	bool EntityManager::HasComponentData(const Entity& entity)
	{
		if (!entity.IsValid()) return false;
		EntityInfo& info = GetInstance().m_entityInfos->at(entity.m_index);
		if (GetInstance().m_entities->at(entity.m_index) == entity) {
			EntityArchetypeInfo* chunkInfo = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_archetypeInfo;
			const size_t id = typeid(T).hash_code();
			if (id == typeid(Transform).hash_code())
			{
				return true;
			}
			if (id == typeid(GlobalTransform).hash_code())
			{
				return true;
			}
			for (const auto& type : chunkInfo->m_componentTypes)
			{
				if (type.m_typeId == id)
				{
					return true;
				}
			}
			return false;
		}
		Debug::Error("Entity version mismatch!");
		return false;
	}
	template<typename T>
	T EntityManager::GetComponentData(const size_t& index)
	{
		if (index > GetInstance().m_entityInfos->size()) return T();
		EntityInfo& info = GetInstance().m_entityInfos->at(index);
		if (GetInstance().m_entities->at(index).m_version != 0) {
			EntityArchetypeInfo* chunkInfo = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_archetypeInfo;
			const size_t chunkIndex = info.m_chunkArrayIndex / chunkInfo->m_chunkCapacity;
			const size_t chunkPointer = info.m_chunkArrayIndex % chunkInfo->m_chunkCapacity;
			ComponentDataChunk chunk = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_chunkArray->Chunks[chunkIndex];
			const size_t id = typeid(T).hash_code();
			if (id == typeid(Transform).hash_code())
			{
				const auto& type = chunkInfo->m_componentTypes[0];
				return chunk.GetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size));
			}
			if (id == typeid(GlobalTransform).hash_code())
			{
				const auto& type = chunkInfo->m_componentTypes[1];
				return chunk.GetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size));
			}
			for (const auto& type : chunkInfo->m_componentTypes)
			{
				if (type.m_typeId == id)
				{
					return chunk.GetData<T>(static_cast<size_t>(type.m_offset * chunkInfo->m_chunkCapacity + chunkPointer * type.m_size));
				}
			}
			Debug::Log("ComponentData doesn't exist");
			return T();
		}
		Debug::Error("Entity already deleted!");
		return T();
	}
	template<typename T>
	bool EntityManager::HasComponentData(const size_t& index)
	{
		if (index > GetInstance().m_entityInfos->size()) return false;
		EntityInfo& info = GetInstance().m_entityInfos->at(index);
		if (GetInstance().m_entities->at(index).m_version != 0) {
			EntityArchetypeInfo* chunkInfo = GetInstance().m_entityComponentStorage->at(info.m_archetypeInfoIndex).m_archetypeInfo;
			const size_t id = typeid(T).hash_code();
			if (id == typeid(Transform).hash_code())
			{
				return true;
			}
			if (id == typeid(GlobalTransform).hash_code())
			{
				return true;
			}
			for (const auto& type : chunkInfo->m_componentTypes)
			{
				if (type.m_typeId == id)
				{
					return true;
				}
			}
			return false;
		}
		Debug::Error("Entity already deleted!");
		return false;
	}

	template <typename T>
	std::unique_ptr<T>& EntityManager::GetPrivateComponent(const Entity& entity)
	{
		if (!entity.IsValid()) throw 0;
		int i = 0;
		for (auto& element : GetInstance().m_entityInfos->at(entity.m_index).m_privateComponentElements)
		{
			if (dynamic_cast<T*>(element.m_privateComponentData.get()))
			{
				return *static_cast<std::unique_ptr<T>*>(static_cast<void*>(&element.m_privateComponentData));
			}
			i++;
		}
		throw 0;
	}
	template <typename T>
	void EntityManager::SetPrivateComponent(const Entity& entity, std::unique_ptr<T> value)
	{
		if (!entity.IsValid()) return;
		value->m_enabled = true;
		bool found = false;
		size_t i = 0;
		for (auto& element : GetInstance().m_entityInfos->at(entity.m_index).m_privateComponentElements)
		{
			if (dynamic_cast<T*>(element.m_privateComponentData.get()))
			{
				found = true;
				element.m_privateComponentData = std::move(value);
				element.ResetOwner(entity);
				element.m_privateComponentData->Init();
			}
			i++;
		}
		if (!found)
		{
			GetInstance().m_entityPrivateComponentStorage->SetPrivateComponent<T>(entity);
			GetInstance().m_entityInfos->at(entity.m_index).m_privateComponentElements.push_back(PrivateComponentElement(std::string(typeid(T).name()), typeid(T).hash_code(), std::move(value), entity));
		}
	}
	template <typename T>
	void EntityManager::RemovePrivateComponent(const Entity& entity)
	{
		if (!entity.IsValid()) return;
		for (auto i = 0; i < GetInstance().m_entityInfos->at(entity.m_index).m_privateComponentElements.size(); i++)
		{
			if (dynamic_cast<T*>(GetInstance().m_entityInfos->at(entity.m_index).m_privateComponentElements[i].m_privateComponentData.get()))
			{
				GetInstance().m_entityPrivateComponentStorage->RemovePrivateComponent<T>(entity);
				GetInstance().m_entityInfos->at(entity.m_index).m_privateComponentElements.erase(GetInstance().m_entityInfos->at(entity.m_index).m_privateComponentElements.begin() + i);
			}
		}
	}

	template <typename T>
	bool EntityManager::HasPrivateComponent(const Entity& entity)
	{
		if (!entity.IsValid()) return false;
		for (auto& element : GetInstance().m_entityInfos->at(entity.m_index).m_privateComponentElements)
		{
			if (dynamic_cast<T*>(element.m_privateComponentData.get()))
			{
				return true;
			}
		}
		return false;
	}

	template<typename T, typename ...Ts>
	void EntityManager::SetEntityQueryAllFilters(const EntityQuery& entityQuery, T arg, Ts ...args)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		GetInstance().m_entityQueryInfos->at(index).m_allComponentTypes = CollectComponentTypes(arg, args...);
		RefreshEntityQueryInfos(index);
	}

	template<typename T, typename ...Ts>
	void EntityManager::SetEntityQueryAnyFilters(const EntityQuery& entityQuery, T arg, Ts ...args)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		GetInstance().m_entityQueryInfos->at(index).m_anyComponentTypes = CollectComponentTypes(arg, args...);
		RefreshEntityQueryInfos(index);
	}

	template<typename T, typename ...Ts>
	void EntityManager::SetEntityQueryNoneFilters(const EntityQuery& entityQuery, T arg, Ts ...args)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		GetInstance().m_entityQueryInfos->at(index).m_noneComponentTypes = CollectComponentTypes(arg, args...);
		RefreshEntityQueryInfos(index);
	}
#pragma endregion
#pragma region For Each
	template<typename T1>
	void EntityManager::ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&)>& func, bool checkEnable)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			ForEachStorage(workers, i, func, checkEnable);
		}
	}
	template<typename T1, typename T2>
	void EntityManager::ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&)>& func, bool checkEnable) {
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			ForEachStorage(workers, i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3>
	void EntityManager::ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&)>& func, bool checkEnable) {
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			ForEachStorage(workers, i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4>
	void EntityManager::ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&)>& func, bool checkEnable) {
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			ForEachStorage(workers, i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5>
	void EntityManager::ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&)>& func, bool checkEnable) {
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			ForEachStorage(workers, i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	void EntityManager::ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&)>& func, bool checkEnable) {
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			ForEachStorage(workers, i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	void EntityManager::ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&)>& func, bool checkEnable) {
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			ForEachStorage(workers, i, func, checkEnable);
		}
	}
	template<typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	void EntityManager::ForEach(ThreadPool& workers, const EntityQuery& entityQuery, const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&)>& func, bool checkEnable) {
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			ForEachStorage(workers, i, func, checkEnable);
		}
	}

	template <typename T1>
	void EntityManager::ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&)>& func,
		bool checkEnable)
	{
		auto& manager = GetInstance();
		auto* storages = manager.m_entityComponentStorage;
		for (auto i = storages->begin() + 1; i < storages->end(); ++i) {
			ForEachStorage(workers, *i, func, checkEnable);
		}
	}

	template <typename T1, typename T2>
	void EntityManager::ForEach(ThreadPool& workers, const std::function<void(int i, Entity entity, T1&, T2&)>& func,
		bool checkEnable)
	{
		auto& manager = GetInstance();
		auto* storages = manager.m_entityComponentStorage;
		for (auto i = storages->begin() + 1; i < storages->end(); ++i) {
			ForEachStorage(workers, *i, func, checkEnable);
		}
	}

	template <typename T1, typename T2, typename T3>
	void EntityManager::ForEach(ThreadPool& workers,
		const std::function<void(int i, Entity entity, T1&, T2&, T3&)>& func, bool checkEnable)
	{
		auto& manager = GetInstance();
		auto* storages = manager.m_entityComponentStorage;
		for (auto i = storages->begin() + 1; i < storages->end(); ++i) {
			ForEachStorage(workers, *i, func, checkEnable);
		}
	}

	template <typename T1, typename T2, typename T3, typename T4>
	void EntityManager::ForEach(ThreadPool& workers,
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&)>& func, bool checkEnable)
	{
		auto& manager = GetInstance();
		auto* storages = manager.m_entityComponentStorage;
		for (auto i = storages->begin() + 1; i < storages->end(); ++i) {
			ForEachStorage(workers, *i, func, checkEnable);
		}
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	void EntityManager::ForEach(ThreadPool& workers,
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&)>& func, bool checkEnable)
	{
		auto& manager = GetInstance();
		auto* storages = manager.m_entityComponentStorage;
		for (auto i = storages->begin() + 1; i < storages->end(); ++i) {
			ForEachStorage(workers, *i, func, checkEnable);
		}
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	void EntityManager::ForEach(ThreadPool& workers,
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&)>& func, bool checkEnable)
	{
		auto& manager = GetInstance();
		auto* storages = manager.m_entityComponentStorage;
		for (auto i = storages->begin() + 1; i < storages->end(); ++i) {
			ForEachStorage(workers, *i, func, checkEnable);
		}
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	void EntityManager::ForEach(ThreadPool& workers,
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&)>& func, bool checkEnable)
	{
		auto& manager = GetInstance();
		auto* storages = manager.m_entityComponentStorage;
		for (auto i = storages->begin() + 1; i < storages->end(); ++i) {
			ForEachStorage(workers, *i, func, checkEnable);
		}
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	void EntityManager::ForEach(ThreadPool& workers,
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&)>& func, bool checkEnable)
	{
		auto& manager = GetInstance();
		auto* storages = manager.m_entityComponentStorage;
		for (auto i = storages->begin() + 1; i < storages->end(); ++i) {
			ForEachStorage(workers, *i, func, checkEnable);
		}
	}

	template <typename T1>
	std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> EntityManager::CreateParallelTask(
		const std::function<void(int i, Entity entity, T1&)>& func)
	{
		std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> task([func](const EntityQuery& entityQuery, bool checkEnable)
			{
				const size_t index = entityQuery.m_index;
				if (index > GetInstance().m_entityQueries->size()) {
					Debug::Error("EntityQuery not exist!");
					return;
				}
				for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
					ForEachStorage(i, func, checkEnable);
				}
			}
		);
		return task;
	}

	template <typename T1, typename T2>
	std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> EntityManager::CreateParallelTask(
		const std::function<void(int i, Entity entity, T1&, T2&)>& func)
	{
		std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> task([func](ThreadPool& workers, const EntityQuery& entityQuery, bool checkEnable)
			{
				const size_t index = entityQuery.m_index;
				if (index > GetInstance().m_entityQueries->size()) {
					Debug::Error("EntityQuery not exist!");
					return;
				}
				for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
					ForEachStorage(workers, i, func, checkEnable);
				}
			}
		);
		return task;
	}

	template <typename T1, typename T2, typename T3>
	std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> EntityManager::CreateParallelTask(
		const std::function<void(int i, Entity entity, T1&, T2&, T3&)>& func)
	{
		std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> task([func](ThreadPool& workers, const EntityQuery& entityQuery, bool checkEnable)
			{
				const size_t index = entityQuery.m_index;
				if (index > GetInstance().m_entityQueries->size()) {
					Debug::Error("EntityQuery not exist!");
					return;
				}
				for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
					ForEachStorage(workers, i, func, checkEnable);
				}
			}
		);
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4>
	std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> EntityManager::CreateParallelTask(
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&)>& func)
	{
		std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> task([func](ThreadPool& workers, const EntityQuery& entityQuery, bool checkEnable)
			{
				const size_t index = entityQuery.m_index;
				if (index > GetInstance().m_entityQueries->size()) {
					Debug::Error("EntityQuery not exist!");
					return;
				}
				for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
					ForEachStorage(workers, i, func, checkEnable);
				}
			}
		);
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5>
	std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> EntityManager::CreateParallelTask(
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&)>& func)
	{
		std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> task([func](ThreadPool& workers, const EntityQuery& entityQuery, bool checkEnable)
			{
				const size_t index = entityQuery.m_index;
				if (index > GetInstance().m_entityQueries->size()) {
					Debug::Error("EntityQuery not exist!");
					return;
				}
				for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
					ForEachStorage(workers, i, func, checkEnable);
				}
			}
		);
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6>
	std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> EntityManager::CreateParallelTask(
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&)>& func)
	{
		std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> task([func](ThreadPool& workers, const EntityQuery& entityQuery, bool checkEnable)
			{
				const size_t index = entityQuery.m_index;
				if (index > GetInstance().m_entityQueries->size()) {
					Debug::Error("EntityQuery not exist!");
					return;
				}
				for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
					ForEachStorage(workers, i, func, checkEnable);
				}
			}
		);
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7>
	std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> EntityManager::CreateParallelTask(
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&)>& func)
	{
		std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> task([func](ThreadPool& workers, const EntityQuery& entityQuery, bool checkEnable)
			{
				const size_t index = entityQuery.m_index;
				if (index > GetInstance().m_entityQueries->size()) {
					Debug::Error("EntityQuery not exist!");
					return;
				}
				for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
					ForEachStorage(workers, i, func, checkEnable);
				}
			}
		);
		return task;
	}

	template <typename T1, typename T2, typename T3, typename T4, typename T5, typename T6, typename T7, typename T8>
	std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> EntityManager::CreateParallelTask(
		const std::function<void(int i, Entity entity, T1&, T2&, T3&, T4&, T5&, T6&, T7&, T8&)>& func)
	{
		std::packaged_task<void(ThreadPool&, const EntityQuery&, bool)> task([func](ThreadPool& workers, const EntityQuery& entityQuery, bool checkEnable)
			{
				const size_t index = entityQuery.m_index;
				if (index > GetInstance().m_entityQueries->size()) {
					Debug::Error("EntityQuery not exist!");
					return;
				}
				for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
					ForEachStorage(workers, i, func, checkEnable);
				}
			}
		);
		return task;
	}
#pragma endregion
	template<typename T>
	void EntityManager::GetComponentDataArray(const EntityQuery& entityQuery, std::vector<T>& container)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			GetComponentDataArrayStorage(i, container);
		}
	}

	template <typename T1, typename T2>
	void EntityManager::GetComponentDataArray(const EntityQuery& entityQuery, std::vector<T1>& container,
		const std::function<bool(const T2&)>& filterFunc)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		std::vector<T2> componentDataList;
		std::vector<T1> targetDataList;
		GetComponentDataArray(entityQuery, componentDataList);
		GetComponentDataArray(entityQuery, targetDataList);
		if (targetDataList.size() != componentDataList.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = componentDataList.size();
		std::vector<std::vector<T1>> collectedDataLists;
		const auto threadSize = JobManager::PrimaryWorkers().Size();
		for (int i = 0; i < threadSize; i++) {
			collectedDataLists.push_back(std::vector<T1>());
		}
		for (int i = 0; i < collectedDataLists.size(); i++) {
			std::vector<T1>* collectedDataList = &collectedDataLists[i];
			futures.push_back(JobManager::PrimaryWorkers().Push([&targetDataList, &componentDataList, size, collectedDataList, i, filterFunc, threadSize](int id) {
				for (int j = 0; j < size / threadSize; j++) {
					if (filterFunc(componentDataList[j * threadSize + i])) {
						collectedDataList->push_back(targetDataList[j * threadSize + i]);
					}
				}
				}).share());
		}
		for (const auto& i : futures) i.wait();
		for (int i = 0; i < collectedDataLists.size(); i++) {
			auto listSize = collectedDataLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedDataLists[i].data(), listSize * sizeof(T1));
		}


		const size_t remainder = size % threadSize;
		for (int i = 0; i < remainder; i++) {
			if (filterFunc(componentDataList[size - remainder + i])) {
				container.push_back(targetDataList[size - remainder + i]);
			}
		}
	}

	template <typename T1, typename T2, typename T3>
	void EntityManager::GetComponentDataArray(const EntityQuery& entityQuery, std::vector<T1>& container,
		const std::function<bool(const T2&, const T3&)>& filterFunc)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		std::vector<T3> componentDataList2;
		std::vector<T2> componentDataList1;
		std::vector<T1> targetDataList;
		GetComponentDataArray(entityQuery, componentDataList2);
		GetComponentDataArray(entityQuery, componentDataList1);
		GetComponentDataArray(entityQuery, targetDataList);
		if (targetDataList.size() != componentDataList1.size() || componentDataList1.size() != componentDataList2.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = componentDataList1.size();
		std::vector<std::vector<T1>> collectedDataLists;
		const auto threadSize = JobManager::PrimaryWorkers().Size();
		for (int i = 0; i < threadSize; i++) {
			collectedDataLists.push_back(std::vector<T1>());
		}
		for (int i = 0; i < collectedDataLists.size(); i++) {
			std::vector<T1>* collectedDataList = &collectedDataLists[i];
			futures.push_back(JobManager::PrimaryWorkers().Push([&targetDataList, &componentDataList1, &componentDataList2, size, collectedDataList, i, filterFunc, threadSize](int id) {
				for (int j = 0; j < size / threadSize; j++) {
					if (filterFunc(componentDataList1[j * threadSize + i], componentDataList2[j * threadSize + i])) {
						collectedDataList->push_back(targetDataList[j * threadSize + i]);
					}
				}
				}).share());
		}
		for (const auto& i : futures) i.wait();
		for (int i = 0; i < collectedDataLists.size(); i++) {
			auto listSize = collectedDataLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedDataLists[i].data(), listSize * sizeof(T1));
		}


		const size_t remainder = size % threadSize;
		for (int i = 0; i < remainder; i++) {
			if (filterFunc(componentDataList1[size - remainder + i], componentDataList2[size - remainder + i])) {
				container.push_back(targetDataList[size - remainder + i]);
			}
		}
	}

	template<typename T1, typename T2>
	void EntityManager::GetComponentDataArray(const EntityQuery& entityQuery, const T1& filter, std::vector<T2>& container)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		std::vector<T1> componentDataList;
		std::vector<T2> targetDataList;
		GetComponentDataArray(entityQuery, componentDataList);
		GetComponentDataArray(entityQuery, targetDataList);
		if (targetDataList.size() != componentDataList.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = componentDataList.size();
		std::vector<std::vector<T2>> collectedDataLists;
		const auto threadSize = JobManager::PrimaryWorkers().Size();
		for (int i = 0; i < threadSize; i++) {
			collectedDataLists.push_back(std::vector<T2>());
		}
		for (int i = 0; i < collectedDataLists.size(); i++) {
			std::vector<T2>* collectedDataList = &collectedDataLists[i];
			futures.push_back(JobManager::PrimaryWorkers().Push([&targetDataList, &componentDataList, size, filter, collectedDataList, i, threadSize](int id) {
				for (int j = 0; j < size / threadSize; j++) {
					if (filter == componentDataList[j * threadSize + i]) {
						collectedDataList->push_back(targetDataList[j * threadSize + i]);
					}
				}
				}).share());
		}
		for (const auto& i : futures) i.wait();
		for (int i = 0; i < collectedDataLists.size(); i++) {
			auto listSize = collectedDataLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedDataLists[i].data(), listSize * sizeof(T2));
		}


		const size_t remainder = size % threadSize;
		for (int i = 0; i < remainder; i++) {
			if (filter == componentDataList[size - remainder + i]) {
				container.push_back(targetDataList[size - remainder + i]);
			}
		}
	}

	template <typename T1>
	void EntityManager::GetEntityArray(const EntityQuery& entityQuery, std::vector<Entity>& container,
		const std::function<bool(const Entity&, const T1&)>& filterFunc)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		std::vector<Entity> allEntities;
		std::vector<T1> componentDataList;
		GetEntityArray(entityQuery, allEntities);
		GetComponentDataArray(entityQuery, componentDataList);
		if (allEntities.size() != componentDataList.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = allEntities.size();
		std::vector<std::vector<Entity>> collectedEntityLists;
		const auto threadSize = JobManager::PrimaryWorkers().Size();
		for (int i = 0; i < threadSize; i++) {
			collectedEntityLists.push_back(std::vector<Entity>());
		}
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			std::vector<Entity>* collectedEntityList = &collectedEntityLists[i];
			futures.push_back(JobManager::PrimaryWorkers().Push([&allEntities, &componentDataList, size, collectedEntityList, i, filterFunc, threadSize](int id) {
				for (int j = 0; j < size / threadSize; j++) {
					if (filterFunc(allEntities[j * threadSize + i], componentDataList[j * threadSize + i])) {
						collectedEntityList->push_back(allEntities[j * threadSize + i]);
					}
				}
				}).share());
		}
		for (const auto& i : futures) i.wait();
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			const auto listSize = collectedEntityLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedEntityLists[i].data(), listSize * sizeof(Entity));
		}


		const size_t remainder = size % threadSize;
		for (int i = 0; i < remainder; i++) {
			if (filterFunc(allEntities[size - remainder + i], componentDataList[size - remainder + i])) {
				container.push_back(allEntities[size - remainder + i]);
			}
		}
	}

	template <typename T1, typename T2>
	void EntityManager::GetEntityArray(const EntityQuery& entityQuery, std::vector<Entity>& container,
		const std::function<bool(const Entity&, const T1&, const T2&)>& filterFunc)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		std::vector<Entity> allEntities;
		std::vector<T1> componentDataList1;
		std::vector<T2> componentDataList2;
		GetEntityArray(entityQuery, allEntities);
		GetComponentDataArray(entityQuery, componentDataList1);
		GetComponentDataArray(entityQuery, componentDataList2);
		if (allEntities.size() != componentDataList1.size() || componentDataList1.size() != componentDataList2.size()) return;
		std::vector<std::shared_future<void>> futures;
		size_t size = allEntities.size();
		std::vector<std::vector<Entity>> collectedEntityLists;
		const auto threadSize = JobManager::PrimaryWorkers().Size();
		for (int i = 0; i < threadSize; i++) {
			collectedEntityLists.push_back(std::vector<Entity>());
		}
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			std::vector<Entity>* collectedEntityList = &collectedEntityLists[i];
			futures.push_back(JobManager::PrimaryWorkers().Push([&allEntities, &componentDataList1, &componentDataList2, size, collectedEntityList, i, filterFunc](int id) {
				for (int j = 0; j < size / threadSize; j++) {
					if (filterFunc(allEntities[j * threadSize + i], componentDataList1[j * threadSize + i], componentDataList2[j * threadSize + i])) {
						collectedEntityList->push_back(allEntities[j * threadSize + i]);
					}
				}
				}).share());
		}
		for (const auto& i : futures) i.wait();
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			const auto listSize = collectedEntityLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedEntityLists[i].data(), listSize * sizeof(Entity));
		}


		const size_t remainder = size % threadSize;
		for (int i = 0; i < remainder; i++) {
			if (filterFunc(allEntities[size - remainder + i], componentDataList1[size - remainder + i], componentDataList2[size - remainder + i])) {
				container.push_back(allEntities[size - remainder + i]);
			}
		}
	}


	template<typename T1>
	void EntityManager::GetEntityArray(const EntityQuery& entityQuery, const T1& filter, std::vector<Entity>& container)
	{
		if (entityQuery.IsNull()) return;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return;
		}
		std::vector<Entity> allEntities;
		std::vector<T1> componentDataList;
		GetEntityArray(entityQuery, allEntities);
		GetComponentDataArray(entityQuery, componentDataList);
		std::vector<std::shared_future<void>> futures;
		size_t size = allEntities.size();
		std::vector<std::vector<Entity>> collectedEntityLists;
		const auto threadSize = JobManager::PrimaryWorkers().Size();
		for (int i = 0; i < threadSize; i++) {
			collectedEntityLists.push_back(std::vector<Entity>());
		}
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			std::vector<Entity>* collectedEntityList = &collectedEntityLists[i];
			futures.push_back(JobManager::PrimaryWorkers().Push([&allEntities, &componentDataList, size, filter, collectedEntityList, i, threadSize](int id) {
				for (int j = 0; j < size / threadSize; j++) {
					if (filter == componentDataList[j * threadSize + i]) {
						collectedEntityList->push_back(allEntities[j * threadSize + i]);
					}
				}
				}).share());
		}
		for (const auto& i : futures) i.wait();
		for (int i = 0; i < collectedEntityLists.size(); i++) {
			const auto listSize = collectedEntityLists[i].size();
			if (listSize == 0) continue;
			container.resize(container.size() + listSize);
			memcpy(&container.at(container.size() - listSize), collectedEntityLists[i].data(), listSize * sizeof(Entity));
		}


		const size_t remainder = size % threadSize;
		for (int i = 0; i < remainder; i++) {
			if (filter == componentDataList[size - remainder + i]) {
				container.push_back(allEntities[size - remainder + i]);
			}
		}
	}

	template <typename T>
	std::vector<std::pair<T*, size_t>> EntityManager::UnsafeGetComponentDataArray(const EntityQuery& entityQuery)
	{
		std::vector<std::pair<T*, size_t>> retVal;
		retVal.resize(0);
		if (entityQuery.IsNull()) return retVal;
		const size_t index = entityQuery.m_index;
		if (index > GetInstance().m_entityQueries->size()) {
			Debug::Error("EntityQuery not exist!");
			return retVal;
		}
		for (const auto& i : GetInstance().m_entityQueryInfos->at(index).m_queriedStorage) {
			auto targetType = Typeof<T>();
			const auto entityCount = i.m_archetypeInfo->m_entityAliveCount;
			auto found = false;
			for (const auto& type : i.m_archetypeInfo->m_componentTypes)
			{
				if (type.m_typeId == targetType.m_typeId)
				{
					targetType = type;
					found = true;
				}
			}
			if (!found) continue;
			const auto capacity = i.m_archetypeInfo->m_chunkCapacity;
			const auto* chunkArray = i.m_chunkArray;
			const auto chunkSize = entityCount / capacity;
			const auto chunkReminder = entityCount % capacity;
			for(int chunkIndex = 0; chunkIndex < chunkSize; chunkIndex++)
			{
				auto* data = static_cast<char*>(chunkArray->Chunks[chunkIndex].m_data);
				T* ptr = reinterpret_cast<T*>(data + targetType.m_offset * capacity);
				retVal.emplace_back(ptr, capacity);
			}
			if(chunkReminder > 0)
			{
				auto* data = static_cast<char*>(chunkArray->Chunks[chunkSize].m_data);
				T* ptr = reinterpret_cast<T*>(data + targetType.m_offset * capacity);
				retVal.emplace_back(ptr, chunkReminder);
			}
		}
		return retVal;
	}

	template <typename T>
	const std::vector<Entity>* EntityManager::GetPrivateComponentOwnersList()
	{
		return GetInstance().m_entityPrivateComponentStorage->GetOwnersList<T>();
	}

	template <typename T>
	void Entity::SetComponentData(const T& value) const
	{
		EntityManager::SetComponentData(*this, value);
	}

	template <typename T>
	T Entity::GetComponentData() const
	{
		return std::move(EntityManager::GetComponentData<T>(*this));
	}

	template <typename T>
	bool Entity::HasComponentData() const
	{
		return EntityManager::HasComponentData<T>(*this);
	}

	template <typename T>
	void Entity::SetPrivateComponent(std::unique_ptr<T> value) const
	{
		EntityManager::SetPrivateComponent(*this, std::move(value));
	}

	template <typename T>
	void Entity::RemovePrivateComponent() const
	{
		EntityManager::RemovePrivateComponent<T>(*this);
	}

	template <typename T>
	bool Entity::HasPrivateComponent() const
	{
		return EntityManager::HasPrivateComponent<T>(*this);
	}

	template <typename T>
	T ComponentDataChunk::GetData(const size_t& offset)
	{
		return T(*reinterpret_cast<T*>(static_cast<char*>(m_data) + offset));
	}

	template <typename T>
	void ComponentDataChunk::SetData(const size_t& offset, const T& data)
	{
		*reinterpret_cast<T*>(static_cast<char*>(m_data) + offset) = data;
	}

	template <typename T>
	std::unique_ptr<T>& Entity::GetPrivateComponent() const
	{
		try {
			return EntityManager::GetPrivateComponent<T>(*this);
		}
		catch (int e)
		{
			throw;
		}
	}

	template <typename T, typename ... Ts>
	void EntityQuery::SetAllFilters(T arg, Ts... args)
	{
		EntityManager::SetEntityQueryAllFilters(*this, arg, args...);
	}

	template <typename T, typename ... Ts>
	void EntityQuery::SetAnyFilters(T arg, Ts... args)
	{
		EntityManager::SetEntityQueryAnyFilters(*this, arg, args...);
	}

	template <typename T, typename ... Ts>
	void EntityQuery::SetNoneFilters(T arg, Ts... args)
	{
		EntityManager::SetEntityQueryNoneFilters(*this, arg, args...);
	}

	template<typename T1>
	void EntityQuery::ToComponentDataArray(std::vector<T1>& container)
	{
		EntityManager::GetComponentDataArray<T1>(*this, container);
	}

	template <typename T1, typename T2>
	void EntityQuery::ToComponentDataArray(std::vector<T1>& container,
		const std::function<bool(const T2&)>& filterFunc)
	{
		EntityManager::GetComponentDataArray(*this, container, filterFunc);
	}

	template <typename T1, typename T2, typename T3>
	void EntityQuery::ToComponentDataArray(std::vector<T1>& container,
		const std::function<bool(const T2&, const T3&)>& filterFunc)
	{
		EntityManager::GetComponentDataArray(*this, container, filterFunc);
	}

	template<typename T1, typename T2>
	void EntityQuery::ToComponentDataArray(const T1& filter, std::vector<T2>& container)
	{
		EntityManager::GetComponentDataArray(*this, filter, container);
	}
	template<typename T1>
	void EntityQuery::ToEntityArray(const T1& filter, std::vector<Entity>& container)
	{
		EntityManager::GetEntityArray(*this, filter, container);
	}

	template <typename T1>
	void EntityQuery::ToEntityArray(std::vector<Entity>& container, const std::function<bool(const Entity&, const T1&)>& filterFunc)
	{
		EntityManager::GetEntityArray<T1>(*this, container, filterFunc);
	}

	template <typename T1, typename T2>
	void EntityQuery::ToEntityArray(std::vector<Entity>& container,
		const std::function<bool(const Entity&, const T1&, const T2&)>& filterFunc)
	{
		EntityManager::GetEntityArray<T1>(*this, container, filterFunc);
	}
#pragma endregion

}