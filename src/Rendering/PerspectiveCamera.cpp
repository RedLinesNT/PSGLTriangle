#include "PerspectiveCamera.h"
#include "Rendering/Renderer.h"

PerspectiveCamera::PerspectiveCamera(float fov, float near, float far) : Camera() {
	fieldOfView = fov;
	nearPlane = near;
	farPlane = far;
}

void PerspectiveCamera::RecalculateProjectionMatrix() {
	projMat = Matrix4::perspective(fieldOfView * (M_PI / 180.0f), Renderer::GetAspectRatio(), nearPlane, farPlane);
	needRecalculateProjMat = false;
}