// Planet.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "UniEngine.h"
#include "CameraControlSystem.h"
#include "PlanetTerrainSystem.h"
#include "PerlinNoiseStage.h"

using namespace UniEngine;
using namespace Planet;
int main()
{
	ComponentFactory::RegisterSerializable<PlanetTerrain>();
	FileIO::SetResourcePath("../Resources/");
	Application::Init();
	RenderManager::GetInstance().m_lightSettings.m_ambientLight = 0.3f;
#pragma region Preparations
	auto& world = Application::GetCurrentWorld();
	WorldTime* time = world->Time();
	EntityArchetype archetype = EntityManager::CreateEntityArchetype("General", Transform(), GlobalTransform());

	
	CameraControlSystem* ccs = world->CreateSystem<CameraControlSystem>(SystemGroup::SimulationSystemGroup);
	ccs->SetSensitivity(0.1f);
	ccs->SetVelocity(15.0f);
	ccs->Enable();

	RenderManager::GetMainCamera()->m_drawSkyBox = false;
	
	PlanetTerrainSystem* pts = world->CreateSystem<PlanetTerrainSystem>(SystemGroup::SimulationSystemGroup);
	pts->Enable();

	PlanetInfo pi;
	Transform planetTransform;
	
	planetTransform.SetPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	planetTransform.SetEulerRotation(glm::vec3(0.0f));
	pi.MaxLodLevel = 8;
	pi.LodDistance = 7.0;
	pi.Radius = 10.0;
	pi.Index = 0;
	pi.Resolution = 8;

	auto planetTerrain1 = std::make_unique<PlanetTerrain>();
	planetTerrain1->Init(pi);
	//Serialization not implemented.
	//planetTerrain1->TerrainConstructionStages.push_back(std::make_shared<PerlinNoiseStage>());
	auto planet1 = EntityManager::CreateEntity(archetype);
	planet1.SetPrivateComponent(std::move(planetTerrain1));
	planet1.SetComponentData(planetTransform);
	planet1.SetName("Planet 1");
	planetTransform.SetPosition(glm::vec3(35.0f, 0.0f, 0.0f));
	pi.MaxLodLevel = 20;
	pi.LodDistance = 7.0;
	pi.Radius = 15.0;
	pi.Index = 1;
	auto planetTerrain2 = std::make_unique<PlanetTerrain>();
	planetTerrain2->Init(pi);
	auto planet2 = EntityManager::CreateEntity(archetype);
	planet2.SetPrivateComponent(std::move(planetTerrain2));
	planet2.SetComponentData(planetTransform);
	planet2.SetName("Planet 2");
	planetTransform.SetPosition(glm::vec3(-20.0f, 0.0f, 0.0f));
	pi.MaxLodLevel = 4;
	pi.LodDistance = 7.0;
	pi.Radius = 5.0;
	pi.Index = 2;
	auto planetTerrain3 = std::make_unique<PlanetTerrain>();
	planetTerrain3->Init(pi);
	auto planet3 = EntityManager::CreateEntity(archetype);
	planet3.SetPrivateComponent(std::move(planetTerrain3));
	planet3.SetComponentData(planetTransform);
	planet3.SetName("Planet 3");
#pragma endregion

#pragma region Lights
	auto sharedMat = std::make_shared<Material>();
	sharedMat->SetTexture(Default::Textures::StandardTexture);

	Transform ltw;
	auto dlc = std::make_unique<DirectionalLight>();
	dlc->m_diffuse = glm::vec3(1.0f);
	Entity dle = EntityManager::CreateEntity("Directional Light");
	dle.SetName("Directional Light 1");
	EntityManager::SetPrivateComponent(dle, std::move(dlc));
	
	auto plmmc = std::make_unique<MeshRenderer>();
	auto plmmc2 = std::make_unique<MeshRenderer>();
	plmmc->m_mesh = Default::Primitives::Sphere;
	plmmc->m_material = sharedMat;
	plmmc2->m_mesh = Default::Primitives::Sphere;
	plmmc2->m_material = sharedMat;
	ltw.SetScale(glm::vec3(0.5f));

	auto plc = std::make_unique<PointLight>();
	plc->m_constant = 1.0f;
	plc->m_linear = 0.09f;
	plc->m_quadratic = 0.032f;
	plc->m_farPlane = 70.0f;
	plc->m_diffuse = glm::vec3(1.0f);
	plc->m_diffuseBrightness = 5;
	Entity ple = EntityManager::CreateEntity("Point Light 1");
	EntityManager::SetPrivateComponent(ple, std::move(plc));
	EntityManager::SetComponentData(ple, ltw);
	EntityManager::SetPrivateComponent<MeshRenderer>(ple, std::move(plmmc));
	
	plc = std::make_unique<PointLight>();
	plc->m_constant = 1.0f;
	plc->m_linear = 0.09f;
	plc->m_quadratic = 0.032f;
	plc->m_farPlane = 70.0f;
	plc->m_diffuse = glm::vec3(1.0f);
	Entity ple2 = EntityManager::CreateEntity("Point Light 2");
	EntityManager::SetPrivateComponent(ple2, std::move(plc));
	EntityManager::SetComponentData(ple2, ltw);
	ple2.SetName("Point Light 2");
	EntityManager::SetPrivateComponent<MeshRenderer>(ple2, std::move(plmmc2));
#pragma endregion

#pragma region EngineLoop
	Application::RegisterPreUpdateFunction([&]()
		{
#pragma region LightsPosition
			ltw.SetPosition(glm::vec4(glm::vec3(0.0f, 20.0f * glm::sin(Application::EngineTime() / 2.0f), -20.0f * glm::cos(Application::EngineTime() / 2.0f)), 0.0f));
			EntityManager::SetComponentData(dle, ltw);
			ltw.SetPosition(glm::vec4(glm::vec3(-20.0f * glm::cos(Application::EngineTime() / 2.0f), 20.0f * glm::sin(Application::EngineTime() / 2.0f), 0.0f), 0.0f));
			EntityManager::SetComponentData(ple, ltw);
			ltw.SetPosition(glm::vec4(glm::vec3(20.0f * glm::cos(Application::EngineTime() / 2.0f), 15.0f, 20.0f * glm::sin(Application::EngineTime() / 2.0f)), 0.0f));
			EntityManager::SetComponentData(ple2, ltw);
#pragma endregion
			Debug::Log("LogHere!");
			Debug::Warning("WarningHere!");
			Debug::Error("ErrorHere!");
		});
	Application::Run();
	Application::End();
#pragma endregion
	return 0;
}
