////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "ambientLightShaderClass.h"
#include "specularlightshaderclass.h"
#include "lightclass.h"
#include "bitmapclass.h"
#include "textureshaderclass.h"
#include "textclass.h"
#include "modellistclass.h"
#include "frustumclass.h"
#include "rendertextureclass.h"
#include "refractionshaderclass.h"
#include "watershaderclass.h"
#include "depthshaderclass.h"
#include "shadowshaderclass.h"
#include "shadow_rendertextureclass.h"
#include "projectionshaderclass.h"
#include "viewpointclass.h"
#include "specmapshaderclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = true;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 1.0f;

const int SHADOWMAP_WIDTH = 1024;
const int SHADOWMAP_HEIGHT = 1024;

////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, float, int, int, D3DXVECTOR3, D3DXVECTOR3, unsigned int);
	bool Render();

	bool RenderScene();
	bool RenderSceneToTexture();
	bool RenderReflectionToTexture();
	bool RenderRefractionToTexture();

	bool InitializeShipParts();
	bool UpdateShipParts();

private:
	D3DClass * m_D3D;
	CameraClass* m_Camera;
	CameraClass* m_UICamera;
	AmbientLightShaderClass* m_ambientLightShader;
	SpecularLightShaderClass* m_specularLightShader;
	TextureShaderClass* m_textureShader;
	LightClass* m_Light;
	BitmapClass* m_Bitmap;
	TextClass* m_Text;

	ModelListClass* m_ModelList;
	vector<const char*> filenameList;
	vector<const WCHAR*> textureList;

	ModelClass* m_skyboxModel;

	FrustumClass* m_Frustum;

	DWORD g_tNow, g_tPre;
	unsigned int numFont;
	unsigned int lightType;

	LightClass *m_Light1, *m_Light2, *m_Light3, *m_Light4;
	D3DXVECTOR3 pointLightPos[4];

	ModelClass *m_BathModel, *m_WaterModel;
	RenderTextureClass *m_RefractionTexture, *m_ReflectionTexture;

	RefractionShaderClass* m_RefractionShader;
	WaterShaderClass* m_WaterShader;

	float fireRotateY;
	bool fireClockwise;
	float m_waterHeight, m_waterTranslation;

	ModelClass *m_CubeModel, *m_GroundModel, *m_SphereModel;

	ShadowRenderTextureClass* m_RenderTexture;
	DepthShaderClass* m_DepthShader;
	ShadowShaderClass* m_ShadowShader;

	ModelClass *m_GroundModel1, *m_CubeModel1;	
	ProjectionShaderClass* m_ProjectionShader;
	TextureClass* m_ProjectionTexture;
	ViewPointClass* m_ViewPoint;
	LightClass* m_SpotLight;

	ID3D11ShaderResourceView *groundTexture, *cubeTexture;

	SpecMapShaderClass* m_SpecMapShader;
	ID3D11ShaderResourceView *bumpTexture, *specTexture;
	ModelClass* m_BumpSpecModel, *m_BumpSpecGround;
	LightClass* m_SpecBumpLight;
	LightClass* m_SpecBumpLight2;
};

#endif