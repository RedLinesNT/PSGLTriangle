//////////////////////////////////////////////////
/* Entry point of the PSGLTriangle application. */
//////////////////////////////////////////////////

#include <cstdio>
#include <sys/return_code.h>
#include <sys/spu_initialize.h>
#include <sysutil/sysutil_sysparam.h>

#include "Rendering/PSGLContext.h"
#include "Shapes/Quad.hpp"

#include "Shapes/Shape.h"
#include "Shapes/Triangle.hpp"

/// <summary>
/// The number of iterations in our
/// loop to switch between the Triangle
/// and the Quad.
/// </summary>
/// <remarks>
/// Not sure, but there's a change this
/// number correspond to the number of frames
/// since PSGL is probably handling presentation
/// cap automatically the framerate and block
/// iterations for a certain amount of time,
/// but I forgot...
/// </remarks>
constexpr int NumberLoopCountsToggleShapes = 180;

/// <summary>
/// Our "priority-ordered" list of
/// resolutions to use with PSGL to display
/// our application.
/// </summary>
constexpr unsigned int resolutions[] = {
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

    int loopCounts = 0;
    
    //Create a shape
    Shape* triangleShape = new Triangle();
    Shape* quadShape = new Quad();

    Shape* activeShapeToRender = triangleShape;
    
    //KEY COMBO TO FORCE SHUTDOWN? (Could be fun)
    while (!ShouldClose) {
        cellSysutilCheckCallback(); //Check for incoming system's callbacks
        
        context->PreRender(); //PSGL's Pre-Render Phase
        activeShapeToRender->Render(); //Render our shape!
        context->PostRender(); //PSGL's Post-Render Phase

        loopCounts++;
        if (loopCounts >= NumberLoopCountsToggleShapes) { //Toggle between the Triangle and Quad
            if (activeShapeToRender == triangleShape) {
                activeShapeToRender = quadShape;
                std::printf("[PSGLTriangle] Displaying the Quad\n");
            } else {
                activeShapeToRender = triangleShape;
                std::printf("[PSGLTriangle] Displaying the Triangle\n");
            }

            loopCounts = 0;
        }
    }
    
    context->Dispose();

    delete triangleShape;
    delete quadShape;
    delete activeShapeToRender;
    delete context;
    
    return CELL_OK; //Directly return into the XMB
}
