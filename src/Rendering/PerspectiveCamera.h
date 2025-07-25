#pragma once

#include "Camera.h"

class PerspectiveCamera final : public Camera {
public:
	PerspectiveCamera(float fov, float near, float far);

	void RecalculateProjectionMatrix() override;

	inline float GetFarPlane() const { return farPlane; }
	inline void SetFarPlane(float value) { farPlane = value; needRecalculateProjMat = true; }

	inline float GetNearPlane() const { return nearPlane; }
	inline void SetNearPlane(float value) { nearPlane = value; needRecalculateProjMat = true; }

	inline float GetFieldOfView() const { return fieldOfView; }
	inline void SetFieldOfView(float value) { fieldOfView = value; needRecalculateProjMat = true; }

private: 
	float farPlane;
	float nearPlane;
	float fieldOfView; //Field Of View, in Degrees!
};