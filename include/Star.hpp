#ifndef STAR_HPP
#define STAR_HPP

/**
 * @file Star.hpp
 * @description Yıldız şekli için sınıf tanımı; yarıçapla büyüyen simetrik desen çizer.
 * Yıldız şeklinin çizim ve hareket mantığını içerir.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#include "Shape.hpp"

class Star : public Shape {
public:
    Star(int x, int y, int radius, char drawChar, int z); // Yeni yıldız oluşturur
    ~Star() override; // Yıldızı yok eder

    void draw(char** buffer, int rows, int cols) const override; // Yıldızı çizer
    void move(int dx, int dy) override; // Yıldızı hareket ettirir

    int getRadius() const; // Yıldızın yarıçapını döndürür
    void setRadius(int newRadius); // Yıldızın yarıçapını ayarlar

private:
    int radius; // Yıldızın yarıçapı
};

#endif

