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

int main() {    
    //max usage spu, max raw spu
    sys_spu_initialize(6, 1);

    //Initialize our own PSGLContext
    PSGLContext* context = new PSGLContext();
    bool initResult = context->Initialize(resolutions, sizeof(resolutions)/sizeof(resolutions[0]));
    if (!initResult) { return -1; } //Initialization failed, details have already been printed

    std::printf("[PSGLTriangle] PSGL's Context has been initialized!\n");

    //Create a shape
    Shape* shape = new Quad();
    
    //TODO: KEY COMBO TO FORCE SHUTDOWN? (Could be fun)
    while (true) {
        context->PreRender();
        
        shape->Render(); //Render our shape!

        context->PostRender();
    }

    context->Dispose();
    
    return CELL_OK; //Directly return into the XMB
}
