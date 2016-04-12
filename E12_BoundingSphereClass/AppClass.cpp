#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("MyBoundingSphereClass example"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");

<<<<<<< HEAD

	//steve
	std::vector<vector3> listOfVertex = m_pMeshMngr->GetVertexList("Steve");
	uint nCount = listOfVertex.size();
=======
	std::vector<vector3> vertexList = m_pMeshMngr->GetVertexList("Steve");
	uint nVertexCount = vertexList.size();
>>>>>>> 24bcaaa6312502f76083515adcd9fefd5a7048a7

	vector3 v3Min;
	vector3 v3Max;

<<<<<<< HEAD
	if (nCount > 0) {
		v3Min = listOfVertex[0];
		v3Max = listOfVertex[0];
	}
	for (uint i = 0; i < nCount; i++) {
		if (listOfVertex[i].x < v3Min.x) {
			v3Min.x = listOfVertex[i].x;
		}
		else if (listOfVertex[i].x > v3Max.x) {
			v3Max.x = listOfVertex[i].x;
		}
		if (listOfVertex[i].y < v3Min.y) {
			v3Min.y = listOfVertex[i].y;
		}
		else if (listOfVertex[i].y > v3Max.y) {
			v3Max.y = listOfVertex[i].y;
		}
		if (listOfVertex[i].z < v3Min.z) {
			v3Min.z = listOfVertex[i].z;
		}
		else if (listOfVertex[i].z > v3Max.z) {
			v3Max.z = listOfVertex[i].z;
		}
	}

	v3Center = (v3Min + v3Max) / 2.0f;
	float fRadius = glm::distance(v3Center, v3Max);

	pSphere1 = new PrimitiveClass();
	pSphere1->GenerateSphere(fRadius, 5, REGREEN);


	//creeper
	std::vector<vector3> listOfVertex2 = m_pMeshMngr->GetVertexList("Creeper");
	nCount = listOfVertex2.size();

	if (nCount > 0) {
		v3Min = listOfVertex2[0];
		v3Max = listOfVertex2[0];
	}
	for (uint i = 0; i < nCount; i++) {
		if (listOfVertex2[i].x < v3Min.x) {
			v3Min.x = listOfVertex2[i].x;
		}
		else if (listOfVertex2[i].x > v3Max.x) {
			v3Max.x = listOfVertex2[i].x;
		}
		if (listOfVertex2[i].y < v3Min.y) {
			v3Min.y = listOfVertex2[i].y;
		}
		else if (listOfVertex2[i].y > v3Max.y) {
			v3Max.y = listOfVertex2[i].y;
		}
		if (listOfVertex2[i].z < v3Min.z) {
			v3Min.z = listOfVertex2[i].z;
		}
		else if (listOfVertex2[i].z > v3Max.z) {
			v3Max.z = listOfVertex2[i].z;
		}
	}

	v3Center2 = (v3Min + v3Max) / 2.0f;
	fRadius = glm::distance(v3Center, v3Max);

	pSphere2 = new PrimitiveClass();
	pSphere2->GenerateSphere(fRadius, 5, REGREEN);
=======
	if (nVertexCount > 0)
	{
		v3Min = vertexList[0];
		v3Max = vertexList[0];
	}

	for (uint i = 0; i < nVertexCount; i++)
	{
		if (vertexList[i].x > v3Max.x)
			v3Max.x = vertexList[i].x;
		else if (vertexList[i].x < v3Min.x)
			v3Min.x = vertexList[i].x;

		if (vertexList[i].y > v3Max.y)
			v3Max.y = vertexList[i].y;
		else if (vertexList[i].y < v3Min.y)
			v3Min.y = vertexList[i].y;

		if (vertexList[i].z > v3Max.z)
			v3Max.z = vertexList[i].z;
		else if (vertexList[i].z < v3Min.z)
			v3Min.z = vertexList[i].z;
	}

	m_v3Center1 = (v3Max + v3Min)/2.0f;
	m_fRadius1 = glm::distance(m_v3Center1, v3Max);

	m_pSphere1 = new PrimitiveClass();
	m_pSphere1->GenerateSphere(m_fRadius1, 10, REGREEN);


	//Creeper
	vertexList = m_pMeshMngr->GetVertexList("Creeper");
	nVertexCount = vertexList.size();

	if (nVertexCount > 0)
	{
		v3Min = vertexList[0];
		v3Max = vertexList[0];
	}

	for (uint i = 0; i < nVertexCount; i++)
	{
		if (vertexList[i].x > v3Max.x)
			v3Max.x = vertexList[i].x;
		else if (vertexList[i].x < v3Min.x)
			v3Min.x = vertexList[i].x;

		if (vertexList[i].y > v3Max.y)
			v3Max.y = vertexList[i].y;
		else if (vertexList[i].y < v3Min.y)
			v3Min.y = vertexList[i].y;

		if (vertexList[i].z > v3Max.z)
			v3Max.z = vertexList[i].z;
		else if (vertexList[i].z < v3Min.z)
			v3Min.z = vertexList[i].z;
	}

	m_v3Center2 = (v3Max + v3Min) / 2.0f;
	m_fRadius2 = glm::distance(m_v3Center2, v3Max);

	m_pSphere2 = new PrimitiveClass();
	m_pSphere2->GenerateSphere(m_fRadius2, 10, REGREEN);
