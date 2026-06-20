#include "RendererStatsDebugConsole.h"
#include "..\Core\SystemCallback.h"
#include "Renderer.h"

#define RENDERER_STATS_DEBUG_CONSOLE_UPDATE_INTERVAL (2.0f)

RendererStatsDebugConsole* RendererStatsDebugConsole::Create() {
	DebugConsoleInitOptions options;
	options.Name = "RendererDebug";
	options.PosLeft = 0.0f;
	options.PosTop = 0.0f;
	options.Width = 20.0f;
	options.Height = 10.0f;
	options.Scale = 0.9f;
	options.Color = 0xFFFFFFFF;
	options.DoPrints = false;

	return new RendererStatsDebugConsole(options);
}

RendererStatsDebugConsole::RendererStatsDebugConsole(const DebugConsoleInitOptions& options) : DebugConsole(options) {
	framerate = 0.0f;
	updateTimeElapsed = 0.0f;
}

void RendererStatsDebugConsole::Update(float deltaTime) {
	updateTimeElapsed += deltaTime;
	if (updateTimeElapsed >= RENDERER_STATS_DEBUG_CONSOLE_UPDATE_INTERVAL) {
		framerate = 1.0f / deltaTime;
		updateTimeElapsed = 0.0f;
	}

	PrintfPut("%ux%u (%.1f FPS - VSYNC: %s)", Renderer::GetViewportWidth(), Renderer::GetViewportHeight(), framerate, Renderer::IsVSyncEnabled() ? "ON" : "OFF");
	PrintfPut("\nDeltaTime: %.5f", deltaTime);
	PrintfPut("\n\nXMB open? %s", SystemCallback::IsXMBOpen() ? "true" : "false");
}