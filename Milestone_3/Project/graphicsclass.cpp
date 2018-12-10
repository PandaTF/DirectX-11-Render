////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_UICamera = 0;
	m_skyboxModel = 0;
	m_ambientLightShader = 0;
	m_specularLightShader = 0;
	m_textureShader = 0;
	m_Light = 0;

	m_Bitmap = 0;
	m_Text = 0;

	m_ModelList = 0;
	m_Frustum = 0;

	m_Light1 = 0;
	m_Light2 = 0;
	m_Light3 = 0;
	m_Light4 = 0;

	m_BathModel = 0;
	m_WaterModel = 0;
	m_RefractionTexture = 0;
	m_RefractionShader = 0;
	m_ReflectionTexture = 0;
	m_WaterShader = 0;

	m_CubeModel = 0;
	m_GroundModel = 0;
	m_SphereModel = 0;
	m_RenderTexture = 0;
	m_DepthShader = 0;
	m_ShadowShader = 0;

	m_GroundModel1 = 0;
	m_CubeModel1 = 0;
	m_SpotLight = 0;
	m_ProjectionShader = 0;
	m_ProjectionTexture = 0;
	m_ViewPoint = 0;

	m_SpecMapShader = 0;
	bumpTexture = 0;
	specTexture = 0;
	m_BumpSpecModel = 0;
	m_SpecBumpLight = 0;
	m_SpecBumpLight2 = 0;
	m_BumpSpecGround = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if (!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	m_UICamera = new CameraClass;
	if (!m_UICamera)
	{
		return false;
	}

	m_UICamera->SetPosition(0.0f, 0.0f, -5.0f);
	m_UICamera->Render();
	m_UICamera->GetViewMatrix(baseViewMatrix);

	// Create the light shader object.
	m_specularLightShader = new SpecularLightShaderClass;
	if (!m_specularLightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_specularLightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular light shader object.", L"Error", MB_OK);
		return false;
	}

	m_ambientLightShader = new AmbientLightShaderClass;
	if (!m_ambientLightShader)
	{
		return false;
	}

	result = m_ambientLightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ambient light shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the light object.
	m_Light = new LightClass;
	if (!m_Light)
	{
		return false;
	}

	// Create the light object.
	m_SpotLight = new LightClass;
	if (!m_SpotLight)
	{
		return false;
	}

	// Create the texture shader object.
	m_textureShader = new TextureShaderClass;
	if(!m_textureShader)
	{
		return false;
	}

	// Initialize the texture shader object.
	result = m_textureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the bitmap object.
	m_Bitmap = new BitmapClass;
	if (!m_Bitmap)
	{
		return false;
	}

	// Initialize the bitmap object.
	result = m_Bitmap->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"../Project/data/ship.dds", 256, 256);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bitmap object.", L"Error", MB_OK);
		return false;
	}

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	numFont = 5;

	// Initialize the text object.
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix, numFont);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK);
		return false;
	}

	int tempY = 20;
	for (unsigned int i = 0; i < numFont; i++)
	{
		string tempStr = "Default";
		m_Text->updateSentenceWithIndex(m_D3D->GetDeviceContext(), i, (tempStr + to_string(i)).c_str(), 20, tempY, D3DXVECTOR3(1.0f, 1.0f, 1.0f));
		tempY += 20;
	}

	// Initialize the model list
