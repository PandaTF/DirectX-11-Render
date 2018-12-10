#pragma once
////////////////////////////////////////////////////////////////////////////////
// Filename: textclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTCLASS_H_
#define _TEXTCLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "fontclass.h"
#include "fontshaderclass.h"
#include <vector>
#include <string>
using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Class name: TextClass
////////////////////////////////////////////////////////////////////////////////
class TextClass
{
private:

	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, D3DXMATRIX, const unsigned int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);

	bool updateSentenceWithIndex(ID3D11DeviceContext*, const unsigned int, const char*, const int, const int, const D3DXVECTOR3);

	int GetFontPositionX(unsigned int index);
	int GetFontPositionY(unsigned int index);

	D3DXVECTOR3 GetFontColor(unsigned int index);
	const char* GetFontContent(unsigned int index);

	bool SetFps(int fps, ID3D11DeviceContext* deviceContext, unsigned int);
	bool SetCpu(int cpu, ID3D11DeviceContext* deviceContext, unsigned int);
	bool SetRenderCount(int renderCount, ID3D11DeviceContext* deviceContext, unsigned int);

	bool UpdateMousePositionInfo(int, int, ID3D11DeviceContext*, unsigned int, unsigned int);

private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, const char*, int, int, D3DXVECTOR3, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*, D3DXMATRIX, D3DXMATRIX);

private:
	FontClass * m_Font;
	FontShaderClass* m_FontShader;
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;

	SentenceType** m_sentenceArray;
	unsigned int numOfSentence;
	int* fontPosX;
	int* fontPosY;
	D3DXVECTOR3* fontColor;
	//char** sentenceContent;
	vector<const char*> sentenceContent;
};

#endif