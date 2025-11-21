/**
 * @file Shape.cpp
 * @description Tüm şekillerin paylaştığı temel davranışların gövdelerini barındırır.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#include "Shape.hpp"

// Bu dosya tüm şekillerin paylaştığı temel davranışların gövdelerini barındırır.
 Shape::Shape(int x, int y, char drawChar, int z)
     : x(x), y(y), character(drawChar), z(z) {}
 
 Shape::~Shape() = default;
 
 void Shape::move(int dx, int dy) {
     x += dx;
     y += dy;
 }
 
 int Shape::getX() const { return x; }
 int Shape::getY() const { return y; }
 int Shape::getZ() const { return z; }
 char Shape::getChar() const { return character; }
 
 void Shape::setPosition(int newX, int newY) {
     x = newX;
     y = newY;
 }
 
 void Shape::setZ(int newZ) {
     z = newZ;
 }