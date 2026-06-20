#include "Camera.h"

Camera* Camera::mainCamera = nullptr;

Camera::Camera(const E_CAMERA_TYPE type) : type(type) {
	transform = new Transform();
	isProjectionMatrixDirty = true;
	if (mainCamera == nullptr) SetMainCamera(this);
}

Camera::~Camera() {
	delete transform;
}

Matrix4 Camera::GetViewMatrix() const {
	return Matrix4::rotationZ(-transform->Rotation.getZ()) *
		Matrix4::rotationY(-transform->Rotation.getY()) *
		Matrix4::rotationX(-transform->Rotation.getX()) *
		Matrix4::translation(-transform->Position);
}