#include "Camera.h"
Camera* Camera::instance = nullptr;

Camera::Camera() {
	position = glm::vec3(0.0f, 0.0f, 15.0f);
	target = glm::vec3(0.0f, 0.0f, 0.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
}
Camera::~Camera() {

}

matrix4 Camera::GetProjection(bool ortho) {
	if (ortho) {
		m_m4Projection = glm::ortho(0.0f, 100.0f, 100.0f, 0.0f);
	}
	else {
		m_m4Projection = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	}
	return m_m4Projection;
}
matrix4 Camera::GetView() {
	return m_m4View;
}
void Camera::SetPosition(vector3 pos) {
	position = pos;
	m_m4View = glm::lookAt(position, target, up);
	m_m4View *= rotate;
}
void Camera::SetTarget(vector3 targ) {
	target = targ;
	m_m4View = glm::lookAt(position, target, up);
	m_m4View *= rotate;
}
void Camera::SetUp(vector3 upVec) {
	up = upVec;
	m_m4View = glm::lookAt(position, target, up); 
	m_m4View *= rotate;
}
void Camera::MoveForward(float fIncrement) {
	SetPosition(vector3(position.x, position.y, position.z + fIncrement));
}
void Camera::MoveSideways(float fIncrement) {
	SetPosition(vector3(fIncrement + position.x, position.y, position.z));
}
void Camera::MoveVertical(float fIncrement) {
	SetPosition(vector3(position.x, position.y + fIncrement, position.z));
}
void Camera::ChangePitch(float fIncrement) {
	glm::quat qRoll = glm::quat(vector3(0.0f, fIncrement, 0.0f));
	rotate *= glm::mat4_cast(qRoll);
	SetPosition(position);
}
void Camera::ChangeRoll(float fIncrement) {
	glm::quat qRoll = glm::quat(vector3(fIncrement, 0.0f, 0.0f));
	rotate *= glm::mat4_cast(qRoll);
	SetPosition(position);
}
void Camera::ChangeYaw(float fIncrement) {
	glm::quat qYaw = glm::quat(vector3(0.0f, 0.0f, fIncrement));
	rotate *= glm::mat4_cast(qYaw);
	SetPosition(position);
}

Camera* Camera::GetInstance() {
	if (instance == nullptr) {
		instance = new Camera();
	}
	return instance;
}
void Camera::ReleaseInstance() {
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}