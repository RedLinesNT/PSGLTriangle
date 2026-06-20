#include "PerspectiveCamera.h"

#include "PSGL/psgl.h"
#include "PSGL/psglu.h"
#include "..\Renderer.h"

PerspectiveCamera::PerspectiveCamera(float fov, float near, float far) : Camera(E_CAMERA_TYPE::PERSPECTIVE) {
	farPlane = far;
	nearPlane = near;
	fieldOfView = fov;
}

void PerspectiveCamera::RecalculateProjectionMatrix() {
	projectionMatrix = Matrix4::perspective(fieldOfView * (M_PI / 180.0f), Renderer::GetViewportAspectRatio(), nearPlane, farPlane);
	isProjectionMatrixDirty = false;
}
