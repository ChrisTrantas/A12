#include "AppClass.h"
#include <random>
#include <time.h>

static inline float RandFloat( float min, float max )
{
    float norm = static_cast<float>( rand() ) / RAND_MAX;
    return ( norm * ( max - min ) ) + min;
}

void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("A12: Spatial Optimization"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(REAXISZ * 45.0f, REAXISY * 5.0f, REAXISY);

	m_pBOMngr = MyBOManager::GetInstance();

    srand( static_cast<unsigned>( time( nullptr ) ) );

    // Create some cubes
	m_nInstances = 512;
	for (int i = 0; i < m_nInstances; i++)
	{
        String sInstance = "Cube_" + std::to_string( i );
        matrix4 m4Positions = glm::translate( RandFloat( -10.0f, 10.0f ),
                                              RandFloat( -10.0f, 10.0f ),
                                              RandFloat( -10.0f, 10.0f ) );
		m_pMeshMngr->LoadModel("Minecraft\\Cube.obj", sInstance, false, m4Positions);
		m_pBOMngr->AddObject(sInstance);
	}

    // Create the octree
    _octree = std::make_shared<Octree>();

    // Ensure the octree contains everything
    size_t octreeCount = _octree->GetObjectCount();
    size_t boCount = m_pBOMngr->GetObjectCount();
    assert( octreeCount == boCount );
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update(false);

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	if (m_bSO)
	{
		for (size_t i = 0; i < m_pBOMngr->GetObjectCount(); i++)
		{
			MyBOClass* boundingObject = m_pBOMngr->GetBoundingObject(i);

			if (_octree->IsColliding(boundingObject))
				m_pBOMngr->DisplayReAlligned(i, RERED);
			else
				m_pBOMngr->DisplayReAlligned(i);
		}
	}
	else
	{
		m_pBOMngr->Update();
		m_pBOMngr->DisplayReAlligned();
	}

	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->PrintLine(std::to_string(nFPS), RERED);
	m_pMeshMngr->Print("Spatial Optimization <O> : ");
	m_pMeshMngr->PrintLine(m_bSO ? "Octree" : "Brute Force", REBLUE);
	m_pMeshMngr->Print("Display Octree <V> : ");
	m_pMeshMngr->PrintLine(m_bVisualizeSO ? "On" : "Off", REGREEN);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window

	//Render the grid based on the camera's mode:
	/* switch (m_pCameraMngr->GetCameraMode())
	{
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	} */
		
	if (m_bVisualizeSO)
		_octree->Draw();


	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	m_pBOMngr->ReleaseInstance();
	super::Release(); //release the memory of the inherited fields
}