#if 1 
	const char* filename = "../Project/data/ship.txt";
	const WCHAR* textureName = L"../Project/data/ship.dds";
	filenameList.push_back(filename);
	textureList.push_back(textureName);

	const char* filename1 = "../Project/data/ship_part1.txt";
	const WCHAR* textureName1 = L"../Project/data/ship.dds";
	filenameList.push_back(filename1);
	textureList.push_back(textureName1);

	const char* filename2 = "../Project/data/ship_part2.txt";
	const WCHAR* textureName2 = L"../Project/data/ship.dds";
	filenameList.push_back(filename2);
	textureList.push_back(textureName2);

	const char* filename3 = "../Project/data/ship_part3.txt";
	const WCHAR* textureName3 = L"../Project/data/ship.dds";
	filenameList.push_back(filename3);
	textureList.push_back(textureName3);

	const char* filename4 = "../Project/data/ship_part4.txt";
	const WCHAR* textureName4 = L"../Project/data/ship.dds";
	filenameList.push_back(filename4);
	textureList.push_back(textureName4);

	const char* filename5 = "../Project/data/ship_part5.txt";
	const WCHAR* textureName5 = L"../Project/data/ship.dds";
	filenameList.push_back(filename5);
	textureList.push_back(textureName5);

	const char* filename6 = "../Project/data/ship_part6.txt";
	const WCHAR* textureName6 = L"../Project/data/ship.dds";
	filenameList.push_back(filename6);
	textureList.push_back(textureName6);

	const char* filename7 = "../Project/data/ship_part7.txt";
	const WCHAR* textureName7 = L"../Project/data/ship.dds";
	filenameList.push_back(filename7);
	textureList.push_back(textureName7);

	const char* filename8 = "../Project/data/ship_part8.txt";
	const WCHAR* textureName8 = L"../Project/data/ship.dds";
	filenameList.push_back(filename8);
	textureList.push_back(textureName8);

	const char* filename9 = "../Project/data/ship_part9.txt";
	const WCHAR* textureName9 = L"../Project/data/ship.dds";
	filenameList.push_back(filename9);
	textureList.push_back(textureName9);

	const char* filename10 = "../Project/data/ship_part10.txt";
	const WCHAR* textureName10 = L"../Project/data/ship.dds";
	filenameList.push_back(filename10);
	textureList.push_back(textureName10);

	const char* filename11 = "../Project/data/ship_part11.txt";
	const WCHAR* textureName11 = L"../Project/data/ship.dds";
	filenameList.push_back(filename11);
	textureList.push_back(textureName11);

	const char* filename12 = "../Project/data/ship_part_Fire_big_1.txt";
	const WCHAR* textureName12 = L"../Project/data/ship.dds";
	filenameList.push_back(filename12);
	textureList.push_back(textureName12);

	const char* filename13 = "../Project/data/ship_part_Fire_big_2.txt";
	const WCHAR* textureName13 = L"../Project/data/ship.dds";
	filenameList.push_back(filename13);
	textureList.push_back(textureName13);

	const char* filename14 = "../Project/data/ship_part_Fire_big_3.txt";
	const WCHAR* textureName14 = L"../Project/data/ship.dds";
	filenameList.push_back(filename14);
	textureList.push_back(textureName14);

	const char* filename15 = "../Project/data/ship_part_Fire_big_4.txt";
	const WCHAR* textureName15 = L"../Project/data/ship.dds";
	filenameList.push_back(filename15);
	textureList.push_back(textureName15);

	const char* filename16 = "../Project/data/ship_part_Fire_big_5.txt";
	const WCHAR* textureName16 = L"../Project/data/ship.dds";
	filenameList.push_back(filename16);
	textureList.push_back(textureName16);

	const char* filename17 = "../Project/data/ship_part_Fire_small_1.txt";
	const WCHAR* textureName17 = L"../Project/data/ship.dds";
	filenameList.push_back(filename17);
	textureList.push_back(textureName17);

	const char* filename18 = "../Project/data/ship_part_Fire_small_2.txt";
	const WCHAR* textureName18 = L"../Project/data/ship.dds";
	filenameList.push_back(filename18);
	textureList.push_back(textureName18);

	const char* filename19 = "../Project/data/ship_part_Fire_small_3.txt";
	const WCHAR* textureName19 = L"../Project/data/ship.dds";
	filenameList.push_back(filename19);
	textureList.push_back(textureName19);

	const char* filename20 = "../Project/data/ship_part_Fire_small_4.txt";
	const WCHAR* textureName20 = L"../Project/data/ship.dds";
	filenameList.push_back(filename20);
	textureList.push_back(textureName20);

	const char* filename21 = "../Project/data/ship_part_Fire_big_1.txt";
	const WCHAR* textureName21 = L"../Project/data/ship.dds";
	filenameList.push_back(filename21);
	textureList.push_back(textureName21);
	
	const char* filename22 = "../Project/data/ship_part_Fire_big_2.txt";
	const WCHAR* textureName22 = L"../Project/data/ship.dds";
	filenameList.push_back(filename22);
	textureList.push_back(textureName22);
	
	const char* filename23 = "../Project/data/ship_part_Fire_big_3.txt";
	const WCHAR* textureName23 = L"../Project/data/ship.dds";
	filenameList.push_back(filename23);
	textureList.push_back(textureName23);
	
	const char* filename24 = "../Project/data/ship_part_Fire_big_4.txt";
	const WCHAR* textureName24 = L"../Project/data/ship.dds";
	filenameList.push_back(filename24);
	textureList.push_back(textureName24);
	
	const char* filename25 = "../Project/data/ship_part_Fire_big_5.txt";
	const WCHAR* textureName25 = L"../Project/data/ship.dds";
	filenameList.push_back(filename25);
	textureList.push_back(textureName25);
	
	const char* filename26 = "../Project/data/ship_part_Fire_big_1.txt";
	const WCHAR* textureName26 = L"../Project/data/ship.dds";
	filenameList.push_back(filename26);
	textureList.push_back(textureName26);
	
	const char* filename27 = "../Project/data/ship_part_Fire_big_2.txt";
	const WCHAR* textureName27 = L"../Project/data/ship.dds";
	filenameList.push_back(filename27);
	textureList.push_back(textureName27);
	
	const char* filename28 = "../Project/data/ship_part_Fire_big_3.txt";
	const WCHAR* textureName28 = L"../Project/data/ship.dds";
	filenameList.push_back(filename28);
	textureList.push_back(textureName28);
	
	const char* filename29 = "../Project/data/ship_part_Fire_big_4.txt";
	const WCHAR* textureName29 = L"../Project/data/ship.dds";
	filenameList.push_back(filename29);
	textureList.push_back(textureName29);
	
	const char* filename30 = "../Project/data/ship_part_Fire_big_5.txt";
	const WCHAR* textureName30 = L"../Project/data/ship.dds";
	filenameList.push_back(filename30);
	textureList.push_back(textureName30);
	
	const char* filename31 = "../Project/data/ship_part_Fire_small_1.txt";
	const WCHAR* textureName31 = L"../Project/data/ship.dds";
	filenameList.push_back(filename31);
	textureList.push_back(textureName31);
	
	const char* filename32 = "../Project/data/ship_part_Fire_small_2.txt";
	const WCHAR* textureName32 = L"../Project/data/ship.dds";
	filenameList.push_back(filename32);
	textureList.push_back(textureName32);
	
	const char* filename33 = "../Project/data/ship_part_Fire_small_3.txt";
	const WCHAR* textureName33 = L"../Project/data/ship.dds";
	filenameList.push_back(filename33);
	textureList.push_back(textureName33);
	
	const char* filename34 = "../Project/data/ship_part_Fire_small_4.txt";
	const WCHAR* textureName34 = L"../Project/data/ship.dds";
	filenameList.push_back(filename34);
	textureList.push_back(textureName34);
