#pragma once
///////////////////////////////////////////////////////////////////////////////
// Filename: modellistclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _MODELLISTCLASS_H_
#define _MODELLISTCLASS_H_

//////////////
// INCLUDES //
//////////////
#include "modelclass.h"

#include <time.h>
#include <vector>
#include <stdlib.h>
//#include <d3dx10math.h>

#include "D3DHeader/D3DX10math.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////////
// Class name: ModelListClass
///////////////////////////////////////////////////////////////////////////////
class ModelListClass
{
public:
	ModelListClass();
	ModelListClass(const ModelListClass&);
	~ModelListClass();

	bool Initialize(ID3D11Device*, vector<const char*>&, vector<const WCHAR*>&, const unsigned int);
	void Shutdown();

	unsigned int GetNumOfModels();

	void SetModelPosition(unsigned int index, float x, float y, float z);
	void SetModelRotation(unsigned int index, float x, float y, float z);
	void SetModelScaling(unsigned int index, float x, float y, float z);

	D3DXVECTOR3 GetModelPosition(unsigned int);
	D3DXVECTOR3 GetModelRotation(unsigned int);
	D3DXVECTOR3 GetModelScaling(unsigned int);

	void SetModelRadius(unsigned int index, float radius);

	float GetmodelRadius(unsigned int index);

	D3DXMATRIX GetModelWorldMatrix(unsigned int);
	void SetModelWorldMatrix(unsigned int, D3DXMATRIX);

	vector<ModelClass*> GetModelList();

private:
	unsigned int numOfModels;
	vector<ModelClass*> m_Modellist;
	vector<D3DXMATRIX> m_ModelWorldMatrix;

	vector<D3DXVECTOR3> m_ModelPosition;
	vector<D3DXVECTOR3> m_ModelRotation;
	vector<D3DXVECTOR3> m_ModelScaling;

	vector<float> m_ModelRadius;
};

#endif