#include "Renderer.h"
#include "Camera.h"
#include "..\Core\Core.h"

GLGraphicsContext* Renderer::context = nullptr;

bool Renderer::Initialize(const unsigned int* resolutionIDs, unsigned int num) {
	if (context != nullptr) { //Uh?
		PRINT("Renderer - The Renderer is already running? What?\n")
		return false;
	}

	context = new GLGraphicsContext();
	if (!context->Initialize(resolutionIDs, num)) {
		PRINT("Renderer - The GLGraphicsContext failed to pass the initialization phase!\n")
		return false;
	}

	PRINT("Renderer - Everything is OK!\n")
	return true;
}

void Renderer::Shutdown() {
	context->Dispose();
	delete context;

	PRINT("Renderer - Shutting down.\n")
}

void Renderer::PreRender() {
	context->PreRender();
}

// MY BEAUTIFUL TRIANGLE :)
Transform* triangleTransform = new Transform();
float* triangleVertices = new float[9] {
	1.0f, 1.0f, 0.0f, //01 - Top
	1.0f, -1.0f, 0.0f, //02 - Bottom Right
	-1.0f, -1.0f, 0.0f, // 03 - Bottom Left
};
float* triangleColors = new float[12] {
	1.0f, 0.0f, 0.0f, 1.0f, //RED
	0.0f, 1.0f, 0.0f, 1.0f, //GREEN
	0.0f, 0.0f, 1.0f, 1.0f, //BLUE
};

void Renderer::Render(float deltaTime) {
	if (Camera::GetMainCamera() == nullptr) return;

	//I'll be using the easy "gl" methods provided by default in OpenGL.
	//I can only hope Sony and Khronos did the "right" thing and actually made these methods use
	//the SPU I allowed the API to use. 

	//This is the "funny" part where I could also do OcclusionCulling requests using an "SPUModule" to determine
	//what should and shouldn't be rendered. (probably not the best place to do it, but eh)
	//In my case, since I only want to draw a simple triangle, I'll just do that part here.

	if (Camera::GetMainCamera()->IsProjectionMatrixDirty()) Camera::GetMainCamera()->RecalculateProjectionMatrix();

	Camera::GetMainCamera()->GetTransform().Update(); //Update Pos/Rot

	//Retrieve Matrices
	Matrix4 projMatrix = Camera::GetMainCamera()->GetProjectionMatrix();
	Matrix4 viewMatrix = -Camera::GetMainCamera()->GetViewMatrix();

	//Rotating the Triangle
	triangleTransform->Rotation[0] += 1.0f * deltaTime;
	triangleTransform->Rotation[1] += 1.0f * deltaTime;
	triangleTransform->Rotation[2] += 1.0f * deltaTime;
	triangleTransform->Update();

	//Projection Matrix (Camera)
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf((GLfloat*)&projMatrix);

	//View Matrix (Camera)
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf((GLfloat*)&viewMatrix);

	//Model Transform (of the triangle in this case)
	glMultMatrixf((GLfloat*)&triangleTransform->GetLocalToWorld());

	glDisable(GL_DEPTH_TEST);
	glCullFace(GL_FRONT_AND_BACK);

	//Drawing the Triangle
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, triangleVertices);
	glColorPointer(4, GL_FLOAT, 0, triangleColors);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glPopMatrix();
}

void Renderer::PostRender() {
	context->PostRender();
}