>>>>>>> 24bcaaa6312502f76083515adcd9fefd5a7048a7
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
	bool bAreColliding = false;

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	bool bAreColliding = false;

	//Collision check goes here
	m_pMeshMngr->Print("x:" + std::to_string( m_v3Center1.x ) + " ", RERED);
	m_pMeshMngr->Print("y:" + std::to_string(m_v3Center1.y) + " ", RERED);
	m_pMeshMngr->Print("z:" + std::to_string(m_v3Center1.z) + " ", RERED);
	m_pMeshMngr->PrintLine("");

	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
<<<<<<< HEAD
	if(bAreColliding)
		m_pMeshMngr->PrintLine("Are Colliding", REGREEN);
	else
		m_pMeshMngr->PrintLine("Not Colliding", REGREEN);
=======
	if (bAreColliding)
		m_pMeshMngr->PrintLine("They are colliding! >_<", RERED);
	else
		m_pMeshMngr->PrintLine("They are not colliding! =)", REGREEN);
>>>>>>> 24bcaaa6312502f76083515adcd9fefd5a7048a7
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
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
	matrix4 m4Model = m_pMeshMngr->GetModelMatrix("Steve");
	m4Model = m4Model * glm::translate(v3Center);
	
<<<<<<< HEAD
	pSphere1->Render(m4Projection, m4View, m4Model);

	m4Model = m_pMeshMngr->GetModelMatrix("Creeper");
	m4Model = m4Model * glm::translate(v3Center2);

	pSphere1->Render(m4Projection, m4View, m4Model);

	m_pMeshMngr->Render();
=======
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	matrix4 m4Model =
		m_pMeshMngr->GetModelMatrix("Steve") *
		glm::translate(m_v3Center1) *
		glm::scale(vector3(m_fRadius1 * 2.0f));
	//m_pSphere1->Render(m4Projection, m4View, m4Model);
	m_pMeshMngr->AddSphereToQueue(m4Model, RERED, WIRE);

	m4Model =
		m_pMeshMngr->GetModelMatrix("Creeper") *
		glm::translate(m_v3Center2) *
		glm::scale(vector3(m_fRadius2 * 2.0f));
	//m_pSphere2->Render(m4Projection, m4View, m4Model);
	m_pMeshMngr->AddSphereToQueue(m4Model, RERED, WIRE);

	m_pMeshMngr->Render(); //renders the render list
>>>>>>> 24bcaaa6312502f76083515adcd9fefd5a7048a7

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
<<<<<<< HEAD
	if (pSphere1 != nullptr) {
		delete pSphere1;
		pSphere1 = nullptr;
	}
	if (pSphere2 != nullptr) {
		delete pSphere2;
		pSphere2 = nullptr;
=======
	if (m_pSphere1 != nullptr)
	{
		delete m_pSphere1;
		m_pSphere1 = nullptr;

	}
	if (m_pSphere2 != nullptr)
	{
		delete m_pSphere2;
		m_pSphere2 = nullptr;

>>>>>>> 24bcaaa6312502f76083515adcd9fefd5a7048a7
	}
	super::Release(); //release the memory of the inherited fields
}