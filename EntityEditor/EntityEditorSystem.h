#pragma once
#include "EntityEditorAPI.h"

namespace UniEngine
{
	enum EntityEditorSystemConfigFlags
	{
		EntityEditorSystem_None = 0,
		EntityEditorSystem_EnableEntityHierarchy = 1 << 0,
		EntityEditorSystem_EnableEntityInspector = 1 << 1
	};

	class ENTITYEDITOR_API EntityEditorSystem :
		public SystemBase
	{
		unsigned int _ConfigFlags = 0;
		int _SelectedHierarchyDisplayMode;
		Entity _SelectedEntity;
		void DrawEntityMenu(bool enabled, Entity& entity);
		void DrawEntityNode(Entity& entity);
		void DisplayComponent(ComponentBase* data, ComponentType type);
		void TempComponentInspector(ComponentType type, void* data);
	public:
		void OnCreate() override;
		void OnDestroy() override;
		void Update() override;
		void FixedUpdate() override;
		Entity GetSelectedEntity();
	};
}
