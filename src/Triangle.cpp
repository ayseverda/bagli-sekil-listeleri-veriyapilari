/**
 * @file Triangle.cpp
 * @description Üçgen şeklinin satır satır nasıl çizildiğini tanımlar.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#include "Triangle.hpp"

// Bu dosya üçgen şeklinin satır satır nasıl çizildiğini tanımlar.

 Triangle::Triangle(int x, int y, int height, char drawChar, int z)
     : Shape(x, y, drawChar, z), height(height) {}
 
 Triangle::~Triangle() = default;
 
 void Triangle::draw(char** buffer, int rows, int cols) const {
     for (int i = 0; i < height; ++i) {
         int startX = x - i;
         int endX = x + i;
         int drawY = y + i;
 
         if (drawY < 0 || drawY >= rows) {
             continue;
         }
 
         for (int col = startX; col <= endX; ++col) {
             if (col < 0 || col >= cols) {
                 continue;
             }
             buffer[drawY][col] = character;
         }
     }
 }
 
 void Triangle::move(int dx, int dy) {
     Shape::move(dx, dy);
 }
 
 int Triangle::getHeight() const {
     return height;
 }
 
 void Triangle::setHeight(int newHeight) {
     height = newHeight;
 }