#pragma once

#include "PSGL/psgl.h"

//-----------------------------------------------------------------------------
// Create, Manage, Dispose the PSGL's graphics context throughout
// the application's life-time.
//
// The GraphicsContext's operations are handled via the "Renderer".
//-----------------------------------------------------------------------------
class GraphicsContext {
	friend class Renderer;

private:
	GraphicsContext();
	~GraphicsContext();

	//-----------------------------------------------------------------------------
	// Initialize PSGL's graphics context.
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
	bool Initialize(const unsigned int* cellResolutionIDs, unsigned int count);
	//-----------------------------------------------------------------------------
	// Dispose PSGL's graphics context.
	//-----------------------------------------------------------------------------
	void Dispose() const;

	//-----------------------------------------------------------------------------
	// Prepare the graphics context for a new frame.
	//-----------------------------------------------------------------------------
	void PreRender();
	//-----------------------------------------------------------------------------
	// Finishes up the current frame.
	//-----------------------------------------------------------------------------
	void PostRender();

	//-----------------------------------------------------------------------------
	// Set up the viewport.
	// Notes: Will only be done once at the context's initialization.
	//-----------------------------------------------------------------------------
	void CreateViewport();
	
	//-----------------------------------------------------------------------------
	// Whether the system's video output is ready for rendering.
	//-----------------------------------------------------------------------------
	static bool IsVideoOutputReady();
	//-----------------------------------------------------------------------------
	// Assign "width" and "height" proper values based on a 
	// "CellVideoOutResolutionId" value.
	// Parameters:
	//      cellResolutionID
	//          The target "CellVideoOutResolutionId" value.
	// Returns:	
	//      1 if the "cellResolutionID" value given is valid and proper values 
	//      have been outputted. 0 if not.
	//-----------------------------------------------------------------------------
	static int GetResolutionFromCELLResolutionID(unsigned int cellResolutionID, unsigned int& width, unsigned int& height);
	//-----------------------------------------------------------------------------
	// Takes up a "priority-ordered" array of "CellVideoOutResolution"
	// values and return the ID of the first value available and supported.
	// Returns:	
	//      0 if nothing amongst the array given is currently available.
	//      Otherwise, the "CellVideoOutResolutionId" of the best available resolution.
	// Notes: 
	//      If the PlayStation3's current resolution used is for example 1080p 
	//      and the application can only do rendering at 720p, the final 
	//      framebuffer will automatically be stretched/upscaled.
	//-----------------------------------------------------------------------------
	static unsigned int GetBestVideoOutputID(const unsigned int* wantedCellResolutionIDs, unsigned int count);

	static void SetClearColor(GLclampf r, GLclampf g, GLclampf b, GLclampf a);

private:
	PSGLcontext* psglContext;
	PSGLdevice* psglDevice;

	unsigned int viewportWidth;
	unsigned int viewportHeight;
	GLfloat aspectRatio;

	bool isVSyncEnabled;
};