#pragma once

#include <cell\pad\libpad.h>
#include <cell\pad\error.h>
#include <list>
#include "Pad.h"

#define CELL_USBPAD_AUTO_PARSE 1

#define PAD_ONE (0)
#define PAD_TWO (1)
#define PAD_THREE (2)
#define PAD_FOUR (3)
#define PAD_FIVE (4)
#define PAD_SIX (5)
#define PAD_SEVEN (6)
#define PAD_EIGHT (7)

class PadUtility {
	public:
		PadUtility() = delete;

		static void Setup(uint8_t num);
		static void Poll();
		static void Dispose();
		
		static void ClearPadBuffers();

		// - Remarks -----------------------------------------------------------------
		// If the "index" given is invalid, the 'PAD_ONE' will be returned instead.
		// ---------------------------------------------------------------------------
		static Pad& GetPad(uint8_t index);

	private:
		static std::list<Pad*> pads;
};