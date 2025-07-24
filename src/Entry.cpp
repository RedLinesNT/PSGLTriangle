//-----------------------------------------------------------------------------
// The global entry point of the PSGLTriangle application.
//-----------------------------------------------------------------------------

#include "Core/Core.cpp"
#include "sys/process.h"

SYS_PROCESS_PARAM(1001, 0x10000)

int main(){
	DEBUG_PRINT("Hello World!\n");

	return 0;
}