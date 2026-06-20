#include "DebugConsole.h"
#include "..\Core\Core.h"
#include "..\Rendering\Renderer.h"

std::list<DebugConsole*> DebugConsole::consoles;
bool DebugConsole::hasBeenInitialized = false;

DebugConsole::DebugConsole(const DebugConsoleInitOptions& options) : initOptions(options) {
	if (!hasBeenInitialized) {
		CellDbgFontConfig config;
		config.bufSize = 512;
		config.screenWidth = Renderer::GetViewportWidth();
		config.screenHeight = Renderer::GetViewportHeight();

		cellDbgFontInit(&config);
		hasBeenInitialized = true;
	}

	CellDbgFontConsoleConfig consoleConfig;
	consoleConfig.posLeft = options.PosLeft;
	consoleConfig.posTop = options.PosTop;
	consoleConfig.cnsWidth = options.Width;
	consoleConfig.cnsHeight = options.Height;
	consoleConfig.scale = options.Scale;
	consoleConfig.color = options.Color;

	consoleID = cellDbgFontConsoleOpen(&consoleConfig);
	consoles.push_back(this);

	PRINT("%s - Console created!\n", initOptions.Name);
	Enable();
}

DebugConsole::~DebugConsole() {
	consoles.remove(this);
	cellDbgFontConsoleClose(consoleID);

	if (consoles.empty()) {
		cellDbgFontExit();
		hasBeenInitialized = false;
	}

	PRINT("%s - Console destroyed!\n", initOptions.Name);
}

void DebugConsole::UpdateConsoles(float deltaTime) {
	cellDbgFontDraw();

	for (DebugConsole* console : consoles) {
		if (console->isEnabled) console->Update(deltaTime);
	}
}

void DebugConsole::Update(float deltaTime) {}

void DebugConsole::Enable() {
	isEnabled = true;
	cellDbgFontConsoleEnable(consoleID);
}

void DebugConsole::Disable() {
	isEnabled = false;
	cellDbgFontConsoleDisable(consoleID);
}

void DebugConsole::Printf(const char* string, ...) const {
	char temp_str[512];

	va_list arg_list;
	va_start(arg_list, string);
	vsprintf(temp_str, string, arg_list);
	va_end(arglist);

	cellDbgFontConsolePrintf(consoleID, temp_str);
	if (initOptions.DoPrints) PRINT("%s - %s\n", initOptions.Name, temp_str);
}

void DebugConsole::PrintfPut(const char* string, ...) const {
	char temp_str[512];

	va_list arg_list;
	va_start(arg_list, string);
	vsprintf(temp_str, string, arg_list);
	va_end(arglist);

	cellDbgFontPuts(initOptions.PosLeft, initOptions.PosTop, initOptions.Scale, initOptions.Color, temp_str);
	if (initOptions.DoPrints) PRINT("%s - %s\n", initOptions.Name, temp_str);
}