#pragma once

#include "GraphicsContext.h"
#include "Camera.h"

//-----------------------------------------------------------------------------
// Global accessor for Rendering commands.
//-----------------------------------------------------------------------------
class Renderer {
public:
	Renderer() = delete;

	//-----------------------------------------------------------------------------
	// Initialize the Renderer and associated components.
	// Parameters:	
	//      cellResolutionIDs 
	//          A "priority-ordered" array of "CellVideoResolutionId" values 
	//          wishing to use with PSGL. Check "GraphicsContext::GetBestVideoOutputID" 
	//          for more details about the usage of both parameters.
	//      count
	//          The number of elements.
	// Returns:	
	//      True if successfully initialized.
	//-----------------------------------------------------------------------------
	static bool Initialize(const unsigned int* cellResolutionIDs, unsigned int count);
	// ----------------------------------------------------------------------------
	// Shutdown the Renderer and associated components.
	// ----------------------------------------------------------------------------
	static void Shutdown();

	//-----------------------------------------------------------------------------
	// Prepare the renderer for a new frame.
	// Notes:
	//      Must be called before any graphics-related commands and "Render(float)".
	//-----------------------------------------------------------------------------
	static void PreRender();
	//-----------------------------------------------------------------------------
	// Update the Renderer's associated components and do the rendering with
	// a provided Camera.
	// Parameters:	
	//      deltaTime 
	//          The current delta time.
	// Notes:
	//      Must be called after "PreRender()" and before "PostRender()".
	//-----------------------------------------------------------------------------
	static void Render(float deltaTime, Camera* camera);
	//-----------------------------------------------------------------------------
	// Prepare the renderer for a new frame.
	// Notes:
	//      Must be called after "Render(float)".
	//-----------------------------------------------------------------------------
	static void PostRender();

	inline static unsigned int GetViewportWidth() { return context->viewportWidth; }
	inline static unsigned int GetViewportHeight() { return context->viewportHeight; }
	inline static GLfloat GetAspectRatio() { return context->aspectRatio; }
	inline static bool IsVSyncEnabled() { return context->isVSyncEnabled; }
	inline static void SetVSync(bool value) { context->isVSyncEnabled = value; }
	inline static void SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a) { context->SetClearColor(r, g, b, a); }

private:
	static GraphicsContext* context;
};