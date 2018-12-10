////////////////////////////////////////////////////////////////////////////////
// Filename: lightclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _LIGHTCLASS_H_
#define _LIGHTCLASS_H_


//////////////
// INCLUDES //
//////////////
//#include <d3dx10math.h>

#include "D3DHeader/D3DX10math.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: LightClass
////////////////////////////////////////////////////////////////////////////////
class LightClass
{
public:
	LightClass();
	LightClass(const LightClass&);
	~LightClass();

	void SetAmbientColor(float, float, float, float);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	void SetSpecularColor(float, float, float, float);
	void SetSpecularPower(float);
	void SetPosition(float, float, float);
	void SetLookAt(float, float, float);

	void SetPointLightColor(float, float, float, float);
	void SetPointLightPosition(float, float, float);

	D3DXVECTOR4 GetPointLightColor();
	D3DXVECTOR4 GetPointLightPosition();

	D3DXVECTOR4 GetAmbientColor();
	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();
	D3DXVECTOR4 GetSpecularColor();
	D3DXVECTOR3 GetPosition();
	float GetSpecularPower();

	void GenerateViewMatrix();
	void GenerateProjectionMatrix(float, float, float, float);

	void GetViewMatrix(D3DXMATRIX&);
	void GetProjectionMatrix(D3DXMATRIX&);

private:
	D3DXVECTOR4 m_ambientColor;
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR3 m_direction;
	D3DXVECTOR4 m_specularColor;
	float m_specularPower;

	D3DXVECTOR4 m_PointLightColor;
	D3DXVECTOR4 m_PointLightPosition;

	D3DXVECTOR3 m_position;
	D3DXVECTOR3 m_lookAt;
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_projectionMatrix;
};

#endif