#pragma once

#include <vectormath\cpp\vectormath_aos.h>

using namespace Vectormath::Aos;

class Transform final {
	public:
		Vector3 Position;
		Vector3 Rotation;
		Vector3 Scale;

		Transform() : Position(0.0f, 0.0f, 0.0f), Rotation(0.0f, 0.0f, 0.0f), Scale(1.0f, 1.0f, 1.0f) {}
		Transform(const Vector3 position, const Vector3 rotation, const Vector3 scale) : Position(position), Rotation(rotation), Scale(scale) {}

		inline void Update() {
			//This code is a mess!
			//Usually, you shouldn't directly expose "Position", "Rotation" and "Scale" like I'm doing.
			//You should rather have Getters/Setters catch these values being modified AND set a "isDirty" flag to true.
			//Using "isDirty" would prevent you from recomputing the whole "localToWorld" matrix each frame. For a single object it'll be fine, but for a whole scene it'll be a sh*tfest...
			//That logic is partially implemented on the "Camera" stuff of the application.
			localToWorld = Matrix4::translation(Position) *
				Matrix4::rotationX(Rotation.getX()) * Matrix4::rotationY(Rotation.getY()) * Matrix4::rotationZ(Rotation.getZ()) *
				Matrix4::scale(Scale);
		}
		inline Matrix4& GetLocalToWorld() { return localToWorld; }

	private:
		Matrix4 localToWorld;
};