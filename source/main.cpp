#include <sys/process.h>
#include <sys/spu_initialize.h>
#include <cell/sysmodule.h>

#include "Core\Core.h"
#include "Core\SystemCallback.h"
#include "Time\DeltaTime.h"
#include "Input\PadUtility.h"
#include "Rendering\Renderer.h"
#include "Rendering\Camera\PerspectiveCamera.h"

#include "Debug\DebugConsole.h"
#include "Rendering\RendererStatsDebugConsole.h"
#include "Rendering\Camera\CameraDebugConsole.h"

SYS_PROCESS_PARAM(1001, 0x10000)

constexpr unsigned int resolutions[] = { //Resolutions available
	CELL_VIDEO_OUT_RESOLUTION_1080, //HDMI Only
	CELL_VIDEO_OUT_RESOLUTION_720, //HDMI Only
	CELL_VIDEO_OUT_RESOLUTION_480,
};

PerspectiveCamera* worldCamera = nullptr; //World Camera
static void EnableVSync() { Renderer::SetVSync(true); }
static void DisableVSync() { Renderer::SetVSync(false); }
static void MoveWorldCameraForward() { worldCamera->GetTransform().Position[2] += 0.1f; }
static void MoveWorldCameraBackward() { worldCamera->GetTransform().Position[2] -= 0.1f; }
static void RotateWorldCameraX() { worldCamera->GetTransform().Rotation[1] += 0.1f; }
static void RotateWorldCameraY() { worldCamera->GetTransform().Rotation[1] -= 0.1f; }
static void WorldCameraFOVUp() { worldCamera->SetFieldOfView(worldCamera->GetFieldOfView() + 2); }
static void WorldCameraFOVDown() { worldCamera->SetFieldOfView(worldCamera->GetFieldOfView() - 2); }

int main() {
	//Define the amount of SPUs the application will use
	sys_spu_initialize(6, 1); //1 Raw SPU dedicated to PSGL

	//System setup
	SystemCallback::Subscribe();
	if (!Renderer::Initialize(resolutions, sizeof(resolutions) / sizeof(resolutions[0]))) return -1; //Failure
	PadUtility::Setup(PAD_EIGHT);
	DeltaTime* deltaTime = new DeltaTime();

	//Button binds
	PadUtility::GetPad(PAD_ONE).SubscribePressedFunc(E_PAD_BUTTON::CROSS, EnableVSync);
	PadUtility::GetPad(PAD_ONE).SubscribePressedFunc(E_PAD_BUTTON::CIRCLE, DisableVSync);
	PadUtility::GetPad(PAD_ONE).SubscribePressedFunc(E_PAD_BUTTON::DPAD_UP, MoveWorldCameraForward);
	PadUtility::GetPad(PAD_ONE).SubscribePressedFunc(E_PAD_BUTTON::DPAD_DOWN, MoveWorldCameraBackward);
	PadUtility::GetPad(PAD_ONE).SubscribePressedFunc(E_PAD_BUTTON::DPAD_LEFT, RotateWorldCameraX);
	PadUtility::GetPad(PAD_ONE).SubscribePressedFunc(E_PAD_BUTTON::DPAD_RIGHT, RotateWorldCameraY);
	PadUtility::GetPad(PAD_ONE).SubscribePressedFunc(E_PAD_BUTTON::R1, WorldCameraFOVUp);
	PadUtility::GetPad(PAD_ONE).SubscribePressedFunc(E_PAD_BUTTON::L1, WorldCameraFOVDown);

	//Camera setup
	worldCamera = new PerspectiveCamera(60.0f, 0.0f, 100.0f);
	worldCamera->GetTransform().Position.setZ(-5.0f);

	//DebugConsoles setup
	RendererStatsDebugConsole* rendererConsole = RendererStatsDebugConsole::Create();
	CameraDebugConsole* cameraConsole = CameraDebugConsole::Create();

	while (!SystemCallback::HasReceivedCloseCallback()) {
		float dt = deltaTime->UpdateDeltaTime();
		SystemCallback::Poll();
		PadUtility::Poll();

		Renderer::PreRender();
			Renderer::Render(dt);
			DebugConsole::UpdateConsoles(dt);
		Renderer::PostRender();
	}

	delete deltaTime;
	delete worldCamera;
	delete rendererConsole;
	delete cameraConsole;

	PadUtility::Dispose();
	Renderer::Shutdown();
	SystemCallback::Unsubscribe();

	return CELL_OK;
}