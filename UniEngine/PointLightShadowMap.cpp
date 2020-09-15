#include "pch.h"
#include "PointLightShadowMap.h"
using namespace UniEngine;

PointLightShadowMap::PointLightShadowMap(size_t amount, size_t resolutionX, size_t resolutionY)
{
	_ResolutionX = resolutionX;
	_ResolutionY = resolutionY;
	_DepthCubeMapArray = new GLTextureCubeMapArray(1, GL_DEPTH_COMPONENT32, static_cast<GLsizei>(_ResolutionX),
	                                               static_cast<GLsizei>(_ResolutionY), static_cast<GLsizei>(amount));
	_DepthCubeMapArray->SetInt(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	_DepthCubeMapArray->SetInt(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	_DepthCubeMapArray->SetInt(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	_DepthCubeMapArray->SetInt(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	_DepthCubeMapArray->SetInt(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	_DepthCubeMapArray->SetInt(GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
	_DepthCubeMapArray->SetInt(GL_TEXTURE_COMPARE_FUNC, GL_GEQUAL);
	AttachTexture(_DepthCubeMapArray, GL_DEPTH_ATTACHMENT);
}

GLTextureCubeMapArray* PointLightShadowMap::DepthCubeMapArray()
{
	return _DepthCubeMapArray;
}

void PointLightShadowMap::Bind()
{
	RenderTarget::Bind();
}
