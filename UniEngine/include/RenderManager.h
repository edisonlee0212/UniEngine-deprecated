#pragma once
#include "Core.h"
#include "UniEngineAPI.h"
#include "CameraComponent.h"
#include "MeshRenderer.h"
#include "Particles.h"
#include "RenderTarget.h"

#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLightShadowMap.h"
#include "PointLightShadowMap.h"
#include "SpotLightShadowMap.h"
#include "Cubemap.h"
#include "Default.h"
#include "Texture2D.h"

#include "PostProcessing.h"

namespace UniEngine {
	struct UNIENGINE_API LightSettingsBlock {
		float m_splitDistance[4];
		int m_pcfSampleAmount = 16;
		float m_scaleFactor = 1.0f;
		int m_blockerSearchAmount = 2;
		float m_seamFixRatio = 0.05f;
		float m_vsmMaxVariance = 0.001f;
		float m_lightBleedFactor = 0.5f;
		float m_evsmExponent = 40.0f;
		float m_ambientLight = 0.3f;
	};

	struct MaterialSettingsBlock
	{
		GLuint64 m_spotShadowMap = 0;
		GLuint64 m_directionalShadowMap = 0;
		GLuint64 m_pointShadowMap = 0;
		
		GLuint64 m_albedoMap = 0;
		GLuint64 m_normalMap = 0;
		GLuint64 m_metallicMap = 0;
		GLuint64 m_roughnessMap = 0;
		GLuint64 m_aoMap = 0;
		
		GLuint64 m_ambient = 0;
		GLuint64 m_diffuse = 0;
		GLuint64 m_specular = 0;
		GLuint64 m_emissive = 0;
		GLuint64 m_displacement = 0;

		
		int m_albedoEnabled = 0;
		int m_normalEnabled = 0;
		int m_metallicEnabled = 0;
		int m_roughnessEnabled = 0;
		int m_aoEnabled = 0;

		int m_ambientEnabled = 0;
		int m_diffuseEnabled = 0;
		int m_specularEnabled = 0;
		int m_emissiveEnabled = 0;
		int m_displacementEnabled = 0;

		glm::vec4 m_albedoColorVal = glm::vec4(1.0f);
		float m_shininessVal = 32.0f;
		float m_metallicVal = 0.5f;
		float m_roughnessVal = 0.5f;
		float m_aoVal = 1.0f;
		float m_displacementScale = 0.0f;
		
		int m_receiveShadow = true;
		int m_enableShadow = true;
		int m_alphaDiscardEnabled = true;
		float m_alphaDiscardOffset = 0.1f;

		GLuint64 m_environmentalMap = 0;
		int m_environmentalMapEnabled = 0;
	};
	
	class UNIENGINE_API RenderManager : public Singleton<RenderManager>
	{
		CameraComponent* m_mainCameraComponent = nullptr;
#pragma region Global Var
#pragma region GUI
		bool m_enableLightMenu = true;
		bool m_enableRenderMenu = false;
		bool m_enableInfoWindow = false;
#pragma endregion
#pragma region Render
		std::unique_ptr<GLUBO> m_kernelBlock;
		std::unique_ptr<GLProgram> m_gBufferInstancedPrepass;
		std::unique_ptr<GLProgram> m_gBufferPrepass;
		std::unique_ptr<GLProgram> m_gBufferLightingPass;

		int m_mainCameraResolutionX = 1;
		int m_mainCameraResolutionY = 1;
		friend class RenderTarget;
		size_t m_triangles = 0;
		size_t m_drawCall = 0;
		
		std::unique_ptr<GLUBO> m_materialSettingsBuffer;
#pragma endregion
#pragma region Shadow
		GLUBO m_directionalLightBlock;
		GLUBO m_pointLightBlock;
		GLUBO m_spotLightBlock;

		size_t m_shadowMapResolution = 4096;
		GLUBO m_shadowCascadeInfoBlock;
		

		DirectionalLightInfo m_directionalLights[Default::ShaderIncludes::MaxDirectionalLightAmount];
		PointLightInfo m_pointLights[Default::ShaderIncludes::MaxPointLightAmount];
		SpotLightInfo m_spotLights[Default::ShaderIncludes::MaxSpotLightAmount];

