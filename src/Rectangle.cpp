/**
 * @file Rectangle.cpp
 * @description Dikdörtgen şeklinin çizim ve hareket mantığını içerir.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#include "Rectangle.hpp"
#include <algorithm>

// Bu dosya dikdörtgen şeklinin çizim ve hareket mantığını içerir.
using namespace std;

 Rectangle::Rectangle(int x, int y, int width, int height, char drawChar, int z)
     : Shape(x, y, drawChar, z), width(width), height(height) {}
 
 Rectangle::~Rectangle() = default;
 
void Rectangle::draw(char** buffer, int rows, int cols) const {
    int startY = max(0, y);
    int endY = min(rows - 1, y + height - 1);
    int startX = max(0, x);
    int endX = min(cols - 1, x + width - 1);

    for (int row = startY; row <= endY; ++row) {
        for (int col = startX; col <= endX; ++col) {
            buffer[row][col] = character;
        }
    }
 }
 
 void Rectangle::move(int dx, int dy) {
     Shape::move(dx, dy);
 }
 
 int Rectangle::getWidth() const { return width; }
 int Rectangle::getHeight() const { return height; }
 
 void Rectangle::setSize(int newWidth, int newHeight) {
     width = newWidth;
     height = newHeight;
 }