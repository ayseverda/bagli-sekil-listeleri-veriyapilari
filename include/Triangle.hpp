/**
 * @file Triangle.hpp
 * @description Üçgen şekli için sınıf tanımı; yüksekliğe göre çizim yapar.
 * Üçgen şeklinin çizim ve hareket mantığını içerir.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Shape.hpp"

class Triangle : public Shape {
public:
    Triangle(int x, int y, int height, char drawChar, int z); // Yeni üçgen oluşturur
    ~Triangle() override; // Üçgeni yok eder

    void draw(char** buffer, int rows, int cols) const override; // Üçgeni çizer
    void move(int dx, int dy) override; // Üçgeni hareket ettirir

    int getHeight() const; // Üçgenin yüksekliğini döndürür 
    void setHeight(int newHeight); // Üçgenin yüksekliğini ayarlar

private:
    int height; // Üçgenin yüksekliği
};

#endif

