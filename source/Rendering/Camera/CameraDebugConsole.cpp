#include "CameraDebugConsole.h"
#include "PerspectiveCamera.h"

CameraDebugConsole* CameraDebugConsole::Create() {
	DebugConsoleInitOptions options;
	options.Name = "CameraDebug";
	options.PosLeft = 0.7f;
	options.PosTop = 0.0f;
	options.Width = 35.0f;
	options.Height = 3.0f;
	options.Scale = 0.65f;
	options.Color = 0xFFFFFFFF;
	options.DoPrints = false;

	return new CameraDebugConsole(options);
}

CameraDebugConsole::CameraDebugConsole(const DebugConsoleInitOptions& options) : DebugConsole(options) {
	
}

void CameraDebugConsole::Update(float deltaTime) {
	if (Camera::GetMainCamera() == nullptr) return;

	if (Camera::GetMainCamera()->GetCameraType() == E_CAMERA_TYPE::PERSPECTIVE) {
		auto* pers = static_cast<PerspectiveCamera*>(Camera::GetMainCamera());
		this->PrintfPut("FOV: %.1f / FAR: %.1f / NEAR: %.3f",
			pers->GetFieldOfView(), pers->GetFarPlane(), pers->GetNearPlane());
	}

	PrintfPut("\nPOS: %.1f, %.1f, %.1f",
		Camera::GetMainCamera()->GetTransform().Position.getX().getAsFloat(),
		Camera::GetMainCamera()->GetTransform().Position.getY().getAsFloat(),
		Camera::GetMainCamera()->GetTransform().Position.getZ().getAsFloat());

	PrintfPut("\n\nROT: %.1f, %.1f, %.1f",
		Camera::GetMainCamera()->GetTransform().Rotation.getX().getAsFloat(),
		Camera::GetMainCamera()->GetTransform().Rotation.getY().getAsFloat(),
		Camera::GetMainCamera()->GetTransform().Rotation.getZ().getAsFloat());
}