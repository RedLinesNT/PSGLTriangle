//////////////////////////////////////////////////
/* Entry point of the PSGLTriangle application. */
//////////////////////////////////////////////////

#include <cstdio>
#include <cell/gcm.h>
#include <sys/return_code.h>
#include <sys/spu_initialize.h>
#include <sysutil/sysutil_sysparam.h>

#include "Rendering/PSGLContext.h"
#include "Shapes/Quad.hpp"

#include "Shapes/Shape.h"
#include "Shapes/Triangle.hpp"

constexpr unsigned int resolutions[] = { //Our target resolutions to use
    CELL_VIDEO_OUT_RESOLUTION_1080,
    CELL_VIDEO_OUT_RESOLUTION_720,
};

/// <summary>
/// Will be set to true if the user
/// or PlayStation3 system is requesting
/// the application to close.
/// </summary>
static bool ShouldClose = false;

/// <summary>
/// Handle some specific CELL's callbacks.
/// </summary>
/// <remarks>
/// Only used to exit the application's while loop.
/// If this isn't handled, the PlayStation3 will
/// freeze when closing the application then force itself
/// into a full reboot.
/// </remarks>
static void HandleCELLCloseCallback(uint64_t status, uint64_t param, void* userdata) {
    (void)param;
    (void)userdata;

    if (status == CELL_SYSUTIL_REQUEST_EXITGAME) {
        ShouldClose = true;
        std::printf("[PSGLTriangle] CELL_SYSUTIL_REQUEST_EXITGAME Callback received! Shutting down...\n");
    }
}

int main() {    
    //max usage spu, max raw spu
    sys_spu_initialize(6, 1); //Setup SPUs
    cellSysutilRegisterCallback(0, HandleCELLCloseCallback, nullptr); //Setup shutdown callback
    
    //Initialize our own PSGLContext
    PSGLContext* context = new PSGLContext();
    bool initResult = context->Initialize(resolutions, sizeof(resolutions)/sizeof(resolutions[0]));
    if (!initResult) { return -1; } //Initialization failed, details have already been printed
    std::printf("[PSGLTriangle] PSGL's Context has been initialized!\n");

    //Create a shape
    Shape* shape = new Triangle();
    
    //TODO: KEY COMBO TO FORCE SHUTDOWN? (Could be fun)
    while (!ShouldClose) {
        cellSysutilCheckCallback(); //Check for incoming system's callbacks
        
        context->PreRender(); //PSGL's Pre-Render Phase
        shape->Render(); //Render our shape!
        context->PostRender(); //PSGL's Post-Render Phase
    }

    context->Dispose();
    
    return CELL_OK; //Directly return into the XMB
}
