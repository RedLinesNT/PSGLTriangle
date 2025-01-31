#pragma once
#include "Shape.h"

class Triangle : public Shape {
public:
    Triangle();
    virtual ~Triangle() override;
    virtual void Render() override;
};