#endif

	m_ModelList = new ModelListClass();
	if (!m_ModelList)
	{
		return false;
	}
	result = m_ModelList->Initialize(m_D3D->GetDevice(), filenameList, textureList, filenameList.size());
	if (!result)
	{
		return false;
	}

	// Create the model object.
	m_skyboxModel = new ModelClass;
	if (!m_skyboxModel)
	{
		return false;
	}

	// Initialize the skybox model object.
	result = m_skyboxModel->Initialize(m_D3D->GetDevice(), "../Project/data/skybox.txt", L"../Project/data/skybox.dds", false, false);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_WaterModel = new ModelClass;
	if (!m_WaterModel)
	{
		return false;
	}

	// Initialize the skybox model object.
	result = m_WaterModel->Initialize(m_D3D->GetDevice(), "../Project/data/water.txt", L"../Project/data/water01.dds", false, false);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the model object.
	m_BathModel = new ModelClass;
	if (!m_BathModel)
	{
		return false;
	}

	// Initialize the skybox model object.
	result = m_BathModel->Initialize(m_D3D->GetDevice(), "../Project/data/bath.txt", L"../Project/data/stone01.dds", false, false);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the cube model object.
	m_CubeModel = new ModelClass;
	if (!m_CubeModel)
	{
		return false;
	}
	
	// Initialize the cube model object.
	result = m_CubeModel->Initialize(m_D3D->GetDevice(), "../Project/data/cube.txt", L"../Project/data/ice01.dds", false, false);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the cube model object.", L"Error", MB_OK);
		return false;
	}
	
	// Set the position for the cube model.
	m_CubeModel->SetPosition(20.0f, 2.0f, 0.0f);
	
	// Create the sphere model object.
	m_SphereModel = new ModelClass;
	if (!m_SphereModel)
	{
		return false;
	}
	
	// Initialize the sphere model object.
	result = m_SphereModel->Initialize(m_D3D->GetDevice(), "../Project/data/sphere.txt", L"../Project/data/ice01.dds", false, false);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the sphere model object.", L"Error", MB_OK);
		return false;
	}
	
	// Set the position for the sphere model.
	m_SphereModel->SetPosition(20.0f, 4.0f, 0.0f);
	
	// Create the ground model object.
	m_GroundModel = new ModelClass;
	if (!m_GroundModel)
	{
		return false;
	}
	
	// Initialize the ground model object.
	result = m_GroundModel->Initialize(m_D3D->GetDevice(), "../Project/data/plane01.txt", L"../Project/data/ice01.dds", false, false);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ground model object.", L"Error", MB_OK);
		return false;
	}

	// Set the position for the ground model.
	m_GroundModel->SetPosition(20.0f, 1.0f, 0.0f);

	// Create the ground model object.
	m_GroundModel1 = new ModelClass;
	if (!m_GroundModel1)
	{
		return false;
	}

	// Initialize the ground model object.
	result = m_GroundModel1->Initialize(m_D3D->GetDevice(), "../Project/data/floor.txt", L"../Project/data/stone01.dds", false, false);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the ground model object.", L"Error", MB_OK);
		return false;
	}

	// Create the cube model object.
	m_CubeModel1 = new ModelClass;
	if (!m_CubeModel1)
	{
		return false;
	}

	// Initialize the cube model object.
	result = m_CubeModel1->Initialize(m_D3D->GetDevice(), "../Project/data/cube.txt", L"../Project/data/stone01.dds", false, false);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the cube model object.", L"Error", MB_OK);
		return false;
	}

	m_BumpSpecModel = new ModelClass;
	if (!m_BumpSpecModel)
	{
		return false;
	}

	result = m_BumpSpecModel->Initialize(m_D3D->GetDevice(), "../Project/data/cube1.txt", L"../Project/data/stone02.dds", false, true);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump specular cube model object.", L"Error", MB_OK);
		return false;
	}

	m_BumpSpecGround = new ModelClass;
	if (!m_BumpSpecGround)
	{
		return false;
	}

	result = m_BumpSpecGround->Initialize(m_D3D->GetDevice(), "../Project/data/plane01.txt", L"../Project/data/stone02.dds", false, true);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bump specular cube model object.", L"Error", MB_OK);
		return false;
	}

	// Create the frustum object.
	m_Frustum = new FrustumClass;
	if (!m_Frustum)
	{
		return false;
	}

	// Create the first light object.
	m_Light1 = new LightClass;
	if (!m_Light1)
	{
		return false;
	}

	// Create the second light object.
	m_Light2 = new LightClass;
	if (!m_Light2)
	{
		return false;
	}

	// Create the third light object.
	m_Light3 = new LightClass;
	if (!m_Light3)
	{
		return false;
	}

	// Create the fourth light object.
	m_Light4 = new LightClass;
	if (!m_Light4)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(64.0f);

	m_Light->SetLookAt(20.0f, 0.0f, 0.0f);
	m_Light->GenerateProjectionMatrix(SCREEN_DEPTH, SCREEN_NEAR, (float)screenWidth, (float)screenHeight);

	// Initialize the light object.
	m_SpotLight->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_SpotLight->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpotLight->SetPosition(2.0f, 5.0f, -2.0f);

	pointLightPos[0] = D3DXVECTOR3(0.0f, 0.0, 0.0f);
	pointLightPos[1] = D3DXVECTOR3(10.0f, 0.0f, 0.0f);
	pointLightPos[2] = D3DXVECTOR3(-10.0f, 0.0f, 0.0f);
	pointLightPos[3] = D3DXVECTOR3(0.0f, 10.0f, -100.0f);

	// Initialize the first light object.
	m_Light1->SetPointLightColor(1.0f, 0.0f, 0.0f, 1.0f);
	m_Light1->SetPointLightPosition(pointLightPos[0].x, pointLightPos[0].y, pointLightPos[0].z);

	// Initialize the second light object.
	m_Light2->SetPointLightColor(0.0f, 0.0f, 1.0f, 1.0f);
	m_Light2->SetPointLightPosition(pointLightPos[1].x, pointLightPos[1].y, pointLightPos[1].z);

	// Initialize the third light object.
	m_Light3->SetPointLightColor(0.0f, 1.0f, 0.0f, 1.0f);
	m_Light3->SetPointLightPosition(pointLightPos[2].x, pointLightPos[2].y, pointLightPos[2].z);

	// Initialize the fourth light object.
	m_Light4->SetPointLightColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light4->SetPointLightPosition(pointLightPos[3].x, pointLightPos[3].y, pointLightPos[3].z);

	g_tNow = g_tPre = 0;

	// Create the refraction render to texture object.
	m_RefractionTexture = new RenderTextureClass;
	if (!m_RefractionTexture)
	{
		return false;
	}

	// Initialize the refraction render to texture object.
	result = m_RefractionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the reflection render to texture object.
	m_ReflectionTexture = new RenderTextureClass;
	if (!m_ReflectionTexture)
	{
		return false;
	}

	// Initialize the reflection render to texture object.
	result = m_ReflectionTexture->Initialize(m_D3D->GetDevice(), screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the reflection render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the refraction shader object.
	m_RefractionShader = new RefractionShaderClass;
	if (!m_RefractionShader)
	{
		return false;
	}

	// Initialize the refraction shader object.
	result = m_RefractionShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the refraction shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the render to texture object.
	m_RenderTexture = new ShadowRenderTextureClass;
	if (!m_RenderTexture)
	{
		return false;
	}

	// Initialize the render to texture object.
	result = m_RenderTexture->Initialize(m_D3D->GetDevice(), SHADOWMAP_WIDTH, SHADOWMAP_HEIGHT, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the render to texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the projection texture object.
	m_ProjectionTexture = new TextureClass;
	if (!m_ProjectionTexture)
	{
		return false;
	}

	// Initialize the projection texture object.
	result = m_ProjectionTexture->Initialize(m_D3D->GetDevice(), L"../Project/data/light01.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the projection texture object.", L"Error", MB_OK);
		return false;
	}

	// Create the depth shader object.
	m_DepthShader = new DepthShaderClass;
	if (!m_DepthShader)
	{
		return false;
	}

	// Initialize the depth shader object.
	result = m_DepthShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the depth shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the shadow shader object.
	m_ShadowShader = new ShadowShaderClass;
	if (!m_ShadowShader)
	{
		return false;
	}

	// Initialize the shadow shader object.
	result = m_ShadowShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the shadow shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the water shader object.
	m_WaterShader = new WaterShaderClass;
	if (!m_WaterShader)
	{
		return false;
	}

	// Initialize the water shader object.
	result = m_WaterShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the water shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the projection shader object.
	m_ProjectionShader = new ProjectionShaderClass;
	if (!m_ProjectionShader)
	{
		return false;
	}

	// Initialize the projection shader object.
	result = m_ProjectionShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the projection shader object.", L"Error", MB_OK);
		return false;
	}

	// Create the view point object.
	m_ViewPoint = new ViewPointClass;
	if (!m_ViewPoint)
	{
		return false;
	}

	// Initialize the view point object.
	m_ViewPoint->SetPosition(0.0f, 0.0f, 0.0f);
	m_ViewPoint->SetLookAt(0.0f, 0.0f, 0.0f);
	m_ViewPoint->SetProjectionParameters((float)(D3DX_PI / 2.0f), 1.0f, 0.1f, 100.0f);
	m_ViewPoint->GenerateViewMatrix();
	m_ViewPoint->GenerateProjectionMatrix();

	m_waterHeight = 4.0f;
	m_waterTranslation = 0.0f;

	//Models Info Initialization
	InitializeShipParts();
	D3DX11CreateShaderResourceViewFromFile(m_D3D->GetDevice(), L"../Project/data/ice01.dds", NULL, NULL, &groundTexture, NULL);
	D3DX11CreateShaderResourceViewFromFile(m_D3D->GetDevice(), L"../Project/data/ice.dds", NULL, NULL, &cubeTexture, NULL);

	// Create the specular map shader object.
	m_SpecMapShader = new SpecMapShaderClass;
	if (!m_SpecMapShader)
	{
		return false;
	}

	// Initialize the specular map shader object.
	result = m_SpecMapShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the specular map shader object.", L"Error", MB_OK);
		return false;
	}

	D3DX11CreateShaderResourceViewFromFile(m_D3D->GetDevice(), L"../Project/data/bump02.dds", NULL, NULL, &bumpTexture, NULL);
	D3DX11CreateShaderResourceViewFromFile(m_D3D->GetDevice(), L"../Project/data/spec02.dds", NULL, NULL, &specTexture, NULL);

	m_SpecBumpLight = new LightClass;
	if(!m_SpecBumpLight)
	{
		return false;
	}

	m_SpecBumpLight->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_SpecBumpLight->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecBumpLight->SetDirection(0.0f, 1.0f, 1.0f);
	m_SpecBumpLight->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecBumpLight->SetSpecularPower(32.0f);

	m_SpecBumpLight2 = new LightClass;
	if (!m_SpecBumpLight2)
	{
		return false;
	}

	m_SpecBumpLight2->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_SpecBumpLight2->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecBumpLight2->SetDirection(0.0f, -0.5f, -1.0f);
	m_SpecBumpLight2->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_SpecBumpLight2->SetSpecularPower(256.0f);

	return true;
}