		std::unique_ptr<GLProgram> m_directionalLightProgram;
		std::unique_ptr<GLProgram> m_directionalLightInstancedProgram;
		std::unique_ptr<GLProgram> m_pointLightProgram;
		std::unique_ptr<GLProgram> m_pointLightInstancedProgram;
		std::unique_ptr<GLProgram> m_spotLightProgram;
		std::unique_ptr<GLProgram> m_spotLightInstancedProgram;

		
		friend class EditorManager;
		std::unique_ptr<DirectionalLightShadowMap> m_directionalLightShadowMap;
		std::unique_ptr<PointLightShadowMap> m_pointLightShadowMap;
		std::unique_ptr<SpotLightShadowMap> m_spotLightShadowMap;
		
		
		
#pragma endregion
#pragma endregion
		
		static void DeferredPrepass(const Mesh* mesh, const Material* material, const glm::mat4& model);
		static void DeferredPrepassInstanced(const Mesh* mesh, const Material* material, const glm::mat4& model, glm::mat4* matrices, const size_t& count);
		
		static void DrawMesh(const Mesh* mesh, const Material* material, const glm::mat4& model, const bool& receiveShadow);
		static void DrawMeshInstanced(const Mesh* mesh, const Material* material, const glm::mat4& model, const glm::mat4* matrices, const size_t& count, const bool& receiveShadow);
		
		static void DrawGizmoMesh(const Mesh* mesh, const glm::vec4& color, const glm::mat4& model, const glm::mat4& scaleMatrix);
		static void DrawGizmoMeshInstanced(const Mesh* mesh, const glm::vec4& color, const glm::mat4& model, const glm::mat4* matrices, const size_t& count, const glm::mat4& scaleMatrix);
		static void DrawGizmoMeshInstancedColored(const Mesh* mesh, const glm::vec4* colors, const glm::mat4* matrices, const size_t& count, const glm::mat4& model, const glm::mat4& scaleMatrix);
		
		static float Lerp(const float& a, const float& b, const float& f);
	public:
		bool m_stableFit = true;
		float m_maxShadowDistance = 500;
		float m_shadowCascadeSplit[Default::ShaderIncludes::ShadowCascadeAmount] = { 0.15f, 0.3f, 0.5f, 1.0f };
		LightSettingsBlock m_lightSettings;
		MaterialSettingsBlock m_materialSettings;

		static void MaterialPropertySetter(const Material* material, const bool& disableBlending = false);
		static void ApplyMaterialSettings(const Material* material, const GLProgram* program);
		static void BindTextureHandles(const Material* material);
		static void ReleaseTextureHandles(const Material* material);
		static void RenderToCameraDeferred(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds = false);
		static void RenderBackGround(const std::unique_ptr<CameraComponent>& cameraComponent);
		static void RenderToCameraForward(const std::unique_ptr<CameraComponent>& cameraComponent, const GlobalTransform& cameraTransform, glm::vec3& minBound, glm::vec3& maxBound, bool calculateBounds = false);
		static void Init();
		//Main rendering happens here.
		static void PreUpdate();
#pragma region Shadow
		static void SetSplitRatio(const float& r1, const float& r2, const float& r3, const float& r4);
		static void SetShadowMapResolution(const size_t& value);

		static glm::vec3 ClosestPointOnLine(const glm::vec3& point, const glm::vec3& a, const glm::vec3& b);
#pragma endregion
#pragma region RenderAPI
		static void LateUpdate();
		static size_t Triangles();
		static size_t DrawCall();


		static void DrawTexture2D(const GLTexture2D* texture, const float& depth, const glm::vec2& center, const glm::vec2& size);
		static void DrawTexture2D(const GLTexture2D* texture, const float& depth, const glm::vec2& center, const glm::vec2& size, const RenderTarget* target);
		static void DrawTexture2D(const Texture2D* texture, const float& depth, const glm::vec2& center, const glm::vec2& size, const RenderTarget* target);
		static void DrawTexture2D(const Texture2D* texture, const float& depth, const glm::vec2& center, const glm::vec2& size, const CameraComponent* cameraComponent);

