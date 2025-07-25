#pragma once

#include <list>
#include "Pad.h"

#define CELL_USBPAD_AUTO_PARSE
#define PAD_ONE (0)
#define PAD_TWO (1)
#define PAD_THREE (2)
#define PAD_FOUR (3)
#define PAD_FIVE (4)
#define PAD_SIX (5)
#define PAD_SEVEN (6)
#define PAD_EIGHT (7)
#define MAX_PADS = PAD_EIGHT

//-----------------------------------------------------------------------------
// Manage the PlayStation3 controllers via the "Pad" class.
//-----------------------------------------------------------------------------
class PadUtility {
public: 
	PadUtility() = delete;

	//-----------------------------------------------------------------------------
	// Initialize the PadUtility as well of each pad requested to be initialized.
	//-----------------------------------------------------------------------------
	static void Initialize(uint8_t maxPads);
	//-----------------------------------------------------------------------------
	// Dispose the PadUtility and the pads created.
	//-----------------------------------------------------------------------------
	static void Dispose();
	static void Update();
	static void ClearPadBuffers();

	static Pad& GetPad(uint8_t portID);
	static bool IsPadConnected(uint8_t portID);

private:
	static std::list<Pad*> pads;
};