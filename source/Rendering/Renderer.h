#pragma once

#include "GLGraphicsContext.h"

//Forward delcarations
class Camera;

// - Summary -----------------------------------------------------------------
// Context-free accessor to interact with the rendering API, bringing a sort
// of "abstraction layer".
// ---------------------------------------------------------------------------
class Renderer {
	friend class Camera;

	public:
		Renderer() = delete;

		// - Summary -----------------------------------------------------------------
		// Initialize and set up the Graphics Context using the PSGL API.
		// - Parameters --------------------------------------------------------------
		// - resolutionIDs
		//     A "priority-ordered" array of "CellVideoOutResolutionId"
		//     values you'd like the rendering API to use.
		//     Check "GLGraphicsContext::GetBestVideoOutputMode" for more details
		//     about the usage of both parameters.
		// - numResolutions
		//     The number of elements in the array given.
		// - Returns -----------------------------------------------------------------
		// False is something failed during the process.
		// If the process failed, the error will be printed before returning.
		// ---------------------------------------------------------------------------
		static bool Initialize(const unsigned int* resolutionIDs, unsigned int num);
		static void Shutdown();

		// - Summary -----------------------------------------------------------------
		// Prepare the Graphics Context for a new frame.
		// ---------------------------------------------------------------------------
		static void PreRender();
		// - Summary -----------------------------------------------------------------
		// Actually render stuff
		// ---------------------------------------------------------------------------
		static void Render(float deltaTime);
		// - Summary -----------------------------------------------------------------
		// Finishes up the current frame.
		// ---------------------------------------------------------------------------
		static void PostRender();

		static inline unsigned int GetViewportWidth() { return context->viewportWidth; }
		static inline unsigned int GetViewportHeight() { return context->viewportHeight; }
		static inline GLfloat GetViewportAspectRatio() { return context->viewportAspectRatio; }
		static inline bool IsVSyncEnabled() { return context->isVSyncEnabled; }
		static inline void SetVSync(bool value) { context->isVSyncEnabled = value; }

	private:
		static GLGraphicsContext* context;
};