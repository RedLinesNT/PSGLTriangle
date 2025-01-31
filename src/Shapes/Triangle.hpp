#pragma once
#include "Shape.h"

class Triangle : public Shape {
public:
    inline Triangle() {
        vertices = new float[9] {
            0.0f, 0.5f, 0.0f, //01 - Middle Top
            0.5f, -0.5f, 0.0f, //02 - Bottom Right
            -0.5f, -0.5f, 0.0f, // 03 - Bottom Left
        };

        colors = new float[12] {
            1.0f, 0.0f, 0.0f, 1.0f, //RED
            0.0f, 1.0f, 0.0f, 1.0f, //GREEN
            0.0f, 0.0f, 1.0f, 1.0f, //BLUE
        };
    }
    ~Triangle() override = default;
    
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
            glDrawArrays(GL_TRIANGLES, 0, 3);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);
        
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }
};