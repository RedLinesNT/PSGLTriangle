//////////////////////////////////////////////////
/* Entry point of the PSGLTriangle application. */
//////////////////////////////////////////////////

#include <sys/spu_initialize.h>

#include "Rendering/PSGLContext.h"

int main() {
    //max usage spu, max raw spu
    sys_spu_initialize(6, 1);

    PSGLContext* context = new PSGLContext();
    context->Initialize();
    
    return 0; //Directly return into the XMB
}
