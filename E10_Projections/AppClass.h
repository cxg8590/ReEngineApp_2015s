/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/09
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>
#include "Camera.h"
//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
	PrimitiveClass* m_pCone = nullptr;
	PrimitiveClass* m_pCylinder = nullptr;

	matrix4 m_m4Projection;
	matrix4 m_m4View;

	Camera* camera = Camera::GetInstance();
public:
	typedef ReEngAppClass super;

	/* Constructor */
	AppClass(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) : super(hInstance, lpCmdLine, nCmdShow) {}

	/*
	InitWindow
	Initialize ReEng variables necessary to create the window
	*/
	virtual void InitWindow(String a_sWindowName);

	/*
	InitVariables
	Initializes user specific variables, this is executed right after InitApplicationVariables,
	the purpose of this member function is to initialize member variables specific for this lesson
	*/
	virtual void InitVariables(void);

	/*
	Update
	Updates the scene
	*/
	virtual void Update(void);

	/*
	Display
	Displays the scene
	*/
	virtual void Display(void);

	/*
	ProcessKeyboard
	Manage the response of key presses
	*/
	virtual void ProcessKeyboard(void);

	/*
	Release
	Releases the application
	IF INHERITED AND OVERRIDEN MAKE SURE TO RELEASE BASE POINTERS (OR CALL BASED CLASS RELEASE)
	*/
	virtual void ProcessMouse(void) final;

	virtual void mouseRotate(float a_fSpeed = 0.005f) final
	{
		UINT	MouseX, MouseY;		// Coordinates for the mouse
		UINT	CenterX, CenterY;	// Coordinates for the center of the screen.

									//Initialize the position of the pointer to the middle of the screen
		CenterX = m_pSystem->GetWindowX() + m_pSystem->GetWindowWidth() / 2;
		CenterY = m_pSystem->GetWindowY() + m_pSystem->GetWindowHeight() / 2;

		//Calculate the position of the mouse and store it
		POINT pt;
		GetCursorPos(&pt);
		MouseX = pt.x;
		MouseY = pt.y;

		//Calculate the difference in view with the angle
		float fAngleX = 0.0f;
		float fAngleY = 0.0f;
		float fDeltaMouse = 0.0f;
		if (MouseX < CenterX)
		{
			fDeltaMouse = static_cast<float>(CenterX - MouseX);
			fAngleY += fDeltaMouse * a_fSpeed;
		}
		else if (MouseX > CenterX)
		{
			fDeltaMouse = static_cast<float>(MouseX - CenterX);
			fAngleY -= fDeltaMouse * a_fSpeed;
		}

		if (MouseY < CenterY)
		{
			fDeltaMouse = static_cast<float>(CenterY - MouseY);
			fAngleX -= fDeltaMouse * a_fSpeed;
		}
		else if (MouseY > CenterY)
		{
			fDeltaMouse = static_cast<float>(MouseY - CenterY);
			fAngleX += fDeltaMouse * a_fSpeed;
		}
		//Change the Yaw and the Pitch of the camera
		camera->ChangeRoll(fAngleX * 3.0f);
		camera->ChangePitch(fAngleY * 3.0f);
		SetCursorPos(CenterX, CenterY);//Position the mouse in the center
	}

	virtual void Release(void);

	/*
	USAGE: Reads the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void ReadConfig(void) final {}
	/*
	USAGE: Writes the configuration of the application to a file
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	virtual void WriteConfig(void) final {}
};

#endif //__APPLICATION_H_
