#pragma once
#include "Shape.h"

class Quad : public Shape {
public:
    inline Quad() {
        vertices = new float[12] {
            0.5f, 0.5f, 0.0f, //01 - Top Right
            0.5f, -0.5f, 0.0f, //02 - Bottom Right
            -0.5f, -0.5f, 0.0f, // 03 - Bottom Left
            -0.5f, 0.5f, 0.0f, //04 - Top Left
        };

        colors = new float[16] {
            1.0f, 0.0f, 0.0f, 1.0f, //RED
            0.0f, 1.0f, 0.0f, 1.0f, //GREEN
            0.0f, 0.0f, 1.0f, 1.0f, //BLUE
            1.0f, 1.0f, 0.0f, 1.0f, //YELLOW
        };
    }
    ~Quad() override = default;
    
    void Render() override {
        glMatrixMode(GL_MODELVIEW); //TODO: Should probably remove matrix stuff from here
        glLoadIdentity();
        glPushMatrix();
        
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_TEXTURE_2D);
        glDisable(GL_BLEND);
    
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
            glVertexPointer(3, GL_FLOAT, 0, vertices);
            glColorPointer(4, GL_FLOAT, 0, colors);
            glDrawArrays(GL_QUADS, 0, 4);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
};