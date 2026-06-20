#pragma once

#include "..\Core\Core.h"
#include "..\Entity\Transform.h"

enum class E_CAMERA_TYPE : int {
	PERSPECTIVE = 0,
	ORTHOGRAPHIC = 1,
};

class Camera {
	public:
		Camera(const E_CAMERA_TYPE type);
		virtual ~Camera();

		virtual void RecalculateProjectionMatrix() = 0;
		
		// - Remarks -----------------------------------------------------------------
		// This will recalculate the View Matrix each time the method is called!
		// ---------------------------------------------------------------------------
		Matrix4 GetViewMatrix() const;

		inline bool IsProjectionMatrixDirty() const { return isProjectionMatrixDirty; }
		inline Matrix4 GetProjectionMatrix() const { return projectionMatrix; }

		// - Summary -----------------------------------------------------------------
		// The camera used for rendering the world.
		// ---------------------------------------------------------------------------
		inline static Camera* GetMainCamera() { return mainCamera; }
		inline static void SetMainCamera(Camera* camera) { mainCamera = camera; PRINT("Main Camera has been defined!\n") }

		inline Transform& GetTransform() const { return *transform; }
		inline E_CAMERA_TYPE GetCameraType() const { return type; }

	protected:
		Transform* transform;
		E_CAMERA_TYPE type;
		bool isProjectionMatrixDirty;
		Matrix4 projectionMatrix;

	private:
		static Camera* mainCamera;
};

