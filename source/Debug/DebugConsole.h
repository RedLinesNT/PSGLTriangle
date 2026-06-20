#pragma once

#include <cell\dbgfont.h>
#include <list>

struct DebugConsoleInitOptions {
	const char* Name;
	float PosLeft = 0.1f;
	float PosTop = 0.1f;

	float Width = 16;
	float Height = 4;
	float Scale = 0.25f;

	// - Remarks -----------------------------------------------------------------
	// ABGR Color, not RGBA!
	// ---------------------------------------------------------------------------
	uint32_t Color = 0xFFFF64FF;

	bool DoPrints = true;
};

class DebugConsole {
	public:
		DebugConsole(const DebugConsoleInitOptions& options);

	protected:
		~DebugConsole();

	public:
		void Printf(const char* string, ...) const;
		void PrintfPut(const char* string, ...) const;

		void Enable();
		void Disable();
		void Clear() const;

		static void UpdateConsoles(float deltaTime);

	protected:
		virtual void Update(float deltaTime);

	private:
		DebugConsoleInitOptions initOptions;
		CellDbgFontConsoleId consoleID;
		bool isEnabled;

		static std::list<DebugConsole*> consoles;
		// - Summary -----------------------------------------------------------------
		// Whether the "cellDbg" library has been already initialized.
		// ---------------------------------------------------------------------------
		static bool hasBeenInitialized;
};