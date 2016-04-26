#ifndef __CAMERA_H_
#define __CAMERA_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include <GLFW\glfw3.h>
//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll
class Camera
{

public:
	matrix4 GetView(void);
	matrix4 GetProjection(bool bOrtographic);
	void SetPosition(vector3 v3Position);
	void SetTarget(vector3 v3Target);
	void SetUp(vector3 v3Up);
	void MoveForward(float fIncrement);
	void MoveSideways(float fIncrement);
	void MoveVertical(float fIncrement);
	void ChangePitch(float fIncrement);
	void ChangeRoll(float fIncrement);
	void ChangeYaw(float fIncrement);

	static Camera* GetInstance();
	static void ReleaseInstance();


private:
	Camera();
	~Camera();
	matrix4 m_m4Projection;
	matrix4 m_m4View;
	vector3 position = glm::vec3(0.0f, 0.0f, 15.0f);
	vector3 target = glm::vec3(0.0f, 0.0f, 14.0f);
	vector3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	matrix4 rotate;
	static Camera* instance;
};

#endif //__APPLICATION_H_