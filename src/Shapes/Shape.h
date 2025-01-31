#pragma once

#include "PSGL/psgl.h"

/// <summary>
/// A very very very primitive
/// way of implementing different
/// type of shapes to draw using PSGL.
/// </summary>
class Shape {
public:
    Shape() = default;
    virtual ~Shape() = default;

    /// <summary>
    /// Render the shape.
    /// </summary>
    virtual void Render() = 0;

protected:
    /// <summary>
    /// The vertices of the shape.
    /// </summary>
    float* vertices;
    /// <summary>
    /// The color of the vertices.
    /// </summary>
    float* colors;
};