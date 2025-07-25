#include "Camera.h"

Camera::Camera() {
	transform = new Transform();
	needRecalculateProjMat = true;
	needRecalculateViewMat = true;
}

Camera::~Camera() {
	delete transform;
}

void Camera::RecalculateViewMatrix() {
	viewMat = Matrix4::rotationZ(-transform->GetRotationZ()) *
				Matrix4::rotationY(-transform->GetRotationY()) *
				Matrix4::rotationX(-transform->GetRotationX()) *
				Matrix4::translation(-transform->GetPosition());
	needRecalculateViewMat = false;
}

Matrix4 Camera::GetViewMatrix() {
	if (needRecalculateViewMat) {
		RecalculateViewMatrix();
	}

	return viewMat;
}

Matrix4 Camera::GetProjectionMatrix() {
	if (needRecalculateProjMat || transform->NeedRecalculateMatrices()) {
		transform->RecalculateMatrices();
		RecalculateProjectionMatrix();
	}

	return projMat;
}