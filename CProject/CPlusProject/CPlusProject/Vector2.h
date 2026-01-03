#pragma once

struct Vector2 {
    int x;
    int y;
    Vector2(int initX, int initY) : x(initX), y(initY) {}
    Vector2() : x(0), y(0) {}
};