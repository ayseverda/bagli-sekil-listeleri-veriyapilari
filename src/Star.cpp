/**
* @file Star.cpp
* @description Yıldız şeklinin çizimini ve hareketini tanımlar.
* @course 1C
* @assignment 1. ÖDEV
* @date 11.2025
* @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
*/

#include "Star.hpp"
#include <algorithm>
#include <cstdlib>

using namespace std;

Star::Star(int x, int y, int radius, char drawChar, int z)
    : Shape(x, y, drawChar, z), radius(radius) {}

Star::~Star() = default;

void Star::draw(char** buffer, int rows, int cols) const {
    int clampedRadius = max(0, radius);
    for (int dy = -clampedRadius; dy <= clampedRadius; ++dy) {
        int drawY = y + dy;
        if (drawY < 0 || drawY >= rows) {
            continue;
        }

        int span = clampedRadius - abs(dy);
        int startX = x - span;
        int endX = x + span;

        startX = max(startX, 0);
        endX = min(endX, cols - 1);

        for (int drawX = startX; drawX <= endX; ++drawX) {
            buffer[drawY][drawX] = character;
        }
    }
}

void Star::move(int dx, int dy) {
    Shape::move(dx, dy);
}

int Star::getRadius() const { return radius; }

void Star::setRadius(int newRadius) {
    radius = newRadius;
}