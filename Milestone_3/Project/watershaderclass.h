#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: watershaderclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _WATERSHADERCLASS_H_
#define _WATERSHADERCLASS_H_

//////////////
// INCLUDES //
//////////////
//#include <d3d11.h>
//#include <d3dx10math.h>
//#include <d3dx11async.h>

#include "D3DHeader/D3D11.h"
#include "D3DHeader/D3DX10math.h"
#include "D3DHeader/D3DX11async.h"
#include <fstream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: WaterShaderClass
////////////////////////////////////////////////////////////////////////////////
class WaterShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct ReflectionBufferType
	{
		D3DXMATRIX reflection;
		float maxHeight;
		D3DXVECTOR3 padding;
	};

	struct WaterBufferType
	{
		float waterTranslation;
		float reflectRefractScale;
		D3DXVECTOR2 padding;
	};

public:
	WaterShaderClass();
	WaterShaderClass(const WaterShaderClass&);
	~WaterShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float, float, float);

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, ID3D11ShaderResourceView*,
		ID3D11ShaderResourceView*, ID3D11ShaderResourceView*, float, float, float);
	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader * m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;

	ID3D11Buffer* m_reflectionBuffer;
	ID3D11Buffer* m_waterBuffer;
};

#endif