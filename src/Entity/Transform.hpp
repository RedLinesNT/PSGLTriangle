#pragma once

#include "vectormath/cpp/vectormath_aos.h"

using namespace Vectormath::Aos;

class Transform final {
public:
	inline Transform() :	position(0.0f, 0.0f, 0.0f),
							rotation(0.0f, 0.0f, 0.0f),
							scale(1.0f, 1.0f, 1.0f) {
		needRecalculateMatrices = true;
	}

	inline Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale) :
						position(position), rotation(rotation), scale(scale) {
		needRecalculateMatrices = true;
	}

	//-----------------------------------------------------------------------------
	// Returns the LocalToWorld matrix of this Transform.
	// Notes:
	//      If "needRecalculateMatrices" is true, "RecalculateMatrices" will
	//      be called first to ensure a correct LocalToWorld matrix is returned.
	//-----------------------------------------------------------------------------
	inline Matrix4 GetLocalToWorld() {
		if (needRecalculateMatrices) {
			RecalculateMatrices();
			needRecalculateMatrices = false;
		}

		return localToWorld;
	}

	//-----------------------------------------------------------------------------
	// Whether this transform needs to have "RecalculateMatrices" called.
	//-----------------------------------------------------------------------------
	inline bool NeedRecalculateMatrices() const { return needRecalculateMatrices; }

	//-----------------------------------------------------------------------------
	// Recalculate the LocalToWorld matrix of this Transform.
	//-----------------------------------------------------------------------------
	inline void RecalculateMatrices() {
		localToWorld = Matrix4::translation(position) *
			Matrix4::rotationX(rotation.getX()) *
			Matrix4::rotationY(rotation.getY()) *
			Matrix4::rotationZ(rotation.getZ()) *
			Matrix4::scale(scale);
	}

	//Oh my god, I should probably do nested structs for this or something like that

	inline float GetPositionX() { return position[0]; }
	inline float GetPositionY() { return position[1]; }
	inline float GetPositionZ() { return position[2]; }
	inline Vector3 GetPosition() const { return position; }
	inline void SetPositionX(float value) { position[0] = value; needRecalculateMatrices = true; }
	inline void SetPositionY(float value) { position[1] = value; needRecalculateMatrices = true; }
	inline void SetPositionZ(float value) { position[2] = value; needRecalculateMatrices = true; }

	inline float GetRotationX() { return rotation[0]; }
	inline float GetRotationY() { return rotation[1]; }
	inline float GetRotationZ() { return rotation[2]; }
	inline Vector3 GetRotation() const { return rotation; }
	inline void SetRotationX(float value) { rotation[0] = value; needRecalculateMatrices = true; }
	inline void SetRotationY(float value) { rotation[1] = value; needRecalculateMatrices = true; }
	inline void SetRotationZ(float value) { rotation[2] = value; needRecalculateMatrices = true; }

	inline float GetScaleX() { return scale[0]; }
	inline float GetScaleY() { return scale[1]; }
	inline float GetScaleZ() { return scale[2]; }
	inline Vector3 GetScale() const { return scale; }
	inline void SetScaleX(float value) { scale[0] = value; needRecalculateMatrices = true; }
	inline void SetScaleY(float value) { scale[1] = value; needRecalculateMatrices = true; }
	inline void SetScaleZ(float value) { scale[2] = value; needRecalculateMatrices = true; }

private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;

	Matrix4 localToWorld;

	bool needRecalculateMatrices;
};