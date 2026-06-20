#pragma once

#include <PSGL\psgl.h>

// - Summary -----------------------------------------------------------------
// The core of the rendering process. Managed by the PSGL graphics API, 
// accessible using "Renderer".
// ---------------------------------------------------------------------------
class GLGraphicsContext {
	friend class Renderer;

	private:
		GLGraphicsContext();
		~GLGraphicsContext();

		// - Summary -----------------------------------------------------------------
		// Initialize and set up the Graphics Context using the PSGL API.
		// - Parameters --------------------------------------------------------------
		// - resolutionIDs
		//     A "priority-ordered" array of "CellVideoOutResolutionId"
		//     values you'd like PSGL to use.
		//     Check "GLGraphicsContext::GetBestVideoOutputMode" for more details
		//     about the usage of both parameters.
		// - numResolutions
		//     The number of elements in the array given.
		// - Returns -----------------------------------------------------------------
		// False is something failed during the process.
		// If the process failed, the error will be printed before returning.
		// ---------------------------------------------------------------------------
		bool Initialize(const unsigned int* resolutionIDs, unsigned int num);
		void Dispose() const;

		void CreateViewport();

		// - Summary -----------------------------------------------------------------
		// Prepare the Graphics Context for a new frame.
		// ---------------------------------------------------------------------------
		void PreRender();
		// - Summary -----------------------------------------------------------------
		// Finishes up the current frame.
		// ---------------------------------------------------------------------------
		void PostRender();

		// - Summary -----------------------------------------------------------------
		// Returns whether the PlayStation(R)3 is ready to output anything.
		// ---------------------------------------------------------------------------
		static bool IsDeviceVideoOutputReady();
		// - Summary -----------------------------------------------------------------
		// Assign "width" and "height" proper values based on an ID
		// from the "CellVideoOutResolutionId" given.
		// - Parameters --------------------------------------------------------------
		// - cellResolutionID
		//     The "CellVideoOutResolutionId" value to retrieve its width and height.
		// - Returns -----------------------------------------------------------------
		// 1 if the "cellResolutionID" given is value and "width" and "height"
		// values have been affected.
		// 0 if not ("width" and "height" will remain unmodified).
		// ---------------------------------------------------------------------------
		static int GetResolutionFromCellResolutionID(unsigned int resolutionID, unsigned int& width, unsigned int& height);
		// - Summary -----------------------------------------------------------------
		// Takes up a "priority-ordered" array of "CellVideoOutResolutionId" values
		// and return the ID of the first value available and supported inside
		// the array given.
		// - Parameters --------------------------------------------------------------
		// - cellResolutionID
		//     The "CellVideoOutResolutionId" value to retrieve its  width and height.
		// - Remarks -----------------------------------------------------------------
		// If a value like "CELL_VIDEO_OUT_RESOLUTION_0000x0000" is in
		// the array given and is selected, there's a chance the application
		// will be rendered at a lower resolution than the one currently setup
		// and used across the PlayStation3 system. In this case, the PSGL will
		// automatically stretch/upscale the final framebuffer to the current
		// resolution used by the PlayStation3.
		// - Example -----------------------------------------------------------------
		// My "top-priority" resolution is "1920x1080", and if not available,
		// I'd like "1280x720" to be my fallback one, I should input:
		//     wantedCellResolutionIDs = {
		//         CELL_VIDEO_OUT_RESOLUTION_1080, //1080p
		//         CELL_VIDEO_OUT_RESOLUTION_720, //720p
		//     };
		//     wantedCellResolutionIDsCount = 2;
		// - Returns -----------------------------------------------------------------
		// 0 if nothing amongst the array given is currently available.
		// Otherwise, the "CellVideoOutResolutionId" of the best available resolution.
		// ---------------------------------------------------------------------------
		static unsigned int GetBestVideoOutputMode(const unsigned int* resolutionIDs, unsigned int num);

		PSGLcontext* context;
		PSGLdevice* device;

		unsigned int viewportWidth;
		unsigned int viewportHeight;
		GLfloat viewportAspectRatio;

		bool isVSyncEnabled;
};