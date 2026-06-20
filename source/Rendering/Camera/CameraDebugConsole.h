#pragma once

#include "..\..\Debug\DebugConsole.h"

// - Summary -----------------------------------------------------------------
// Display information about the Camera::mainCamera running.
// ---------------------------------------------------------------------------
class CameraDebugConsole final : public DebugConsole {
	public:
		CameraDebugConsole(const DebugConsoleInitOptions& options);
		virtual ~CameraDebugConsole() = default;

		static CameraDebugConsole* Create();

	protected:
		void Update(float deltaTime) override;
};