void GraphicsClass::Shutdown()
{
	// Release the specular map shader object.
	if (m_SpecMapShader)
	{
		m_SpecMapShader->Shutdown();
		delete m_SpecMapShader;
		m_SpecMapShader = 0;
	}

	if (m_SpecBumpLight)
	{
		delete m_SpecBumpLight;
		m_SpecBumpLight = 0;
	}

	if (m_SpecBumpLight2)
	{
		delete m_SpecBumpLight2;
		m_SpecBumpLight2 = 0;
	}

	if (m_BumpSpecModel)
	{
		m_BumpSpecModel->Shutdown();
		delete m_BumpSpecModel;
		m_BumpSpecModel = 0;
	}

	if (m_BumpSpecGround)
	{
		m_BumpSpecGround->Shutdown();
		delete m_BumpSpecGround;
		m_BumpSpecGround = 0;
	}

	if (bumpTexture)
	{
		bumpTexture->Release();
		bumpTexture = 0;
	}

	if (specTexture)
	{
		specTexture->Release();
		specTexture = 0;
	}

	if (groundTexture)
	{
		groundTexture->Release();
		groundTexture = 0;
	}

	if (cubeTexture)
	{
		cubeTexture->Release();
		cubeTexture = 0;
	}

	// Release the view point object.
	if (m_ViewPoint)
	{
		delete m_ViewPoint;
		m_ViewPoint = 0;
	}

	// Release the projection texture object.
	if (m_ProjectionTexture)
	{
		m_ProjectionTexture->Shutdown();
		delete m_ProjectionTexture;
		m_ProjectionTexture = 0;
	}

	// Release the projection shader object.
	if (m_ProjectionShader)
	{
		m_ProjectionShader->Shutdown();
		delete m_ProjectionShader;
		m_ProjectionShader = 0;
	}

	// Release the light object.
	if (m_SpotLight)
	{
		delete m_SpotLight;
		m_SpotLight = 0;
	}

	// Release the shadow shader object.
	if (m_ShadowShader)
	{
		m_ShadowShader->Shutdown();
		delete m_ShadowShader;
		m_ShadowShader = 0;
	}

	// Release the depth shader object.
	if (m_DepthShader)
	{
		m_DepthShader->Shutdown();
		delete m_DepthShader;
		m_DepthShader = 0;
	}

	// Release the render to texture object.
	if (m_RenderTexture)
	{
		m_RenderTexture->Shutdown();
		delete m_RenderTexture;
		m_RenderTexture = 0;
	}

	// Release the ground model object.
	if (m_GroundModel)
	{
		m_GroundModel->Shutdown();
		delete m_GroundModel;
		m_GroundModel = 0;
	}
	
	// Release the sphere model object.
	if (m_SphereModel)
	{
		m_SphereModel->Shutdown();
		delete m_SphereModel;
		m_SphereModel = 0;
	}
	
	// Release the cube model object.
	if (m_CubeModel)
	{
		m_CubeModel->Shutdown();
		delete m_CubeModel;
		m_CubeModel = 0;
	}

	// Release the cube model object.
	if (m_CubeModel1)
	{
		m_CubeModel1->Shutdown();
		delete m_CubeModel1;
		m_CubeModel1 = 0;
	}

	// Release the ground model object.
	if (m_GroundModel1)
	{
		m_GroundModel1->Shutdown();
		delete m_GroundModel1;
		m_GroundModel1 = 0;
	}

	// Release the water shader object.
	if (m_WaterShader)
	{
		m_WaterShader->Shutdown();
		delete m_WaterShader;
		m_WaterShader = 0;
	}

	// Release the refraction shader object.
	if (m_RefractionShader)
	{
		m_RefractionShader->Shutdown();
		delete m_RefractionShader;
		m_RefractionShader = 0;
	}

	// Release the reflection render to texture object.
	if (m_ReflectionTexture)
	{
		m_ReflectionTexture->Shutdown();
		delete m_ReflectionTexture;
		m_ReflectionTexture = 0;
	}

	// Release the refraction render to texture object.
	if (m_RefractionTexture)
	{
		m_RefractionTexture->Shutdown();
		delete m_RefractionTexture;
		m_RefractionTexture = 0;
	}

	// Release the light objects.
	if (m_Light1)
	{
		delete m_Light1;
		m_Light1 = 0;
	}

	if (m_Light2)
	{
		delete m_Light2;
		m_Light2 = 0;
	}

	if (m_Light3)
	{
		delete m_Light3;
		m_Light3 = 0;
	}

	if (m_Light4)
	{
		delete m_Light4;
		m_Light4 = 0;
	}

	// Release the bitmap object.
	if (m_Bitmap)
	{
		m_Bitmap->Shutdown();
		delete m_Bitmap;
		m_Bitmap = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	if (m_textureShader)
	{
		m_textureShader->Shutdown();
		delete m_textureShader;
		m_textureShader = 0;
	}

	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	if (m_ambientLightShader)
	{
		m_ambientLightShader->Shutdown();
		delete m_ambientLightShader;
		m_ambientLightShader = 0;
	}

	// Release the light shader object.
	if(m_specularLightShader)
	{
		m_specularLightShader->Shutdown();
		delete m_specularLightShader;
		m_specularLightShader = 0;
	}

	// Release the model object.
	if(m_skyboxModel)
	{
		m_skyboxModel->Shutdown();
		delete m_skyboxModel;
		m_skyboxModel = 0;
	}

	if (m_WaterModel)
	{
		m_WaterModel->Shutdown();
		delete m_WaterModel;
		m_WaterModel = 0;
	}

	if (m_BathModel)
	{
		m_BathModel->Shutdown();
		delete m_BathModel;
		m_BathModel = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	if (m_UICamera)
	{
		delete m_UICamera;
		m_UICamera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	if (m_ModelList)
	{
		m_ModelList->Shutdown();
		delete m_ModelList;
		m_ModelList = 0;
	}

	// Release the frustum object.
	if (m_Frustum)
	{
		delete m_Frustum;
		m_Frustum = 0;
	}

	return;
}

bool GraphicsClass::Frame(int fps, int cpu, float frameTime, int mouseX, int mouseY, D3DXVECTOR3 position, D3DXVECTOR3 rotation, unsigned int LightType)
{
	bool result;
	static float deg = 0.0f;
	static float spot_deg = 0.0f;

	lightType = LightType;

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext(),0);
	if (!result)
	{
		return false;
	}

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext(), 1);
	if (!result)
	{
		return false;
	}

	// Update the location of the mouse
	result = m_Text->UpdateMousePositionInfo(mouseX, mouseY, m_D3D->GetDeviceContext(), 2, 3);
	if (!result)
	{
		return false;
	}

	switch (lightType)
	{
	case 1: //Light On
		m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
		m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light->SetSpecularPower(64.0f);

		m_Light1->SetPointLightColor(0.0f, 0.0f, 0.0f, 0.0f);
		m_Light2->SetPointLightColor(0.0f, 0.0f, 0.0f, 0.0f);
		m_Light3->SetPointLightColor(0.0f, 0.0f, 0.0f, 0.0f);
		m_Light4->SetPointLightColor(0.0f, 0.0f, 0.0f, 0.0f);

		break;

	case 2: //Light Off
		m_Light->SetAmbientColor(0.0f, 0.0f, 0.0f, 0.0f);
		m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 0.0f);
		m_Light->SetSpecularColor(0.0f, 0.0f, 0.0f, 0.0f);
		m_Light->SetSpecularPower(100000000000.0f);

		//PointLight 1 Red
		pointLightPos[0].x += 0.5f;
		if (pointLightPos[0].x > 100.0f)
			pointLightPos[0].x -= 200.0f;

		m_Light1->SetPointLightColor(1.0f, 0.0f, 0.0f, 1.0f);
		m_Light1->SetPointLightPosition(pointLightPos[0].x, pointLightPos[0].y, pointLightPos[0].z);

		//PointLight 2 Blue
		pointLightPos[1].z += 0.5f;
		if (pointLightPos[1].z > 100.0f)
			pointLightPos[1].z -= 200.0f;

		m_Light2->SetPointLightColor(0.0f, 0.0f, 1.0f, 1.0f);
		m_Light2->SetPointLightPosition(pointLightPos[1].x, pointLightPos[1].y, pointLightPos[1].z);

		//PointLight 3 Green
		pointLightPos[2].z -= 0.5f;
		if (pointLightPos[2].z < -100.0f)
			pointLightPos[2].z += 200.0f;

		m_Light3->SetPointLightColor(0.0f, 1.0f, 0.0f, 1.0f);
		m_Light3->SetPointLightPosition(pointLightPos[2].x, pointLightPos[2].y, pointLightPos[2].z);

		//PointLight 4 Yellow
		pointLightPos[3].y -= 0.5f;
		if (pointLightPos[3].y < -100.0f)
			pointLightPos[3].y += 200.0f;

		m_Light4->SetPointLightColor(1.0f, 1.0f, 1.0f, 1.0f);
		m_Light4->SetPointLightPosition(pointLightPos[3].x, pointLightPos[3].y, pointLightPos[3].z);
		break;
	case 3:
		break;
	}

	deg += 0.01f;
	if (deg > 360.0f)
		deg -= 360.0f;

	float lengthX, lengthZ;
	lengthX = cosf(deg);
	lengthZ = sinf(deg);
	m_Light->SetDirection(1 * lengthX, -0.4f, 1 * lengthZ);

	// Update the position of the light.
	m_Light->SetPosition(-5*lengthX + 20.0f, 15.0f, -5* lengthZ);

	// Update the position of the water to simulate motion.
	m_waterTranslation += 0.0005f;
	if (m_waterTranslation > 1.0f)
	{
		m_waterTranslation -= 1.0f;
	}

	m_Camera->SetPosition(position.x, position.y, position.z);
	m_Camera->SetRotation(rotation.x, rotation.y, rotation.z);
	m_UICamera->SetPosition(0.0f, 0.0f, -5.0f);

	spot_deg += 0.01f;
	if (spot_deg > 360.0f)
		spot_deg -= 360.0f;

	float spot_lengthX, spot_lengthZ;
	spot_lengthX = cosf(spot_deg);
	spot_lengthZ = sinf(spot_deg);
	m_ViewPoint->SetPosition(2.0f*spot_lengthX - 20.0f, 5.0f, -2.0f*spot_lengthZ);
	m_ViewPoint->SetLookAt(-20.0f, 0.0f, 0.0f);
	m_ViewPoint->GenerateViewMatrix();
	m_ViewPoint->GenerateProjectionMatrix();

	m_SpotLight->SetPosition(2.0f*spot_lengthX - 20.0f, 5.0f, -2.0f*spot_lengthZ);
	m_SpotLight->SetDirection(-spot_lengthX, -0.4f, spot_lengthZ);

	return true;
}

