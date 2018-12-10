////////////////////////////////////////////////////////////////////////////////
// Filename: SpecularLightShaderClass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SpecularLightShaderClass_H_
#define _SpecularLightShaderClass_H_

/////////////
// GLOBALS //
/////////////
const int NUM_LIGHTS = 4;

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
// Class name: SpecularLightShaderClass
////////////////////////////////////////////////////////////////////////////////
class SpecularLightShaderClass
{
private:
	struct MatrixBufferType
	{
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct CameraBufferType
	{
		D3DXVECTOR3 cameraPosition;
		float padding;
	};

	struct LightBufferType
	{
		D3DXVECTOR4 ambientColor;
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR3 lightDirection;
		float specularPower;
		D3DXVECTOR4 specularColor;
	};

	struct LightColorBufferType
	{
		D3DXVECTOR4 pointLightColor[NUM_LIGHTS];
	};

	struct LightPositionBufferType
	{
		D3DXVECTOR4 pointLightPosition[NUM_LIGHTS];
	};

public:
	SpecularLightShaderClass();
	SpecularLightShaderClass(const SpecularLightShaderClass&);
	~SpecularLightShaderClass();

	bool Initialize(ID3D11Device*, HWND);
	void Shutdown();

	bool Render(ID3D11DeviceContext*, int,		//Direct3D device, indexCount
		D3DXMATRIX, D3DXMATRIX, D3DXMATRIX,		//WorldMatrix, ViewMatrix, ProjectionMatrix
		ID3D11ShaderResourceView*,				//Texture
		D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4,	//Light Direction, Ambient Color, Diffuse Color
		D3DXVECTOR3, D3DXVECTOR4, float,		//Camera Position, SpecularColor, Specular Power
		D3DXVECTOR4[], D3DXVECTOR4[]);	

private:
	bool InitializeShader(ID3D11Device*, HWND, const WCHAR*, const WCHAR*);
	void ShutdownShader();
	void OutputShaderErrorMessage(ID3D10Blob*, HWND, const WCHAR*);

	bool SetShaderParameters(ID3D11DeviceContext*,
		D3DXMATRIX, D3DXMATRIX, D3DXMATRIX, 
		ID3D11ShaderResourceView*, 
		D3DXVECTOR3, D3DXVECTOR4, D3DXVECTOR4,
		D3DXVECTOR3, D3DXVECTOR4, float,
		D3DXVECTOR4[], D3DXVECTOR4[]);

	void RenderShader(ID3D11DeviceContext*, int);

private:
	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;

	ID3D11Buffer* m_lightBuffer;
	ID3D11Buffer* m_cameraBuffer;

	ID3D11Buffer* m_lightColorBuffer;
	ID3D11Buffer* m_lightPositionBuffer;
};

#endif