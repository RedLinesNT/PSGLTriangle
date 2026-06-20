#pragma once

#include "..\Camera.h"

class PerspectiveCamera final : public Camera {
	public:
		PerspectiveCamera(float fov, float near, float far);

		void RecalculateProjectionMatrix() override;

		inline float GetFarPlane() const { return farPlane; }
		inline void SetFarPlane(const float value) { farPlane = value; isProjectionMatrixDirty = true; }

		inline float GetNearPlane() const { return nearPlane; }
		inline void SetNearPlane(const float value) { nearPlane = value; isProjectionMatrixDirty = true; }

		inline float GetFieldOfView() const { return fieldOfView; }
		inline void SetFieldOfView(const float value) { fieldOfView = value; isProjectionMatrixDirty = true; }

	private:
		float farPlane;
		float nearPlane;
		float fieldOfView;
};