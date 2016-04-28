#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

	numPoints = 11;
	currentPoint = 0;
	nextPoint = 1;

	//the movement point array
	movePoints = new vector3[numPoints];
	//the array of spheres
	spheres = new PrimitiveClass[numPoints];
	//the locations of the movement points
	pointLocations = new matrix4[numPoints];

	#pragma region Movement Points
		//Makes the movement points and adds them to the array
		movePoints[0] = vector3(-4.0f, -2.0f, 5.0f);
		movePoints[1] = vector3(1.0f, -2.0f, 5.0f);
		movePoints[2] = vector3(-3.0f, -1.0f, 3.0f);
		movePoints[3] = vector3(2.0f, -1.0f, 3.0f);
		movePoints[4] = vector3(-2.0f, 0.0f, 0.0f);
		movePoints[5] = vector3(3.0f, 0.0f, 0.0f);
		movePoints[6] = vector3(-1.0f, 1.0f, -3.0f);
		movePoints[7] = vector3(4.0f, 1.0f, -3.0f);
		movePoints[8] = vector3(0.0f, 2.0f, -5.0f);
		movePoints[9] = vector3(5.0f, 2.0f, -5.0f);
		movePoints[10] = vector3(1.0f, 3.0f, -5.0f);
	#pragma endregion

	for (uint i = 0; i < numPoints; i++) {
		spheres[i].GenerateSphere(0.1f, 5, RERED);		//generate a sphere for each point
		pointLocations[i] = glm::translate(movePoints[i]);	//moves the sphere to its corresponding movement point
	}
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here

	float fPercent = MapValue(static_cast<float>(fRunTime), 0.0f, fDuration, 0.0f, 1.0f);	//makes a percentage based on how close fRuntime is getting to fDuration
	vector3 move = glm::lerp(movePoints[currentPoint], movePoints[nextPoint], fPercent);	//uses the above percentage to make a vector3 that is that percentage between currentPoint and nextPoint
	moving = glm::translate(move);	//takes the above vector3 and makes a mat4 translation
	m_pMeshMngr->SetModelMatrix(moving, "WallEye");		//applies that mat4 to the walleye

	//if it gets to the movement point
	if (fRunTime > fDuration) {
		//makes it so that the new currentPoint is the one we just got to
		currentPoint = nextPoint;
		//then make nextPoint the point after that
		nextPoint++;
		//sets runtime to zero for the next cycle
		fRunTime = 0;

		//if we are on the last point, set it so that the next movement point we go to is the first one
		if (currentPoint > 9) {
			nextPoint = 0;
		}
	}

#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
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
	}

	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	for (uint i = 0; i < numPoints; i++) {
		spheres[i].Render(m4Projection, m4View, pointLocations[i]);
	}
	
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ResetRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	if (movePoints != nullptr) {
		delete[] movePoints;
		movePoints = nullptr;
	}
	if (spheres != nullptr) {
		delete[] spheres;
		spheres = nullptr;
	}
	if (pointLocations != nullptr) {
		delete[] pointLocations;
		pointLocations = nullptr;
	}
	super::Release(); //release the memory of the inherited fields
}