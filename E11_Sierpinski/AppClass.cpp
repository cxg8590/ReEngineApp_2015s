#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	//Using Base InitWindow method
	super::InitWindow("Instance Rendering");
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), vector3(0.0f, 0.0f, 0.0f), REAXISY);

	m_pMesh = new MyMesh();
	
	//Creating the Mesh points
	/*m_pMesh->AddVertexPosition(vector3(-1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3( 1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(0.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(RERED);
	m_pMesh->AddVertexPosition(vector3(-1.0f,  1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3(1.0f, -1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);
	m_pMesh->AddVertexPosition(vector3( 1.0f, 1.0f, 0.0f));
	m_pMesh->AddVertexColor(REBLUE);*/

	MakeTriangle(10, vector3(0.0f, 2.0f, 0.0f), vector3(-4.0f, -2.0f, 0.0f), vector3(4.0f, -2.0f, 0.0f));

	m_fMatrixArray = new float[m_nObjects * 16];

	const float* m4MVP = glm::value_ptr(IDENTITY_M4);
	for (uint n = 0; n < m_nObjects; n++)
	{
		memcpy(&m_fMatrixArray[n * 16], m4MVP, 16 * sizeof(float));
	}

	//Compiling the mesh
	m_pMesh->CompileOpenGL3X();
}

void AppClass::Update(void)
{
	//Update the system so it knows how much time has passed since the last call
	m_pSystem->UpdateTime();

	//Is the arcball active?
	if (m_bArcBall == true)
		ArcBall();

	//Is the first person camera active?
	if (m_bFPC == true)
		CameraRotation();

	//Calculate Camera
	m_pCameraMngr->CalculateView();

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
										  //Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the window
	
	//Matrices from the camera
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();

	m_pMesh->RenderList(m4Projection, m4View, m_fMatrixArray, m_nObjects);//Rendering nObjects
	m_pMeshMngr->Render();

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	SafeDelete(m_fMatrixArray);
	if (m_pMesh != nullptr)
	{
		delete m_pMesh;
		m_pMesh = nullptr;
	}
	super::Release();
}

void AppClass::MakeTriangle(int level, vector3 top, vector3 left, vector3 right) {
	if (level == 0) {
		m_pMesh->AddVertexPosition(top);
		m_pMesh->AddVertexColor(RERED);
		m_pMesh->AddVertexPosition(left);
		m_pMesh->AddVertexColor(RERED);
		m_pMesh->AddVertexPosition(right);
		m_pMesh->AddVertexColor(RERED);
	}
	else {
		vector3 leftMid = vector3((top.x + left.x) / 2.0f, (top.y + left.y) / 2.0f, 0.0f);
		vector3 rightMid = vector3((top.x + right.x) / 2.0f, (top.y + right.y) / 2.0f, 0.0f);
		vector3 bottomMid = vector3((right.x + left.x) / 2.0f, (right.y + left.y) / 2.0f, 0.0f);

		MakeTriangle(level - 1, top, leftMid, rightMid);
		MakeTriangle(level - 1, leftMid, left, bottomMid);
		MakeTriangle(level - 1, rightMid, bottomMid, right);
	}
}