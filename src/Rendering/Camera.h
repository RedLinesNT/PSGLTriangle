#pragma once

#include "Core/Core.h"
#include "Entity/Transform.hpp"

class Camera {
public:
	Camera();
	virtual ~Camera();

	//-----------------------------------------------------------------------------
	// Recalculate the Projection Matrix of this Camera.
	//-----------------------------------------------------------------------------
	virtual void RecalculateProjectionMatrix() = 0;
	//-----------------------------------------------------------------------------
	// Recalculate the View Matrix of this Camera.
	//-----------------------------------------------------------------------------
	void RecalculateViewMatrix();

	//-----------------------------------------------------------------------------
	// Calculate and return the View Matrix of this Camera.
	// Notes: 
	//      If "needRecalculateViewMat" is true, "RecalculateViewMatrix()" will
	//      be called first to ensure a correct View Matrix is returned.
	//-----------------------------------------------------------------------------
	Matrix4 GetViewMatrix();
	//-----------------------------------------------------------------------------
	// Returns the Projection Matrix of this camera.
	// Notes:
	//      If "needRecalculateProjMat" is true, "RecalculateProjectionMatrix" will
	//      be called first to ensure a correct Projection Matrix is returned.
	//-----------------------------------------------------------------------------
	Matrix4 GetProjectionMatrix();

	//-----------------------------------------------------------------------------
	// Returns the Transform associated with this Camera.
	//-----------------------------------------------------------------------------
	inline Transform& GetTransform() { return *transform; }
	//-----------------------------------------------------------------------------
	// Whether this camera needs to have "RecalculateProjectionMatrix" called.
	//-----------------------------------------------------------------------------
	inline bool NeedRecalculateProjectionMatrix() const { return needRecalculateProjMat; }
	//-----------------------------------------------------------------------------
	// Whether this camera needs to have "RecalculateViewMatrix" called.
	//-----------------------------------------------------------------------------
	inline bool NeedRecalculateViewMatrix() const { return needRecalculateViewMat; }

protected:
	Transform* transform;

	Matrix4 projMat;
	Matrix4 viewMat;

	bool needRecalculateProjMat;

private:
	bool needRecalculateViewMat;
};