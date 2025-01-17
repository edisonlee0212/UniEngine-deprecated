#include "pch.h"
#include "MeshRenderer.h"
#include "UniEngine.h"
#include "RenderManager.h"
#include "SerializationManager.h"
void UniEngine::MeshRenderer::RenderBound(glm::vec4& color) const
{
	const auto transform = GetOwner().GetComponentData<GlobalTransform>().m_value;
	glm::vec3 size = m_mesh->m_bound.Size();
	if (size.x < 0.01f) size.x = 0.01f;
	if (size.z < 0.01f) size.z = 0.01f;
	if (size.y < 0.01f) size.y = 0.01f;
	RenderManager::DrawGizmoMesh(Default::Primitives::Cube.get(), EditorManager::GetSceneCamera().get(), color, transform * (glm::translate(m_mesh->m_bound.Center()) * glm::scale(size)), 1);
}

void UniEngine::MeshRenderer::OnGui()
{
	ImGui::Checkbox("Forward Rendering##MeshRenderer", &m_forwardRendering);
	if(!m_forwardRendering) ImGui::Checkbox("Receive shadow##MeshRenderer", &m_receiveShadow);
	ImGui::Checkbox("Cast shadow##MeshRenderer", &m_castShadow);
	ImGui::Text("Material:");
	ImGui::SameLine();
	EditorManager::DragAndDrop(m_material);
	if (m_material) {
		if (ImGui::TreeNode("Material##MeshRenderer")) {
			m_material->OnGui();
			ImGui::TreePop();
		}
	}
	ImGui::Text("Mesh:");
	ImGui::SameLine();
	EditorManager::DragAndDrop(m_mesh);
	if (m_mesh) {
		if (ImGui::TreeNode("Mesh##MeshRenderer")) {
			ImGui::Checkbox("Display bounds##MeshRenderer", &m_displayBound);
			if (m_displayBound)
			{
				ImGui::ColorEdit4("Color:##MeshRenderer", (float*)(void*)&m_displayBoundColor);
				RenderBound(m_displayBoundColor);
			}
			m_mesh->OnGui();
			ImGui::TreePop();
		}
	}
}

UniEngine::MeshRenderer::MeshRenderer()
{
	SetEnabled(true);
}

UniEngine::MeshRenderer::~MeshRenderer()
{
}

void UniEngine::MeshRenderer::Serialize(YAML::Emitter& out)
{
	out << YAML::Key << "ForwardRendering" << m_forwardRendering;
	out << YAML::Key << "CastShadow" << m_castShadow;
	out << YAML::Key << "ReceiveShadow" << m_receiveShadow;
}

void UniEngine::MeshRenderer::Deserialize(const YAML::Node& in)
{
	m_forwardRendering = in["ForwardRendering"].as<bool>();
	m_castShadow = in["CastShadow"].as<bool>();
	m_receiveShadow = in["ReceiveShadow"].as<bool>();
}
