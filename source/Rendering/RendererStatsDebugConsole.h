#pragma once

#include "..\Debug\DebugConsole.h"

class RendererStatsDebugConsole final : public DebugConsole {
	public:
		RendererStatsDebugConsole(const DebugConsoleInitOptions& options);
		virtual ~RendererStatsDebugConsole() = default;

		static RendererStatsDebugConsole* Create();

	protected:
		void Update(float deltaTime) override;

	private:
		float framerate; //Latest framerate value displayed
		float updateTimeElapsed; 
};