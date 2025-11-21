#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

/**
 * @file Rectangle.hpp
 * @description Dikdörtgen şekli için sınıf tanımı; ekran tamponunda dolu blok çizer.
 * Dikdörtgen şeklinin çizim ve hareket mantığını içerir.
 * @course 1C
 * @assignment 1. ÖDEV
 * @date 11.2025
 * @author Ayşe Verda Gülcemal ayse.gulcemal@ogr.sakarya.edu.tr
 */

#include "Shape.hpp"

class Rectangle : public Shape {
public:
    Rectangle(int x, int y, int width, int height, char drawChar, int z); // Yeni dikdörtgen oluşturur
    ~Rectangle() override; // Dikdörtgeni yok eder

    void draw(char** buffer, int rows, int cols) const override; // Dikdörtgeni çizer
    void move(int dx, int dy) override; // Dikdörtgeni hareket ettirir

    int getWidth() const; // Dikdörtgenin genişliğini döndürür
    int getHeight() const; // Dikdörtgenin yüksekliğini döndürür
    void setSize(int newWidth, int newHeight); // Dikdörtgenin boyutunu ayarlar

private:
    int width; // Dikdörtgenin genişliği
    int height; // Dikdörtgenin yüksekliği
};

#endif

