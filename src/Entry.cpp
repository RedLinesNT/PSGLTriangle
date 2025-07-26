//-----------------------------------------------------------------------------
// The global entry point of the PSGLTriangle application.
//-----------------------------------------------------------------------------

#include "sys/process.h"
#include "sys/spu_initialize.h"

#include "Core/Core.h"
#include "Rendering/Renderer.h"
#include "Rendering/PerspectiveCamera.h"
#include "Core/CELLCallbacks.h"
#include "Core/DeltaTime.hpp"
#include "Input/PadUtility.h"

SYS_PROCESS_PARAM(1001, 0x10000)

// ------------------------------------------
// Our "priority-ordered" list of resolutions
// to display our application at.
// ------------------------------------------
constexpr unsigned int resolutions[] = {
	CELL_VIDEO_OUT_RESOLUTION_1080, //HDMI Only
	CELL_VIDEO_OUT_RESOLUTION_720, //HDMI Only
	CELL_VIDEO_OUT_RESOLUTION_576,
	CELL_VIDEO_OUT_RESOLUTION_480,
};

static void ColorRED() {
	Renderer::SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);
}

static void ColorGREEN() {
	Renderer::SetClearColor(0.0f, 1.0f, 0.0f, 1.0f);
}

PerspectiveCamera* worldCamera = nullptr;

int main(){
	DEBUG_PRINT("Launching PSGLTriangle...\n");

	sys_spu_initialize(6, 1); //1 Raw SPU used by PSGL
	CELLCallbacks::BindCallbacks();
	DeltaTime* deltaTime = new DeltaTime();
	PadUtility::Initialize(PAD_EIGHT);

	PadUtility::GetPad(PAD_ONE).SetPressedFunc(E_PAD_BUTTONS::CROSS, ColorRED);
	PadUtility::GetPad(PAD_ONE).SetPressedFunc(E_PAD_BUTTONS::CIRCLE, ColorGREEN);

	if (!Renderer::Initialize(resolutions, sizeof(resolutions)/sizeof(resolutions[0]))) {
		exit(-1); //Initialization failed, details have been printed
	}

	//Set up a Perspective Camera
	worldCamera = new PerspectiveCamera(60.0f, 0.1f, 100.0f);
	worldCamera->GetTransform().SetPositionZ(-5.0f);

	while (!CELLCallbacks::HasReceivedCloseCallback()) {
		float dt = deltaTime->UpdateDeltaTime();

		Renderer::PreRender();
			Renderer::Render(dt, worldCamera);
		Renderer::PostRender();
		
		CELLCallbacks::Update();
		PadUtility::Update();
	}

	PadUtility::Dispose();
	CELLCallbacks::UnbindCallbacks();
	Renderer::Shutdown();

	delete worldCamera;

	return 0; //Return to the XMB
}