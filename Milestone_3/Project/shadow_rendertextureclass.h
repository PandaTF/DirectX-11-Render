#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: rendertextureclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SHADOWRENDERTEXTURECLASS_H_
#define _SHADOWRENDERTEXTURECLASS_H_


//////////////
// INCLUDES //
//////////////
//#include <d3d11.h>
//#include <d3dx10math.h>

#include "D3DHeader/D3D11.h"
#include "D3DHeader/D3DX10math.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: RenderTextureClass
////////////////////////////////////////////////////////////////////////////////
class ShadowRenderTextureClass
{
public:
	ShadowRenderTextureClass();
	ShadowRenderTextureClass(const ShadowRenderTextureClass&);
	~ShadowRenderTextureClass();

	bool Initialize(ID3D11Device*, int, int, float, float);
	void Shutdown();

	void SetRenderTarget(ID3D11DeviceContext*);
	void ClearRenderTarget(ID3D11DeviceContext*, float, float, float, float);
	ID3D11ShaderResourceView* GetShaderResourceView();
	void GetProjectionMatrix(D3DXMATRIX&);
	void GetOrthoMatrix(D3DXMATRIX&);

private:
	ID3D11Texture2D * m_renderTargetTexture;
	ID3D11RenderTargetView* m_renderTargetView;
	ID3D11ShaderResourceView* m_shaderResourceView;
	ID3D11Texture2D* m_depthStencilBuffer;
	ID3D11DepthStencilView* m_depthStencilView;
	D3D11_VIEWPORT m_viewport;
	D3DXMATRIX m_projectionMatrix;
	D3DXMATRIX m_orthoMatrix;

};

#endif