		static void SetMainCamera(CameraComponent* value);
		static CameraComponent* GetMainCamera();
#pragma region Gizmos
		static void DrawGizmoMesh(const Mesh* mesh, const CameraComponent* cameraComponent, const glm::vec4& color = glm::vec4(1.0f), const glm::mat4& model = glm::mat4(1.0f), const float& size = 1.0f);
		static void DrawGizmoMeshInstanced(const Mesh* mesh, const CameraComponent* cameraComponent, const glm::vec4& color, const glm::mat4* matrices, const size_t& count, const glm::mat4& model = glm::mat4(1.0f), const float& size = 1.0f);
		static void DrawGizmoMeshInstancedColored(const Mesh* mesh, const CameraComponent* cameraComponent, const glm::vec4* colors, const glm::mat4* matrices, const size_t& count, const glm::mat4& model = glm::mat4(1.0f), const float& size = 1.0f);

		static void DrawGizmoMesh(const Mesh* mesh, const CameraComponent* cameraComponent, const glm::vec3& cameraPosition, const glm::quat& cameraRotation, const glm::vec4& color = glm::vec4(1.0f), const glm::mat4& model = glm::mat4(1.0f), const float& size = 1.0f);
		static void DrawGizmoMeshInstanced(const Mesh* mesh, const CameraComponent* cameraComponent, const glm::vec3& cameraPosition, const glm::quat& cameraRotation, const glm::vec4& color, const glm::mat4* matrices, const size_t& count, const glm::mat4& model = glm::mat4(1.0f), const float& size = 1.0f);
		static void DrawGizmoMeshInstancedColored(const Mesh* mesh, const CameraComponent* cameraComponent, const glm::vec3& cameraPosition, const glm::quat& cameraRotation, const glm::vec4* colors, const glm::mat4* matrices, const size_t& count, const glm::mat4& model = glm::mat4(1.0f), const float& size = 1.0f);


		static void DrawGizmoRay(const CameraComponent* cameraComponent, const glm::vec4& color, const glm::vec3& start, const glm::vec3& end, const float& width = 0.01f);
		static void DrawGizmoRays(const CameraComponent* cameraComponent, const glm::vec4& color, std::vector<std::pair<glm::vec3, glm::vec3>>& connections, const float& width = 0.01f);
		static void DrawGizmoRays(const CameraComponent* cameraComponent, const glm::vec4& color, std::vector<Ray>& rays, const float& width = 0.01f);
		static void DrawGizmoRay(const CameraComponent* cameraComponent, const glm::vec4& color, Ray& ray, const float& width = 0.01f);

		static void DrawGizmoRay(const CameraComponent* cameraComponent, const glm::vec3& cameraPosition, const glm::quat& cameraRotation, const glm::vec4& color, const glm::vec3& start, const glm::vec3& end, const float& width = 0.01f);
		static void DrawGizmoRays(const CameraComponent* cameraComponent, const glm::vec3& cameraPosition, const glm::quat& cameraRotation, const glm::vec4& color, std::vector<std::pair<glm::vec3, glm::vec3>>& connections, const float& width = 0.01f);
		static void DrawGizmoRays(const CameraComponent* cameraComponent, const glm::vec3& cameraPosition, const glm::quat& cameraRotation, const glm::vec4& color, std::vector<Ray>& rays, const float& width = 0.01f);
		static void DrawGizmoRay(const CameraComponent* cameraComponent, const glm::vec3& cameraPosition, const glm::quat& cameraRotation, const glm::vec4& color, Ray& ray, const float& width = 0.01f);
#pragma endregion

		static void DrawMesh(const Mesh* mesh, const Material* material, const glm::mat4& model, const CameraComponent* cameraComponent, const bool& receiveShadow = true);
		static void DrawMeshInstanced(const Mesh* mesh, const Material* material, const glm::mat4& model, const glm::mat4* matrices, const size_t& count, const CameraComponent* cameraComponent, const bool& receiveShadow = true);

#pragma endregion
	};
}