bool GraphicsClass::Render()
{
	bool result;

	result = RenderRefractionToTexture();
	if (!result)
	{
		return false;
	}
	
	result = RenderReflectionToTexture();
	if (!result)
	{
		return false;
	}

	result = RenderScene();
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::InitializeShipParts()
{
	m_ModelList->SetModelRadius(0, 10.0f);
	m_ModelList->SetModelScaling(0, 0.05f, 0.05f, 0.05f);
	m_ModelList->SetModelRotation(0, 0.0f, 0.0f, 0.0f);
	m_ModelList->SetModelPosition(0, 0.0f, 60.0f, 0.0f);

	for (unsigned int i = 1; i <= 20; i++)
	{
		m_ModelList->SetModelRadius(i, 5.0f);
		m_ModelList->SetModelScaling(i, 0.05f, 0.05f, 0.05f);
		m_ModelList->SetModelRotation(i, 0.0f, 0.0f, 0.0f);
		m_ModelList->SetModelPosition(i, 0.0f, 60.0f, 0.0f);
	}

	for (unsigned int i = 21; i <= 25; i++)
	{
		m_ModelList->SetModelRadius(i, 5.0f);
		m_ModelList->SetModelScaling(i, 0.05f, 0.05f, 0.05f);
		m_ModelList->SetModelRotation(i, 0.0f, 0.0f, 0.0f);
		m_ModelList->SetModelPosition(i, 0.0f, 64.0f, 21.0f);
	}
	
	for (unsigned int i = 26; i <= 30; i++)
	{
		m_ModelList->SetModelRadius(i, 5.0f);
		m_ModelList->SetModelScaling(i, 0.05f, 0.05f, 0.05f);
		m_ModelList->SetModelRotation(i, 0.0f, 180.0f, 0.0f);
		m_ModelList->SetModelPosition(i, 0.0f, 63.0f, 8.0f);
	}
	
	for (unsigned int i = 31; i <= 34; i++)
	{
		m_ModelList->SetModelRadius(i, 5.0f);
		m_ModelList->SetModelScaling(i, 0.05f, 0.05f, 0.05f);
		m_ModelList->SetModelRotation(i, 0.0f, 180.0f, 0.0f);
		m_ModelList->SetModelPosition(i, 0.0f, 59.0f, -11.0f);
	}

	fireClockwise = true;

	return true;
}

bool GraphicsClass::UpdateShipParts()
{
	if (fireClockwise)
	{
		fireRotateY += 0.001f;
		if (fireRotateY >= 30.0f)
		{
			fireClockwise = false;
			fireRotateY = 30.0f;
		}
	}
	else
	{
		fireRotateY -= 0.001f;
		if (fireRotateY <= -30.0f)
		{
			fireClockwise = true;
			fireRotateY = -30.0f;
		}
	}

	for (unsigned int i = 21; i <= 25; i++)
	{
		m_ModelList->SetModelRotation(i, 0.0f, fireRotateY, 0.0f);
		
		D3DXMATRIX rotateYMatrix = {
			cosf(-fireRotateY), 0,	sinf(-fireRotateY),	0,
			0,					1,	0,					0,
			-sinf(-fireRotateY),0,	cos(-fireRotateY),	0,
			0,					0,	0,					1
		};
		
		D3DXMATRIX wm = m_ModelList->GetModelWorldMatrix(i);
		wm = wm * rotateYMatrix;
		
		m_ModelList->SetModelWorldMatrix(i, wm);
	}

	return true;
}

bool GraphicsClass::RenderScene()
{

	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, orthoMatrix, reflectionMatrix;
	D3DXMATRIX lightViewMatrix, lightProjectionMatrix;
	D3DXMATRIX viewMatrix2, projectionMatrix2;
	float posX, posY, posZ;
	bool result;
	int renderCount, modelCount;

	D3DXMATRIX skyBoxMatrix;
	D3DXMATRIX bitmapMatrix, bitmapViewMatrix, fontMatrix, fontViewMatrix;
	D3DXVECTOR4 pointLightColor[4];
	D3DXVECTOR4 pointLightPosition[4];

	static float degree = 0.0f;
	// Update the rotation variable each frame.
	degree += (float)D3DX_PI * 0.05f;
	if (degree > 360.0f)
	{
		degree -= 360.0f;
	}

	// First render the scene to a texture.
	result = RenderSceneToTexture();
	if (!result)
	{
		return false;
	}

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.1f, 0.1f, 0.1f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Generate the light view matrix based on the light's position.
	m_Light->GenerateViewMatrix();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Get the light's view and projection matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	// Get the view and projection matrices from the view point object.
	m_ViewPoint->GetViewMatrix(viewMatrix2);
	m_ViewPoint->GetProjectionMatrix(projectionMatrix2);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Construct the frustum.
	m_Frustum->ConstructFrustum(SCREEN_DEPTH, projectionMatrix, viewMatrix);

	// Get the number of models
	modelCount = m_ModelList->GetNumOfModels();

	// Initialize the count of models that have been rendered.
	renderCount = 0;

	vector<ModelClass*> modelList;
	modelList = m_ModelList->GetModelList();

	//UpdateShipParts();

	// Go through all the models and render them only if they can be seen by the camera view.
	for (int index = 0; index<modelCount; index++)
	{
		D3DXVECTOR3 position = m_ModelList->GetModelPosition(index);
		float radius = m_ModelList->GetmodelRadius(index);

		// Check if the sphere model is in the view frustum.
		result = m_Frustum->CheckSphere(position.x / 20.0f, position.y / 20.0f, position.z / 20.0f, radius);

		if (result)
		{
			D3DXVECTOR3 rotation = m_ModelList->GetModelRotation(index);
			D3DXVECTOR3 scaling = m_ModelList->GetModelScaling(index);

			D3DXMATRIX thisWorldMatrix = m_ModelList->GetModelWorldMatrix(index);
			D3DXMATRIX t, r, s;


			//T
			D3DXMatrixTranslation(&t, position.x, position.y, position.z);
			D3DXMatrixMultiply(&thisWorldMatrix, &thisWorldMatrix, &t);

			//R
			D3DXMatrixRotationYawPitchRoll(&r, (float)D3DXToRadian(rotation.y), (float)D3DXToRadian(rotation.x), (float)D3DXToRadian(rotation.z));
			D3DXMatrixMultiply(&thisWorldMatrix, &r, &thisWorldMatrix);

			//S
			D3DXMatrixScaling(&s, scaling.x, scaling.y, scaling.z);
			D3DXMatrixMultiply(&thisWorldMatrix, &thisWorldMatrix, &s);

			D3DXMatrixMultiply(&thisWorldMatrix, &thisWorldMatrix, &worldMatrix);
			modelList[index]->Render(m_D3D->GetDeviceContext());

			// Render the model using the specular light shader.
			// Create the diffuse color array from the four light colors.
			pointLightColor[0] = m_Light1->GetPointLightColor();
			pointLightColor[1] = m_Light2->GetPointLightColor();
			pointLightColor[2] = m_Light3->GetPointLightColor();
			pointLightColor[3] = m_Light4->GetPointLightColor();

			// Create the light position array from the four light positions.
			pointLightPosition[0] = m_Light1->GetPointLightPosition();
			pointLightPosition[1] = m_Light2->GetPointLightPosition();
			pointLightPosition[2] = m_Light3->GetPointLightPosition();
			pointLightPosition[3] = m_Light4->GetPointLightPosition();

			result = m_specularLightShader->Render(m_D3D->GetDeviceContext(), modelList[index]->GetIndexCount(),
				thisWorldMatrix, viewMatrix, projectionMatrix,
				modelList[index]->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(), pointLightColor, pointLightPosition);

			if (!result)
			{
				return false;
			}

			renderCount++;
		}
	}

	//Sky Box
	m_Light->SetDiffuseColor(0.0f, 0.0f, 0.0f, 1.0f);
	m_Light->SetAmbientColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	m_D3D->GetWorldMatrix(skyBoxMatrix);
	m_skyboxModel->Render(m_D3D->GetDeviceContext());
	
	D3DXMATRIX skyBoxR, skyBoxT, skyBoxS;
	
	D3DXMatrixIdentity(&skyBoxS);
	D3DXMatrixScaling(&skyBoxS, SCREEN_DEPTH, SCREEN_DEPTH, SCREEN_DEPTH);
	D3DXMatrixMultiply(&skyBoxMatrix, &skyBoxMatrix, &skyBoxS);
	float cX, cY, cZ;
	cX = m_Camera->GetPosition().x;
	cY = m_Camera->GetPosition().y;
	cZ = m_Camera->GetPosition().z;
	D3DXMatrixTranslation(&skyBoxT, cX, cY, cZ);
	D3DXMatrixMultiply(&skyBoxMatrix, &skyBoxMatrix, &skyBoxT);
	
	result = m_ambientLightShader->Render(m_D3D->GetDeviceContext(), m_skyboxModel->GetIndexCount(), skyBoxMatrix, viewMatrix, projectionMatrix,
		m_skyboxModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);


	if (lightType == 1)
	{
		D3DXMATRIX R, T, S;
	
		// Reset the world matrix.
		m_D3D->GetWorldMatrix(worldMatrix);
	
		result = m_Frustum->CheckCube(0.0f, 2.0f, -1.0f, 10.0f);
		if (result)
		{		// Translate to where the bath model will be rendered.
			D3DXMatrixScaling(&S, 2.0f, 1.0f, 2.0f);
			D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &S);
	
			D3DXMatrixTranslation(&T, 0.0f, 2.0f, -1.0f);
			D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &T);
	
			// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_BathModel->Render(m_D3D->GetDeviceContext());
	
			// Render the bath model using the light shader.
			result = m_specularLightShader->Render(m_D3D->GetDeviceContext(), m_BathModel->GetIndexCount(),
				worldMatrix, viewMatrix, projectionMatrix,
				m_BathModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
				m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower(),
				pointLightColor, pointLightPosition);
			if (!result)
			{
				return false;
			}
	
			// Reset the world matrix.
			m_D3D->GetWorldMatrix(worldMatrix);
			renderCount++;
		}
	
		result = m_Frustum->CheckRectangle(0.0f, 2.0f, -1.0f, 10.0f, 1.0f, 10.0f);
	
		if (result)
		{
			// Get the camera reflection view matrix.
			reflectionMatrix = m_Camera->GetReflectionViewMatrix();
	
			// Translate to where the water model will be rendered.
			D3DXMatrixScaling(&S, 2.0f, 1.0f, 2.0f);
			D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &S);
	
			D3DXMatrixTranslation(&T, 0.0f, 2.7f, -1.0f);
			D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &T);
	
			// Put the water model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_WaterModel->Render(m_D3D->GetDeviceContext());
	
			m_D3D->TurnOnAlphaBlending();
			// Render the water model using the water shader.
			result = m_WaterShader->Render(m_D3D->GetDeviceContext(), m_WaterModel->GetIndexCount(), worldMatrix, viewMatrix,
				projectionMatrix, reflectionMatrix, m_ReflectionTexture->GetShaderResourceView(),
				m_RefractionTexture->GetShaderResourceView(), m_WaterModel->GetTexture(),
				m_waterTranslation, 0.04f, m_waterHeight);
			if (!result)
			{
				return false;
			}
	
			m_D3D->TurnOffAlphaBlending();
	
			// Reset the world matrix.
			m_D3D->GetWorldMatrix(worldMatrix);
	
			renderCount++;
		}
	}
	
	m_D3D->GetWorldMatrix(worldMatrix);
	
	// Setup the translation matrix for the cube model.
	m_CubeModel->GetPosition(posX, posY, posZ);
	D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);
	
	// Put the cube model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_CubeModel->Render(m_D3D->GetDeviceContext());
	
	// Render the model using the shadow shader.
	result = m_ShadowShader->Render(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_CubeModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}
	
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);
	
	// Setup the translation matrix for the sphere model.
	m_SphereModel->GetPosition(posX, posY, posZ);
	D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);
	
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_SphereModel->Render(m_D3D->GetDeviceContext());
	result = m_ShadowShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_SphereModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}
	
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);
	
	// Setup the translation matrix for the ground model.
	m_GroundModel->GetPosition(posX, posY, posZ);
	D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);
	
	// Render the ground model using the shadow shader.
	m_GroundModel->Render(m_D3D->GetDeviceContext());
	result = m_ShadowShader->Render(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, lightViewMatrix,
		lightProjectionMatrix, m_GroundModel->GetTexture(), m_RenderTexture->GetShaderResourceView(), m_Light->GetPosition(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	if (!result)
	{
		return false;
	}
	
	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Setup the translation for the ground model.
	D3DXMatrixTranslation(&worldMatrix, -20.0f, 1.0f, 0.0f);
	

	// Render the ground model using the projection shader.
	m_GroundModel1->Render(m_D3D->GetDeviceContext());
	result = m_ProjectionShader->Render(m_D3D->GetDeviceContext(), m_GroundModel1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
					    m_GroundModel1->GetTexture(), groundTexture, m_SpotLight->GetAmbientColor(), m_SpotLight->GetDiffuseColor(), m_SpotLight->GetPosition(),
					    viewMatrix2, projectionMatrix2, m_ProjectionTexture->GetTexture(), m_SpotLight->GetDirection());
	if(!result)
	{
		return false;
	}

	// Reset the world matrix and setup the translation for the cube model.
	m_D3D->GetWorldMatrix(worldMatrix);
	D3DXMatrixTranslation(&worldMatrix, -20.0f, 2.0f, 0.0f);

	// Render the cube model using the projection shader.
	m_CubeModel1->Render(m_D3D->GetDeviceContext());
	result = m_ProjectionShader->Render(m_D3D->GetDeviceContext(), m_CubeModel1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
					    m_CubeModel1->GetTexture(), cubeTexture, m_SpotLight->GetAmbientColor(), m_SpotLight->GetDiffuseColor(), m_SpotLight->GetPosition(),
					    viewMatrix2, projectionMatrix2, m_ProjectionTexture->GetTexture(), m_SpotLight->GetDirection());
	if(!result)
	{
		return false;
	}

	D3DXMATRIX specT, specR, specS;
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	D3DXMatrixRotationY(&specR, (float)D3DXToRadian(degree));
	worldMatrix *= specR;
	D3DXMatrixTranslation(&specT, 0.0f, 1.0f, 20.0f);
	worldMatrix *= specT;

	ID3D11ShaderResourceView **textureArray = new ID3D11ShaderResourceView*[3];
	textureArray[0] = m_BumpSpecModel->GetTexture();
	textureArray[1] = bumpTexture;
	textureArray[2] = specTexture;

	m_BumpSpecModel->Render(m_D3D->GetDeviceContext());

	m_SpecMapShader->Render(m_D3D->GetDeviceContext(), m_BumpSpecModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		textureArray, m_SpecBumpLight->GetDirection(), m_SpecBumpLight->GetDiffuseColor(),
		m_Camera->GetPosition(), m_SpecBumpLight->GetSpecularColor(), m_SpecBumpLight->GetSpecularPower(), m_SpecBumpLight->GetAmbientColor());

	m_D3D->GetWorldMatrix(worldMatrix);
	//D3DXMatrixRotationX(&specR, (float)D3DXToRadian(270.0f));
	//worldMatrix *= specR;
	D3DXMatrixTranslation(&specT, 0.0f, 0.0f, 20.0f);
	worldMatrix *= specT;

	m_BumpSpecGround->Render(m_D3D->GetDeviceContext());

	m_SpecMapShader->Render(m_D3D->GetDeviceContext(), m_BumpSpecGround->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		textureArray, m_SpecBumpLight2->GetDirection(), m_SpecBumpLight2->GetDiffuseColor(),
		m_Camera->GetPosition(), m_SpecBumpLight2->GetSpecularColor(), m_SpecBumpLight2->GetSpecularPower(), m_SpecBumpLight2->GetAmbientColor());

	delete[] textureArray;

	m_Text->SetRenderCount(renderCount, m_D3D->GetDeviceContext(), 4);
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//// Turn off the Z buffer to begin all 2D rendering.
	m_D3D->TurnZBufferOff();

	//m_UICamera->Render();
	//m_UICamera->GetViewMatrix(bitmapViewMatrix);
	//m_D3D->GetWorldMatrix(bitmapMatrix);
	//
	//
	//// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 50, 900, 100, 100);
	//if (!result)
	//{
	//	return false;
	//}
	//
	//// Render the bitmap with the texture shader.
	//result = m_textureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), bitmapMatrix, 
	//	bitmapViewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	m_UICamera->Render();
	m_UICamera->GetViewMatrix(fontViewMatrix);
	m_D3D->GetWorldMatrix(fontMatrix);

	// Turn on the alpha blending before rendering the text.
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings.
	result = m_Text->Render(m_D3D->GetDeviceContext(), fontViewMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text.
	m_D3D->TurnOffAlphaBlending();

	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

bool GraphicsClass::RenderSceneToTexture()
{
	D3DXMATRIX worldMatrix, lightViewMatrix, lightProjectionMatrix, translateMatrix;
	float posX, posY, posZ;
	bool result;

	// Set the render target to be the render to texture.
	m_RenderTexture->SetRenderTarget(m_D3D->GetDeviceContext());

	// Clear the render to texture.
	m_RenderTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the light view matrix based on the light's position.
	m_Light->GenerateViewMatrix();

	// Get the world matrix from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Get the view and orthographic matrices from the light object.
	m_Light->GetViewMatrix(lightViewMatrix);
	m_Light->GetProjectionMatrix(lightProjectionMatrix);

	// Setup the translation matrix for the cube model.
	m_CubeModel->GetPosition(posX, posY, posZ);
	D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

	// Render the cube model with the depth shader.
	m_CubeModel->Render(m_D3D->GetDeviceContext());
	result = m_DepthShader->Render(m_D3D->GetDeviceContext(), m_CubeModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Setup the translation matrix for the sphere model.
	m_SphereModel->GetPosition(posX, posY, posZ);
	D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

	// Render the sphere model with the depth shader.
	m_SphereModel->Render(m_D3D->GetDeviceContext());
	result = m_DepthShader->Render(m_D3D->GetDeviceContext(), m_SphereModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the world matrix.
	m_D3D->GetWorldMatrix(worldMatrix);

	// Setup the translation matrix for the ground model.
	m_GroundModel->GetPosition(posX, posY, posZ);
	D3DXMatrixTranslation(&worldMatrix, posX, posY, posZ);

	// Render the ground model with the depth shader.
	m_GroundModel->Render(m_D3D->GetDeviceContext());
	result = m_DepthShader->Render(m_D3D->GetDeviceContext(), m_GroundModel->GetIndexCount(), worldMatrix, lightViewMatrix, lightProjectionMatrix);
	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::RenderRefractionToTexture()
{
	D3DXVECTOR4 clipPlane;
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Setup a clipping plane based on the height of the water to clip everything above it.
	clipPlane = D3DXVECTOR4(0.0f, -1.0f, 0.0f, m_waterHeight + 0.1f);

	// Set the render target to be the refraction render to texture.
	m_RefractionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the refraction render to texture.
	m_RefractionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	D3DXMATRIX R, T, S;
	// Translate to where the bath model will be rendered.
	D3DXMatrixScaling(&S, 2.0f, 1.0f, 2.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &S);

	D3DXMatrixTranslation(&T, 0.0f, 2.0f, -1.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &T);

	// Put the bath model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BathModel->Render(m_D3D->GetDeviceContext());

	// Render the bath model using the light shader.
	result = m_RefractionShader->Render(m_D3D->GetDeviceContext(), m_BathModel->GetIndexCount(), worldMatrix, viewMatrix,
		projectionMatrix, m_BathModel->GetTexture(), m_Light->GetDirection(),
		m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), clipPlane);

	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}

bool GraphicsClass::RenderReflectionToTexture()
{
	D3DXMATRIX reflectionViewMatrix, worldMatrix, projectionMatrix;
	bool result;

	// Set the render target to be the reflection render to texture.
	m_ReflectionTexture->SetRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView());

	// Clear the reflection render to texture.
	m_ReflectionTexture->ClearRenderTarget(m_D3D->GetDeviceContext(), m_D3D->GetDepthStencilView(), 0.0f, 0.0f, 0.0f, 1.0f);

	// Use the camera to render the reflection and create a reflection view matrix.
	m_Camera->RenderReflection(m_waterHeight);

	// Get the camera reflection view matrix instead of the normal view matrix.
	reflectionViewMatrix = m_Camera->GetReflectionViewMatrix();

	// Get the world and projection matrices from the d3d object.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);


	D3DXMATRIX r, t, s;
	//S
	D3DXMatrixScaling(&s, m_ModelList->GetModelScaling(0).x, m_ModelList->GetModelScaling(0).y, m_ModelList->GetModelScaling(0).z);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &s);

	//R
	D3DXMatrixRotationZ(&r, (float)D3DXToRadian(180.0f));
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &r);

	//T
	D3DXMatrixTranslation(&t, 0.0f, 2.2f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &t);

	// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.

	unsigned int numOfParts = m_ModelList->GetNumOfModels();

	for (unsigned int i = 0; i < numOfParts; i++)
	{
		m_ModelList->GetModelList()[i]->Render(m_D3D->GetDeviceContext());
		// Render the wall model using the light shader and the reflection view matrix.
		result = m_ambientLightShader->Render(m_D3D->GetDeviceContext(), m_ModelList->GetModelList()[i]->GetIndexCount(), worldMatrix, reflectionViewMatrix,
			projectionMatrix, m_ModelList->GetModelList()[i]->GetTexture(), m_Light->GetDirection(),
			m_Light->GetAmbientColor(), m_Light->GetDiffuseColor());
	}

	if (!result)
	{
		return false;
	}

	// Reset the render target back to the original back buffer and not the render to texture anymore.
	m_D3D->SetBackBufferRenderTarget();

	// Reset the viewport back to the original.
	m_D3D->ResetViewport();

	return true;
}
