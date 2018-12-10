///////////////////////////////////////////////////////////////////////////////
// Filename: modellistclass.cpp
///////////////////////////////////////////////////////////////////////////////
#include "modellistclass.h"

ModelListClass::ModelListClass()
{
}


ModelListClass::ModelListClass(const ModelListClass& other)
{
}


ModelListClass::~ModelListClass()
{
}

bool ModelListClass::Initialize(ID3D11Device *device, vector<const char*> &modelNames, vector<const WCHAR*> &textureNames, unsigned int numModels)
{
	bool result;

	if (!numModels)
	{
		return false;
	}

	numOfModels = numModels;

	for (unsigned int i = 0; i < numModels; i++)
	{
		ModelClass* newModel = new ModelClass;
		if (!newModel)
		{
			return false;
		}

		result = newModel->Initialize(device, modelNames[i], textureNames[i], false, false);
		if (!result)
		{
			return false;
		}

		m_Modellist.push_back(newModel);

		D3DXMATRIX temp;
		D3DXMatrixIdentity(&temp);
		m_ModelWorldMatrix.push_back(temp);

		D3DXVECTOR3 temp1;
		temp1.x = temp1.y = temp1.z = 0.0f;
		m_ModelPosition.push_back(temp1);
		m_ModelRotation.push_back(temp1);

		temp1.x = temp1.y = temp1.z = 1.0f;
		m_ModelScaling.push_back(temp1);

		float radius = 1.0f;
		m_ModelRadius.push_back(radius);
	}

	return true;
}

void ModelListClass::Shutdown()
{
	if (m_Modellist.size() != 0)
	{
		for (unsigned int i = 0; i < m_Modellist.size(); i++)
		{
			m_Modellist[i]->Shutdown();
			delete m_Modellist[i];
			m_Modellist[i] = 0;
		}

		m_Modellist.clear();
	}
}

unsigned int ModelListClass::GetNumOfModels()
{
	return numOfModels;
}

void ModelListClass::SetModelPosition(unsigned int index, float x, float y, float z)
{
	if (index < numOfModels)
	{
		m_ModelPosition[index].x = x;
		m_ModelPosition[index].y = y;
		m_ModelPosition[index].z = z;
	}
}

void ModelListClass::SetModelRotation(unsigned int index, float x, float y, float z)
{
	if (index < numOfModels)
	{
		m_ModelRotation[index].x = x;
		m_ModelRotation[index].y = y;
		m_ModelRotation[index].z = z;
	}
}

void ModelListClass::SetModelScaling(unsigned int index, float x, float y, float z)
{
	if (index < numOfModels)
	{
		m_ModelScaling[index].x = x;
		m_ModelScaling[index].y = y;
		m_ModelScaling[index].z = z;
	}
}

D3DXVECTOR3 ModelListClass::GetModelPosition(unsigned int index)
{
	if (index < numOfModels)
	{
		return m_ModelPosition[index];
	}
	else
		return D3DXVECTOR3(0.0f,0.0f,0.0f);
}

D3DXVECTOR3 ModelListClass::GetModelRotation(unsigned int index)
{
	if (index < numOfModels)
	{
		return m_ModelRotation[index];
	}
	else
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

D3DXVECTOR3 ModelListClass::GetModelScaling(unsigned int index)
{
	if (index < numOfModels)
	{
		return m_ModelScaling[index];
	}
	else
		return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

void ModelListClass::SetModelRadius(unsigned int index, float radius)
{
	if (index < numOfModels)
	{
		m_ModelRadius[index] = radius;
	}
}

float ModelListClass::GetmodelRadius(unsigned int index)
{
	if (index < numOfModels)
	{
		return m_ModelRadius[index];
	}
	else
		return 0.0f;
}

D3DXMATRIX ModelListClass::GetModelWorldMatrix(unsigned int index)
{
	if (index < numOfModels)
		return m_ModelWorldMatrix[index];
	else
	{
		D3DXMATRIX temp;
		D3DXMatrixIdentity(&temp);
		return temp;
	}
}

void ModelListClass::SetModelWorldMatrix(unsigned int index, D3DXMATRIX newWorldMatrix)
{
	if (index < numOfModels)
	{
		m_ModelWorldMatrix[index] = newWorldMatrix;
	}
}

vector<ModelClass*> ModelListClass::GetModelList()
{
	return m_Modellist;
}
